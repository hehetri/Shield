#pragma once
#ifdef WITH_60FPS

#define g_MsLastTick         (*(int32*)0xa92e28)
#define g_OverflowFrames     (*(int32*)0xa92e2c)
#define g_MsTickDesired      (*(int32*)0xa92e30)
#define g_MsOld              (*(int32*)0xa92e34)
#define g_FPS                (*(int32*)0xa92e38)
#define g_FrameCounter       (*(int32*)0xa92e3c)
#define g_FrameWasTickSecond (*(int32*)0xa92e40)
#define g_MsLastTickSecond   (*(int32*)0xa92e44)

int Clock_CalculateTickDelta();

#endif