#include <stdarg.h>
#include <stdio.h>

int __mingw_vprintf(const char *format, va_list args) {
    return vprintf(format, args);
}

int __mingw_printf(const char *format, ...) {
    int result;
    va_list args;

    va_start(args, format);
    result = __mingw_vprintf(format, args);
    va_end(args);

    return result;
}
