#include "main.h"
#include "config.h"
#include "ui/ui.h"

static void patchFont();
static void patchScalingCode();


static void patchFont() {
    wcscpy(((wchar_t*)0x009CE0A0), L"Consolas"); // default is Courier New
    char widthByte = 15; // letter width, default is 16
    UnprotectedMemcpy(0x0044CFC8, &widthByte, 1);
    UnprotectedMemcpy(0x0044D8DB, &widthByte, 1);
    UnprotectedMemcpy(0x0044EA68, &widthByte, 1);
}

// /**
//  * There is a spooky error in the image loader that we can just bypass.
// **/
// static void bypassImageSizeCutTooBigError() {
//     // 00416ACB | E9 C0000000            | jmp bout.416B90
//     // 00416AD0 | 90                     | nop
//     DWORD oldProtection;
//     VirtualProtect(0x00416ACB, 10, PAGE_EXECUTE_READWRITE, &oldProtection);
//     WriteInt8(0x00416ACB, 0xE9);
//     WriteInt32(0x00416ACC, 0x000000C0);
//     WriteInt8(0x00416AD0, 0x90);
//     VirtualProtect(0x00416ACB, 10, oldProtection, &oldProtection);
// }



static void changeCaratBlinkTime() {
    // Make the blink rate so that it's visible longer
    char bytesBlink[] = { 0x81, 0xFA, 0x88, 0x00, 0x00, 0x00 }; // cmp edx, 88h
    UnprotectedMemcpy(0x0041551A, bytesBlink, sizeof(bytesBlink));
}




void ApplyInitialUIPatches() {

    // bypassImageSizeCutTooBigError();
    patchFont();
    changeCaratBlinkTime();
    CViewLogin_ApplyInitialPatches();
    CViewLobby_ApplyInitialUIPatches();
    CViewShop_ApplyInitialUIPatches();
    CMyInfo_ApplyInitialUIPatches();
    CViewRoom_ApplyInitialUIPatches();

}