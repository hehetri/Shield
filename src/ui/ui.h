#pragma once
#include "main.h"

/* Globals */
#define g_pViewMan ReadInt32(0x00A96A1C, 0)

/* Window */
#define WINDOW_TITLE ((const char*)0x009CD328)
int Window_Init(HINSTANCE instance, int cmdShow, HWND* pWindow, HACCEL* pAccel);

/* UI Core */
void ApplyInitialUIPatches(void);
void PatchScalingCode(void);

/* Views */
void CViewLogin_ApplyInitialPatches(void);
void CMyInfo_ApplyInitialUIPatches(void);

/* Navigation */
void CUI_TryReturnToLobbyByEsc(void);
void CUI_HandleGlobalHotkeys(WPARAM wParam);

/* Lobby */
void __stdcall CViewLobby_ApplyInitialUIPatches(void);
void __stdcall CViewLobby_Create(void);
void __stdcall CViewLobby_Prepare(void);
void __stdcall CViewLobby_DrawRoomName(
    int32 x, int32 y, LPDRAWTEXTPARAMS lpDrawTextParams, const char* lpChText
);
void __stdcall CViewLobby_DrawRoomLevel(
    int32 x, int32 y, LPDRAWTEXTPARAMS lpDrawTextParams, const char* lpChText
);
void __stdcall CViewLobby_DrawPlayerName(
    int32 x, int32 y, LPDRAWTEXTPARAMS lpDrawTextParams, const char* lpChText
);
void __stdcall CViewLobby_DrawWhisperListText(
    int32 x, int32 y, LPDRAWTEXTPARAMS lpDrawTextParams, const char* lpChText
);

/* Room */
void CViewRoom_ApplyInitialUIPatches(void);
void CViewRoom_Prepare(void);

/* Shop */
void CViewShop_ApplyInitialUIPatches(void);

/* Battle */
void __stdcall CViewBattle_Prepare(void);
