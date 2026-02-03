#include <stdarg.h>
#include <stdio.h>

int __mingw_printf(const char *format, ...) {
    int result;
    va_list args;

    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);

    return result;
}
