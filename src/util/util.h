#pragma once

/*******************************************************************************
 * C++ call method emulation.
 * If you don't have a struct (class name) for a type, use void.
 ******************************************************************************/
#define THISCALL_ENTER(type)/**/\
    type* this;\
    asm("movl %%ecx, %0" :"=g"(this))

#define THISCALL_ENTER_REG(type)/**/\
    type* this;\
    asm("movl %%ecx, %0" :"=r"(this))

#define THISCALL_ENTER_MEM(type)/**/\
    type* this;\
    asm("movl %%ecx, %0" :"=m"(this))

/*******************************************************************************
 * Memory writing macros.
 * Note that the offsets are always incremented by 1, instead of by sizeof(type)
 ******************************************************************************/
#define MakeFuncPtr(function, address)/**/\
    (((int8*)&function) - address - 5)

#define WriteInt8(address, value)/**/\
    *(int8*)(address)=(value)

#define WriteInt16(address, value)/**/\
    *(int16*)(address)=(value)

#define WriteInt32(address, value)/**/\
    *(int32*)(address)=(value)

#define WriteInt8ToBuffer(address, offset, value)/**/\
    *(int8*)((int8*)address+(offset))=(value)

#define WriteInt16ToBuffer(address, offset, value)/**/\
    *(int16*)((int8*)address+(offset))=(value)

#define WriteInt32ToBuffer(address, offset, value)/**/\
    *(int32*)((int8*)address+(offset))=(value)

#define WriteToJumpTable(address, function)/**/\
    WriteInt32ToBuffer(address, 1, MakeFuncPtr(function, address))
// void WriteToJumpTable(address, function);

/*******************************************************************************
 * Memory reading macros.
 * Note that the offsets are always incremented by 1, instead of by sizeof(type)
 ******************************************************************************/
#define ReadInt8(buffer, offset)/**/\
    (*(int8*)((int32)(buffer)+(offset)))

#define ReadInt16(buffer, offset)/**/\
    (*(int16*)((int32)(buffer)+(offset)))

#define ReadInt32(buffer, offset)/**/\
    (*(int32*)(((int32)(buffer))+(offset)))

/*******************************************************************************
 * Endianness.
 ******************************************************************************/
int32 SwapEndian32(int32 num);
int16 SwapEndian16(int16 num);

/*******************************************************************************
 * Code-editing.
 ******************************************************************************/
void WriteJMP(void* location, void* to);
void WriteJMPToBuffer(void* location, void* to, char* buffer);
void WriteCall(void* location, void* to);
void WriteCallToBuffer(void* location, void* to, char* buffer);
void UnprotectedMemcpy(void* dest, void* source, int size);
