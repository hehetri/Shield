#include "main.h"
#include "ui/ui.h"

#define g_pViewCurrent ReadInt32(0x00A96CA0, 0) // g_SysViewCurrent

/**
 * Forces Room/Battle -> Lobby when ESC is pressed.
 *
 * View ids in this client:
 * 9: lobby
 * 10: room
 * 11: battle
**/
void CUI_TryReturnToLobbyByEsc(void) {
    static int8 wasEscPressed = 0;

    int8 isEscPressed = (GetAsyncKeyState(VK_ESCAPE) & 0x8000) ? 1 : 0;
    if (!isEscPressed) {
        wasEscPressed = 0;
        return;
    }

    if (wasEscPressed)
        return;
    wasEscPressed = 1;

    int32 view = g_pViewCurrent;
    if (view != 10 && view != 11)
        return;

    // Ask the client to go back to lobby by flipping the current view id.
    // The engine view loop will process this transition.
    WriteInt32(0x00A96CA0, 9);
}

