#include "main.h"
#include "d3d/direct3d.h"

// First function ptr is at: [  [[g_PDirect3D]+4]  ]+0

int8 g_HookCode[D3D9_DEVICE_FUNCTION_COUNT * 5];

void D3DHook_Init() {
    asm volatile("movl %0, %%ecx" ::"g"(g_Direct3D));
    LPDIRECT3DDEVICE9 pDevice = CDirect3D_GetDevice();
    printf("%p\n", ReadInt32(pDevice, 0));

    DWORD oldProtection;
    VirtualProtect(g_HookCode, sizeof(g_HookCode), PAGE_READWRITE, &oldProtection);
    for (int i = 0; i < D3D9_DEVICE_FUNCTION_COUNT; i++) {
        WriteJMP( g_HookCode + (i * 5), ReadInt32(ReadInt32(pDevice, 0), 4 * i) );
        WriteInt32( ReadInt32(pDevice, 0) + 4 * i, g_HookCode + (i * 5) );
        // @TODO: Hook at the right time
    }
    VirtualProtect(g_HookCode, sizeof(g_HookCode), PAGE_EXECUTE, &oldProtection);
}