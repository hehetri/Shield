#ifdef WITH_60FPS
#include <Windows.h>
#include "main.h"
#include "60fps/60fps.h"

#undef g_MsTickDesired
#define g_MsTickDesired 16 /*60FPS hack*/

int Clock_CalculateTickDelta() {
    int32 msOld = g_MsOld;
    int32 msNow = timeGetTime();
    if ((msNow - msOld) > 1000) {
        g_MsOld = msNow;
        g_FPS = g_FrameCounter;
        g_FrameCounter = 0;
    }
    int32 msTick = msNow - g_MsLastTick;
    g_OverflowFrames = 0;
    if (msTick > g_MsTickDesired) {
        g_FrameCounter++;
        g_OverflowFrames = msTick / g_MsTickDesired;
        g_MsLastTick += g_OverflowFrames * g_MsTickDesired;
        g_FrameWasTickSecond = 0;
        if (msNow - g_MsLastTickSecond > 1000) {
            g_MsLastTickSecond = msNow;
            g_FrameWasTickSecond = 1;
        }
        return 1;
    }
    return 0;
}

#endif