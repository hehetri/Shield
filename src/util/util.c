#include "main.h"
#include "util/util.h"

// void WriteToJumpTable(void* address, void* function) {
//     WriteInt32ToBuffer(address, 1, (((int8*)function) - address - 5));
// }


/**
 * Here's a little lesson about endianness.
 * Little endian means, that, the "smallest" byte of a hex number comes last.
 * For example:
 * 1234 in decimal, becomes 0x000004d2 written in little endian hex.
 * Notice how the zeroes are all to the left.
 * However, as big endian this would be written as 0xd20400000.
 * As you can see, the smallest byte comes first, and the biggest last;
 * That is why they call it big endian!
**/

int32 SwapEndian32(int32 num) {
    return
        ((num >> 24) & 0xff)      | // move byte 3 to byte 0
        ((num << 8)  & 0xff0000)  | // move byte 1 to byte 2
        ((num >> 8)  & 0xff00)    | // move byte 2 to byte 1
        ((num << 24) & 0xff000000); // move byte 0 to byte 3
}

int16 SwapEndian16(int16 num) {
    return (num >> 8) | (num << 8);
}




void WriteJMP(void* location, void* to) {
    DWORD oldProtection;
    VirtualProtect(location, 5, PAGE_EXECUTE_READWRITE, &oldProtection);
    *(char*)location = 0xE9; // JMP opcode
    *(int*)(location + 1) = (int)(to - location - 5);
    VirtualProtect(location, 5, oldProtection, &oldProtection);
}

void WriteJMPToBuffer(void* location, void* to, char* buffer) {
    *(char*)buffer = 0xE9; // JMP opcode
    *(int*)(buffer + 1) = (int)(to - location - 5);
}

void WriteCall(void* location, void* to) {
    DWORD oldProtection;
    VirtualProtect(location, 5, PAGE_EXECUTE_READWRITE, &oldProtection);
    *(char*)location = 0xE8; // CALL opcode
    *(int*)(location + 1) = (int)(to - location - 5);
    VirtualProtect(location, 5, oldProtection, &oldProtection);
}

void WriteCallToBuffer(void* location, void* to, char* buffer) {
    *(char*)buffer = 0xE8; // CALL opcode
    *(int*)(buffer + 1) = (int)(to - location - 5);
}

void UnprotectedMemcpy(void* dest, void* source, int size) {
    DWORD oldProtection;
    VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &oldProtection);
    memcpy(dest, source, size);
    VirtualProtect(dest, size, oldProtection, &oldProtection);
}