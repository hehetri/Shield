#include "main.h"
#include "config.h"
#include "ui/ui.h"

// #define g_DerivedMouseX() // [g_GameClassHandle]+0x5D4
// #define g_DerivedMouseY() // [g_GameClassHandle]+0x5DC

int Window_Init(HINSTANCE instance, int cmdShow, HWND* pWindow, HACCEL* pAccel) {
    // create window class
    HICON icon = LoadIconA(instance, 107);
    WNDCLASSEX wndclass;
    wndclass.cbSize        = sizeof(wndclass);
    wndclass.lpszClassName = WINDOW_TITLE;
    wndclass.lpfnWndProc   = (WNDPROC)0x403B0C;
    wndclass.style         = 0; // no style flags
    wndclass.hInstance     = instance;
    wndclass.hIcon         = icon;
    wndclass.hIconSm       = icon;
    wndclass.hCursor       = LoadCursorA(NULL, IDC_ARROW);
    wndclass.hbrBackground = COLOR_WINDOWFRAME;
    wndclass.lpszMenuName  = NULL;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    if (!RegisterClassExA(&wndclass))
        return E_FAIL;

    // load accelerator
    *pAccel = LoadAcceleratorsA(instance, 109);

    // create window
    int wndTotalWidth  = g_ConfigWindowWidth  + 2 * GetSystemMetrics(SM_CXSIZEFRAME);
    int wndTotalHeight = g_ConfigWindowHeight + 2 * GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYCAPTION);
    HWND wnd = CreateWindowExA(
        WS_EX_LEFT,
        WINDOW_TITLE,
        WINDOW_TITLE,
        (~(g_ConfigWindowedMode)+1) & WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        wndTotalWidth,
        wndTotalHeight,
        NULL,
        NULL,
        instance,
        NULL);
    if (!wnd)
        return E_FAIL;
    ShowWindow(wnd, cmdShow);
    UpdateWindow(wnd);
    ShowCursor(0);
    *pWindow = wnd;

    return 0;
}

