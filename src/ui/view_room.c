#include "main.h"
#include "ui/ui.h"

#define g_pViewRoom ReadInt32(g_pViewMan, 0x974) /* [[0x00A96A1C]+0x974] */
#define g_pViewCurrent ReadInt32(0x00A96CA0, 0) // g_SysViewCurrent


void CViewRoom_ApplyInitialUIPatches() {
    // Minimap
    char minimapRect[] = {
        0x68, 0xBE, 0x01, 0x00, 0x00, 0x68, 0x1F, 0x03, 0x00, 0x00, 0x68, 0x59, 0x01, 0x00, 0x00, 0x90,
        0x90, 0x90, 0x6A, 0x00
    };
    UnprotectedMemcpy(0x004E23A7, minimapRect, sizeof(minimapRect));

}

/**
 * When ending the game then this function is called twice.
**/
void CViewRoom_Prepare() {
    CUI_TryReturnToLobbyByEsc();
    // printf("conditions: %i %i %i\n",
    //     (10 == g_pViewCurrent),
    //     (1 == ReadInt32(0x00B17DBC, 0)),
    //     (0 != g_pViewMan)
    // );
    if ((10 == g_pViewCurrent) && (1 == ReadInt32(0x00B17DBC, 0) && 0 != g_pViewMan)) {
        RECT* chatRect = g_pViewRoom + 0x23A0 + 0x270; // [[0x00A96A1C]+0x974] + 0x23A0 + 0x270
        chatRect->left = 272;
        chatRect->top = 571;
        chatRect->right = 653;
        chatRect->bottom = 590;
        return;
    }
}