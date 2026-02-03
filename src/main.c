#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "ui/ui.h"
#include "d3d/direct3d.h"
#include "antihack/antihack.h"
#include "60fps/60fps.h"
#include "config.h"

#ifndef DISABLE_GAME_PATCHES
#define DISABLE_GAME_PATCHES 1
#endif

#ifdef DEBUG
BOOL __stdcall SetRectWrapper(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom) {
    printf("SetRect(%lu,%lu, %lu,%lu)\n", xLeft,yTop,xRight,yBottom);
    return SetRect(lprc, xLeft, yTop, xRight, yBottom);
}
#endif


/**
 * Gets called right before the game enters the game loop.
**/
void OnLoad() {
    // PatchScalingCode();
#ifdef DEBUG
    // D3DHook_Init();
#endif
}

static void overwriteWindowTitle() {
    strcpy((char*)WINDOW_TITLE, "Bout Evolution");
}

static void removeGameGuard() {
    // Prevent gameguard from creating it's directory
    char jmp = 0xEB;
    UnprotectedMemcpy(0x00706EC4, &jmp, 1);
}

/**
 * The client has fake instructions right before it enters the game loop.
 * This is to make the game more dependant on the shield.
 * When the shield is loaded, it patches these instructions with a call to
 * to OnLoad(), and then a jump that skips the rest of the fake instructions.
**/
static void installOnLoadHook() {
    // 004376F1 | 6A 05       | push 5                                             | BOGUS INSTRUCTION
    // 004376F3 | 93          | xchg ebx,eax                                       | BOGUS INSTRUCTION
    // 004376F4 | B9 54010000 | mov ecx,154                                        | BOGUS INSTRUCTION
    // 004376F9 | E8 D6A1FCFF | call <bout.JMP_F_CCameraManager::ChangeAngle(int i | BOGUS INSTRUCTION
    // 004376FE | 83C4 08     | add esp,8                                          | BOGUS INSTRUCTION
    int8 code[16];
    WriteCallToBuffer(0x004376F1, OnLoad, code);
    WriteJMPToBuffer(0x004376F1 + 5, 0x00437701/*@gameLoop*/, code + 5);
    UnprotectedMemcpy(0x004376F1, code, 16);
}

/**
 * Patches the game's built in multiclient protection.
**/
static void allowMulticlienting() {
    // 00437330 | E9 EE050000 | jmp <ohka.z_return>
    int8 code[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
    UnprotectedMemcpy(0x00437330, code, sizeof(code));
}   

/**
 * Overwrites / hooks game functions.
**/
static void loadHooks() {
    WriteToJumpTable(0x0040132A, Config_Write);
    WriteToJumpTable(0x0040448A, Config_Load);
    // WriteToJumpTable(0x004022CA, CDirect3D_Create); // @TODO: This crashed, maybe due to a thiscall bug
    WriteToJumpTable(0x0040173A, CDirect3D_GetDevice);
    // WriteToJumpTable(0x00401C6C, CDirect3D_DrawText);
    WriteToJumpTable(0x004048CC, Window_Init);

#ifdef WITH_60FPS
    WriteToJumpTable(0x00403A71, Clock_CalculateTickDelta);
#endif

    // Lobby
    WriteToJumpTable(0x004027C5, CViewLobby_Create);
    char nopsLobbyPrepare[] = {
        0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
    };
    UnprotectedMemcpy(0x0053E38C, nopsLobbyPrepare, sizeof(nopsLobbyPrepare));
    WriteCall(0x0053E387, CViewLobby_Prepare);

    // Room
    char nopsRoomPrepare[] = {
        0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xFF, 0x15, 0xD8, 0x9D, 0xBD, 0x00
    };
    UnprotectedMemcpy(0x0053E484, nopsRoomPrepare, sizeof(nopsRoomPrepare));
    WriteCall(0x0053E484, CViewRoom_Prepare);
    char nopsRoomPrepare2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
    UnprotectedMemcpy(0x00422055, nopsRoomPrepare2, sizeof(nopsRoomPrepare2));
    WriteCall(0x00422055, CViewRoom_Prepare); // hooks end of view change function

    // Battle
    WriteCall(0x0042235B, CViewBattle_Prepare);
    
    // WriteInt32(0x00BDA200, SetRectWrapper);


}

__declspec(dllexport) void _pei386_runtime_relocator(void){} // required mingw w64 hack


BOOL WINAPI DllMainCRTStartup(HMODULE module, DWORD reason, LPVOID reserved) {
    switch (reason) {
    case DLL_THREAD_ATTACH:
        // ThreadList_AddThread(GetCurrentThreadId());
        break;
    case DLL_THREAD_DETACH:
        // ThreadList_RemoveThread(GetCurrentThreadId());
        break;
    case DLL_PROCESS_ATTACH:
#if !DISABLE_GAME_PATCHES
        removeGameGuard();
        overwriteWindowTitle();
        installOnLoadHook();
        loadHooks();
        ApplyInitialUIPatches();

    #ifndef DEBUG
        LoadAntihack();
    #else
        allowMulticlienting();
    #endif

    #ifdef WITH_SEX
        Sex_Init();
    #endif
#else
        (void)module;
        (void)reserved;
#endif
        break;
    }
    return TRUE;
}
