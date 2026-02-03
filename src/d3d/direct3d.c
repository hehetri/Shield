#include "main.h"
#include "d3d/direct3d.h"
#include <d3d9.h>

/**
 * This is the Direct3D class from Bout. 
**/

typedef void CDirect3D;
typedef int32 CFont;
typedef void (*FP_DRAW_TEXT)(CFont*, HDC, const char*, int32, LPRECT, int32, void*);



int __stdcall CDirect3D_Create() {
    THISCALL_ENTER(LPDIRECT3D9);
    *this = Direct3DCreate9(D3D_SDK_VERSION);
    if (!*this) {
        MessageBoxA(NULL, "Failed to initialize graphics.", "Error", NULL);
        #ifdef DEBUG
        puts("[ERROR] Direct3D failed to initialize.");
        #endif
        ExitProcess(0);
        return E_FAIL;
    }

    int result;
    //createDevice(this);
    // @TODO: call actual function (create device)
    asm         ("movl %0, %%ecx" ::"g"(this));
    asm volatile("call 0x4048A9");
    asm         ("movl %%eax, %0" :"=r"(result));
    if (result < 0) return E_FAIL;
    return 0;
}

LPDIRECT3DDEVICE9 __stdcall CDirect3D_GetDevice() {
    THISCALL_ENTER(LPDIRECT3D9);
    return ReadInt32(ReadInt32(g_Direct3D, 0), 4);
}


void __stdcall CDirect3D_DrawText(int32 x, int32 y, int32 colorRGB, const char* lpChText) {
    THISCALL_ENTER(CDirect3D);
    if (ReadInt32(this, 0x670) == 2) // do not draw
        return;
    RECT rect;
    SetRect(&rect, x,y, x+981,y+30);
    // SetRect(&rect, x,y, x+200,y+20);

    CFont* pFont = ReadInt32(this, 0x674);
    FP_DRAW_TEXT drawTextPtr = ReadInt32(*pFont, 0x30); // todo, dereference
    drawTextPtr(
        pFont,
        NULL, // hdc
        lpChText, // lpchtext
        -1, // null terminated string
        &rect,
        100, // DT_NOCLIP, // format, was int 100 instead of 0x100 accidentally
        colorRGB // margins and tab lengths
    );
}

void __stdcall CDirect3D_DrawTextCustom(int32 x, int32 y, int32 colorRGB, const char* lpChText, UINT format, int maxWidth) {
    THISCALL_ENTER(CDirect3D);
    if (ReadInt32(this, 0x670) == 2) // do not draw
        return;
    RECT rect;
    SetRect(&rect, x,y, x + maxWidth,y+30);

    CFont* pFont = ReadInt32(this, 0x674);
    FP_DRAW_TEXT drawTextPtr = ReadInt32(*pFont, 0x30); // todo, dereference
    drawTextPtr(
        pFont,
        NULL, // hdc
        lpChText, // lpchtext
        -1, // null terminated string
        &rect,
        format, // format
        colorRGB // margins and tab lengths
    );
}


