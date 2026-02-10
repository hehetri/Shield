#include "main.h"
#include "ui/ui.h"
#ifdef WITH_SEX
#include "antihack/sex.h"
#endif

void __stdcall CViewBattle_Prepare() {

    CUI_TryReturnToLobbyByEsc();

    const void* pUI = 0x00A96A20;
    RECT* pInputRect = (RECT*)(ReadInt32(pUI, 0) + 0x404); // [g_pDungeonPlay]+0x404
    pInputRect->left = 275;
    pInputRect->top  = 581;
    pInputRect->right = 600;
    pInputRect->bottom = 596;

    RECT* pWhisperRect = (RECT*)(ReadInt32(pUI, 0) + 0x9ec); // [g_pDungeonPlay]+0x9ec
    pWhisperRect->left = 199;
    pWhisperRect->top = 580;
    pWhisperRect->right = 271;
    pWhisperRect->bottom = 597;

    const void* pHud = 0x00BC71C8;
    RECT* pGaugeFrameRect = (RECT*)(ReadInt32(pHud, 0) + 0x54C); // [g_pHud]+0x54C
    pGaugeFrameRect->left = 0;
    pGaugeFrameRect->top = 0;
    pGaugeFrameRect->right = 799;
    pGaugeFrameRect->bottom = 599;

    RECT* pHelp = (RECT*)(ReadInt32(pHud, 0) + 0x69C); // [g_pHud]+0x69C
    pHelp->left = 0;
    pHelp->top = 0;
    pHelp->right = 799;
    pHelp->bottom = 599;
    

#ifdef WITH_SEX
    Sex_PrepareForBattle();
#endif

}
