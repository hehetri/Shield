#include "main.h"
#include "antihack/antihack.h"
#include <psapi.h>

/**
 * Here Cheat Engine scanning is prevented.
**/

static DWORD s_VirtualAddress;
static HANDLE s_GameProcess;



/**
 * Allocates non-physically backed memory.
**/
void InitScanProtection() {
    s_GameProcess = GetCurrentProcess();
    s_VirtualAddress = VirtualAlloc(0, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

/**
 * So, we have a block of virtual memory, which will not be allocated until it
 * is accessed, and when is it accessed? Through a cheat engine scan!
 * Once allocated, it is not virtual memory anymore therefore they tried to hax.
**/
void TickScanProtection() {
    // Usually performed in some detection thread
    PSAPI_WORKING_SET_EX_INFORMATION info = {0};
    info.VirtualAddress = s_VirtualAddress;

    // Check if our own non-physically backed memory is valid
    BOOL result = QueryWorkingSetEx(
        s_GameProcess,
        &info,
        sizeof(PSAPI_WORKING_SET_EX_INFORMATION));
    if (!result) return; // error

    // Check if a scan was performed
    if (info.VirtualAttributes.Valid)
        ReportHack(OBVIOUSLY_A_HACK); 
}
