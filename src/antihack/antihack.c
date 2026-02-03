#include "main.h"
#include "antihack/antihack.h"

static void tickAntihack() {
    TickScanProtection();
    PreventDebugging();
}

void LoadAntihack() {
    InitScanProtection();
    WriteToJumpTable(0x004048F9, tickAntihack);
}

void ReportHack(int level) {
    if (level == OBVIOUSLY_A_HACK) {
        MessageBoxA(NULL, "You tried to hack bitch!", "It's fairly obvious too", MB_OK | MB_SETFOREGROUND);
    } else {
        MessageBoxA(NULL, "You tried to hack bitch!", "Could be false flag though", MB_OK | MB_SETFOREGROUND);
    }
    #ifndef DEBUG
    // @TODO: Obfuscated quit game function
    #endif
}