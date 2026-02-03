#ifdef WITH_60FPS
#include <Windows.h>
#include "main.h"
#include "60fps/60fps.h"

#define FPS_TICK_MS 16 /*60FPS hack*/

static int g_clock_initialized = 0;

void Clock_Init60FPS() {
    int32 now = timeGetTime();
    g_MsTickDesired = FPS_TICK_MS;
    g_MsOld = now;
    g_MsLastTick = now;
    g_MsLastTickSecond = now;
    g_OverflowFrames = 0;
    g_FPS = 0;
    g_FrameCounter = 0;
    g_FrameWasTickSecond = 0;
    g_clock_initialized = 1;
}

int Clock_CalculateTickDelta() {
    if (!g_clock_initialized) {
        Clock_Init60FPS();
    }
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
