#pragma once

#define g_ConfigWindowedMode    (*(int*)0xa7efd0)

#define g_ConfigMacroF5         ((char*)0xa90838)
#define g_ConfigMacroF6         ((char*)0xa90869)
#define g_ConfigMacroF7         ((char*)0xa9089a)
#define g_ConfigMacroF8         ((char*)0xa908cb)

#define g_ConfigWindowWidth     (*(int*)0xa94e78)
#define g_ConfigWindowHeight    (*(int*)0xa94e7c)
#define g_ConfigMusicEnabled    (*(int*)0xa94e80)
#define g_ConfigSoundEnabled    (*(int*)0xa94e84)
#define g_ConfigViewHelp        (*(int*)0xa94e88)
#define g_ConfigFXQuality       (*(int*)0xa94e8c)
#define g_ConfigTexQuality      (*(int*)0xa94e90)
#define g_UIButtonGraphicsState (*(int*)0xa94e94)
#define g_ConfigKeyUp           (*(int*)0xa94e98)
#define g_ConfigKeyDown         (*(int*)0xa94e9c)
#define g_ConfigKeyLeft         (*(int*)0xa94ea0)
#define g_ConfigKeyRight        (*(int*)0xa94ea4)
#define g_ConfigKeyAttack       (*(int*)0xa94ea8)
#define g_ConfigKeyJump         (*(int*)0xa94eac)
#define g_ConfigKeyDefend       (*(int*)0xa94eb0)
#define g_ConfigKeyTrans        (*(int*)0xa94eb4)
#define g_ConfigKeySkill1       (*(int*)0xa94eb8)
#define g_ConfigKeySkill2       (*(int*)0xa94ebc)
#define g_ConfigKeySkill3       (*(int*)0xa94ec0)
#define g_ConfigObserver        (*(int*)0xa94ec4)
#define g_ConfigPreventAutoban  (*(int*)0xa94ec8)
#define g_ConfigSpecialText     (*(int*)0xa94ecc)
#define g_ConfigDebugTextActive (*(int*)0xa94ed0)
#define g_ConfigAutoReady       (*(int*)0xa94ed4)
//#define g_ConfigHelp            (*(int*)0xa94f0c)

void Config_Load();
void Config_Write();