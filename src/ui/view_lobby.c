#include "main.h"
#include "ui/ui.h"
#include "d3d/direct3d.h"

/**
 * Honestly I am so sorry for writing this code, but I have no idea how to do it
 * in a cleaner way because I haven't figured out enough about these classes in
 * order to make structs for them.
**/
#define g_pViewLobby ReadInt32(g_pViewMan, 0x970) /* [[0x00A96A1C]+0x970] */
#define g_pViewLobby_pSomething (g_pViewLobby + 0xC)  /* [[0x00A96A1C]+0x970]+0xC */



/*******************************************************************************
 * Chat
 ******************************************************************************/
static void moveChat() {
    int32 chat = (g_pViewLobby_pSomething + 0x4); // [[0x00A96A1C]+0x970]+0xC+0x4

    // Chat input collision rect
    RECT* chatRect = g_pViewLobby + 0x27C; // [[0x00A96A1C]+0x970]+0x27C
    chatRect->left = 272;
    chatRect->top = 571;
    chatRect->right = 653;
    chatRect->bottom = 590;

}




void __stdcall CViewLobby_Create() {
    // Execute CViewLobby::Create
    asm volatile("call 0x00502490");
}

void __stdcall CViewLobby_Prepare() {
    moveChat();
}


void __stdcall CViewLobby_ApplyInitialUIPatches() {
    char patchRectOne[] = { 0x68, 0x57, 0x02, 0x00, 0x00, 0x68, 0x1F, 0x03, 0x00, 0x00, 0x6A, 0x00, 0x6A, 0x00 };
    char patchRectTwo[] = { 0x68, 0x57, 0x02, 0x00, 0x00, 0x68, 0x1F, 0x03, 0x00, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x90, 0x90, 0x90 };
    char patchRectThree[] = { 0x68, 0x57, 0x02, 0x00, 0x00, 0x68, 0x1F, 0x03, 0x00, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x90, 0x90, 0x90 };
    char patchRectFour[] = { 0x68, 0x57, 0x02, 0x00, 0x00, 0x68, 0x1F, 0x03, 0x00, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
    char patchRectGamemodeTabs[] = {
        0x6A, 0x39, 0x68, 0x4D, 0x02, 0x00, 0x00, 0x6A, 0x00, 0x68, 0xC6, 0x00, 0x00, 0x00, 0x90, 0x90,
        0x90, 0x90, 0x90, 0x90, 0x90, 0x8D, 0x45, 0xEC, 0x50, 0xFF, 0x15, 0x00, 0xA2, 0xBD, 0x00
    };
    char patchRectPlayerTabs[] = {
        0x68, 0x1B, 0x01, 0x00, 0x00, 0x68, 0x9B, 0x00, 0x00, 0x00, 0x68, 0x05, 0x01, 0x00, 0x00, 0x6A,
        0x5A
    };

    UnprotectedMemcpy(0x0051C81F, patchRectOne, sizeof(patchRectOne)); // option box
    UnprotectedMemcpy(0x0053D295, patchRectThree, sizeof(patchRectThree)); // view player box
    UnprotectedMemcpy(0x00517AAF, patchRectOne, sizeof(patchRectOne)); // mail
    UnprotectedMemcpy(0x004F226F, patchRectOne, sizeof(patchRectOne)); // my gifts
    UnprotectedMemcpy(0x00504FBD, patchRectTwo, sizeof(patchRectTwo)); // draw help
    UnprotectedMemcpy(0x004EE5AF, patchRectOne, sizeof(patchRectOne)); // ranked popup
    UnprotectedMemcpy(0x0051FA2F, patchRectThree, sizeof(patchRectThree)); // events popup
    UnprotectedMemcpy(0x004EC14F, patchRectFour, sizeof(patchRectFour)); // trade popup
    UnprotectedMemcpy(0x0053B57F, patchRectOne, sizeof(patchRectOne)); // market popup
    UnprotectedMemcpy(0x00505D5F, patchRectFour, sizeof(patchRectFour)); // create room popup
    UnprotectedMemcpy(0x004F0BDF, patchRectTwo, sizeof(patchRectTwo)); // send gift
    UnprotectedMemcpy(0x00504B0F, patchRectGamemodeTabs, sizeof(patchRectGamemodeTabs)); // gamemode tabs
    UnprotectedMemcpy(0x00504AC3, patchRectPlayerTabs, sizeof(patchRectPlayerTabs)); // player friends guild tabs
    UnprotectedMemcpy(0x004EC8BF, patchRectFour, sizeof(patchRectFour)); // guild create msg
    UnprotectedMemcpy(0x004EB60F, patchRectThree, sizeof(patchRectThree)); // guild accept decline msg
    UnprotectedMemcpy(0x004ECF3F, patchRectFour, sizeof(patchRectFour)); // confirm quit guild
    UnprotectedMemcpy(0x004EA215, patchRectTwo, sizeof(patchRectTwo)); // guild info msg
    UnprotectedMemcpy(0x005175BF, patchRectFour, sizeof(patchRectFour)); // send mail msg




}