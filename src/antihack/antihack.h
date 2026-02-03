#pragma once
#include "antihack/sex.h"

#define COULD_BE_FALSE_FLAG 0
#define OBVIOUSLY_A_HACK 1

void LoadAntihack();
void ReportHack(int level);

void InitScanProtection();
void TickScanProtection();

void PreventDebugging();