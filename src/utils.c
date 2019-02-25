#include <stdlib.h>
#include <stdarg.h>
#include "log.h"
#include "utils.h"

void die(char* fstring, ...)
{
    va_list args;
    va_start(args, fstring);
    log_fatal(fstring, args);
    va_end(args);
    exit(1);
}
