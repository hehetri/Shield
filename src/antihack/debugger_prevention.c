#include "main.h"
#include "antihack/antihack.h"


static LONG WINAPI exceptionHandlerZeroDivide(PEXCEPTION_POINTERS pExceptions) {
    // restore old unhandled exception filter
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)
        pExceptions->ContextRecord->Eax);
    // skip exception code
    pExceptions->ContextRecord->Eip += 2;
    return EXCEPTION_CONTINUE_EXECUTION;
}

static LONG WINAPI exceptionHandlerVectoredAntiVEH(PEXCEPTION_POINTERS pExceptions) {
    if (pExceptions->ExceptionRecord->ExceptionCode != EXCEPTION_BREAKPOINT) {
        ReportHack(OBVIOUSLY_A_HACK); 
    }
    pExceptions->ContextRecord->Eip += 1;
    return EXCEPTION_CONTINUE_EXECUTION;
}

static void detectDebuggerVEH() {
    PVOID h = AddVectoredExceptionHandler(0, exceptionHandlerVectoredAntiVEH);
    asm volatile("int3");
    RemoveVectoredExceptionHandler(h);
}

static void causeUnhandledException() {
    SetUnhandledExceptionFilter(exceptionHandlerZeroDivide);
    asm volatile("xor %eax, %eax");
    asm volatile("div %eax");
}

static int8 detectDebuggerFromPEB() {
    int8 beingDebugged;
    asm volatile("movl %fs:0x18, %eax");                // eax = TEB
    asm volatile("movl 0x30(%eax), %eax");              // eax = PEB
    asm volatile("movb 0x02(%eax), %al");               // al = eax+0x02
    asm volatile("movb %%al, %0" :"=r"(beingDebugged)); // beingDebugged = al
    if (beingDebugged) {
        ReportHack(OBVIOUSLY_A_HACK);
    }
}



void PreventDebugging() {
    detectDebuggerFromPEB();
    detectDebuggerVEH();
    causeUnhandledException(); // @TODO: this last resort might have to be put somewhere else
}
