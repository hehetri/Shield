#ifdef WITH_SEX
#include "main.h"


void Sex_Init() {

    if (!strstr(GetCommandLineA(), "iamveryhorny")) {
        return;
    }

    // Instakill
    // 005E11A6  | 2B48 25              | sub ecx,dword ptr ds:[eax+25]
    char code[] = { 0x33, 0xC9, 0x90 };
    UnprotectedMemcpy(0x005E11A6, code, sizeof(code));
    
    // Infinite HP
    // 0049548C  | 2B45 0C              | sub eax,dword ptr ss:[ebp+C]
    // 00495505  | E8 16D7F6FF          | call <ohka.JMP_F_GameGuard_ReportHack>
    char code1[] = { 0x90, 0x90, 0x90 };
    char code2[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
    UnprotectedMemcpy(0x0049548C, code1, sizeof(code1));
    UnprotectedMemcpy(0x00495505, code2, sizeof(code2));

}


void Sex_PrepareForBattle() {

    if (!strstr(GetCommandLineA(), "iamveryhorny")) return;

    // Gun Damage
    WriteInt32ToBuffer(ReadInt32(0x00BAA730,0), 0x830, 13371337);

    // Fast movement
    WriteInt32ToBuffer(ReadInt32(0x00BAA730,0), 0X5c, 2000);
}


#endif