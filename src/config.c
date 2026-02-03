#include "main.h"
#include "config.h"
#include <dinput.h>
#include <string.h>
#include <stdio.h>



#define CONFIG_FILE_SIZE 264



void Config_LoadDefaults() {
    g_ConfigWindowedMode    = 1;
    strcpy(g_ConfigMacroF5, "Please ready.");
    strcpy(g_ConfigMacroF6, "lololol");
    strcpy(g_ConfigMacroF7, "Suicide or kick");
    strcpy(g_ConfigMacroF8, "RB Plz");
    g_ConfigWindowWidth     = 1200;
    g_ConfigWindowHeight    = 800;
    g_ConfigMusicEnabled    = 1;
    g_ConfigSoundEnabled    = 1;
    g_ConfigViewHelp        = 1;
    g_ConfigFXQuality       = 0;
    g_ConfigTexQuality      = 1;
    g_UIButtonGraphicsState = 0;
    g_ConfigKeyUp           = DIK_UP;
    g_ConfigKeyDown         = DIK_DOWN;
    g_ConfigKeyLeft         = DIK_LEFT;
    g_ConfigKeyRight        = DIK_RIGHT;
    g_ConfigKeyAttack       = DIK_V;
    g_ConfigKeyJump         = DIK_C;
    g_ConfigKeyDefend       = DIK_X;
    g_ConfigKeyTrans        = DIK_Z;
    g_ConfigKeySkill1       = DIK_A;
    g_ConfigKeySkill2       = DIK_S;
    g_ConfigKeySkill3       = DIK_D;
    g_ConfigObserver        = 0;
    g_ConfigPreventAutoban  = 0;
    g_ConfigSpecialText     = 0;
    g_ConfigDebugTextActive = 0;
    g_ConfigAutoReady       = 0;
}

void Config_LoadRemainingDefaults() {
    g_ConfigFXQuality       = 0;
    g_ConfigTexQuality      = 1;
    g_ConfigObserver        = 0;
    g_ConfigPreventAutoban  = 0;
    g_ConfigSpecialText     = 0;
    g_ConfigDebugTextActive = 0;
    g_ConfigAutoReady       = 0;
}

/* Config file data:
 * 0x00  - Window Width
 * 0x04  - Window Height
 * 0x08  - Windowed Mode
 * 0x0C  - SFX Enabled
 * 0x10  - Music Enabled
 * 0x14  - Key up
 * 0x18  - Key down
 * 0x1C  - Key left
 * 0x20  - Key right
 * 0x24  - Key attack
 * 0x28  - Key jump
 * 0x2C  - Key defend
 * 0x30  - Key trans
 * 0x34  - Key skill 1
 * 0x38  - Key skill 2
 * 0x3C  - Key skill 3
 * 0x40  - Macro F5
 * 0x71  - Macro F6
 * 0xA2  - Macro F7
 * 0xD3  - Macro F8
 * 0x104 - Whether the player should view help
**/

void Config_Load() {
    // Try to open the config file handle
    FILE* file = fopen("config.dat", "rb");
    if (!file) {
        Config_LoadDefaults();
        return;
    }

    // Read the config file and close it's handle
    char buffer[CONFIG_FILE_SIZE];
    fread(buffer, CONFIG_FILE_SIZE, 1, file);
    g_ConfigWindowWidth  = ReadInt32(buffer, 0x00);
    g_ConfigWindowHeight = ReadInt32(buffer, 0x04);
    g_ConfigWindowedMode = ReadInt32(buffer, 0x08);
    g_ConfigSoundEnabled = ReadInt32(buffer, 0x0C);
    g_ConfigMusicEnabled = ReadInt32(buffer, 0x10);
    g_ConfigKeyUp        = ReadInt32(buffer, 0x14);
    g_ConfigKeyDown      = ReadInt32(buffer, 0x18);
    g_ConfigKeyLeft      = ReadInt32(buffer, 0x1C);
    g_ConfigKeyRight     = ReadInt32(buffer, 0x20);
    g_ConfigKeyAttack    = ReadInt32(buffer, 0x24);
    g_ConfigKeyJump      = ReadInt32(buffer, 0x28);
    g_ConfigKeyDefend    = ReadInt32(buffer, 0x2C);
    g_ConfigKeyTrans     = ReadInt32(buffer, 0x30);
    g_ConfigKeySkill1    = ReadInt32(buffer, 0x34);
    g_ConfigKeySkill2    = ReadInt32(buffer, 0x38);
    g_ConfigKeySkill3    = ReadInt32(buffer, 0x3C);
    g_ConfigViewHelp     = ReadInt32(buffer, 0x104);
    strcpy(g_ConfigMacroF5, buffer+0x40);
    strcpy(g_ConfigMacroF6, buffer+0x71);
    strcpy(g_ConfigMacroF7, buffer+0xA2);
    strcpy(g_ConfigMacroF8, buffer+0xD3);
    fclose(file);

    // Load the values that were not part of the config file
    Config_LoadRemainingDefaults();
    // Config_LoadDefaults();
    // Config_Write();
}

void Config_Write() {
    FILE* file = fopen("config.dat", "wb");
    if (!file) return; // @TODO: log an error

    char buffer[CONFIG_FILE_SIZE];
    WriteInt32ToBuffer(buffer, 0x00 , g_ConfigWindowWidth);
    WriteInt32ToBuffer(buffer, 0x04 , g_ConfigWindowHeight);
    WriteInt32ToBuffer(buffer, 0x08 , g_ConfigWindowedMode);
    WriteInt32ToBuffer(buffer, 0x0C , g_ConfigSoundEnabled);
    WriteInt32ToBuffer(buffer, 0x10 , g_ConfigMusicEnabled);
    WriteInt32ToBuffer(buffer, 0x14 , g_ConfigKeyUp);
    WriteInt32ToBuffer(buffer, 0x18 , g_ConfigKeyDown);
    WriteInt32ToBuffer(buffer, 0x1C , g_ConfigKeyLeft);
    WriteInt32ToBuffer(buffer, 0x20 , g_ConfigKeyRight);
    WriteInt32ToBuffer(buffer, 0x24 , g_ConfigKeyAttack);
    WriteInt32ToBuffer(buffer, 0x28 , g_ConfigKeyJump);
    WriteInt32ToBuffer(buffer, 0x2C , g_ConfigKeyDefend);
    WriteInt32ToBuffer(buffer, 0x30 , g_ConfigKeyTrans);
    WriteInt32ToBuffer(buffer, 0x34 , g_ConfigKeySkill1);
    WriteInt32ToBuffer(buffer, 0x38 , g_ConfigKeySkill2);
    WriteInt32ToBuffer(buffer, 0x3C , g_ConfigKeySkill3);
    WriteInt32ToBuffer(buffer, 0x104, g_ConfigViewHelp);
    memcpy(buffer+0x40, g_ConfigMacroF5, 49);
    memcpy(buffer+0x71, g_ConfigMacroF6, 49);
    memcpy(buffer+0xA2, g_ConfigMacroF7, 49);
    memcpy(buffer+0xD3, g_ConfigMacroF8, 49);
    fwrite(buffer, CONFIG_FILE_SIZE, 1, file);

    fclose(file);
}
