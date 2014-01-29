#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "test-utils.hpp"

static void _v2print(const char* prefix, const char* filen, int linen,
                     const char* fmt, const char* func, va_list marker)
{
  fprintf(stderr, prefix, filen, linen);

  if(func) {
    fwrite(func, 1, strlen(func), stderr);
    fwrite(" - ", 1, 3, stderr);
  }

  vfprintf(stderr, fmt, marker);
  fprintf(stderr, "\n");
}

void test_print(const char *fmt, const char* func, const char* filen,
               int linen, ...)
{
#define ERROR_MSG "TEST %s:%d: "
  va_list marker;

  va_start(marker, linen);
  _v2print(ERROR_MSG, filen, linen, fmt, func, marker);

  va_end(marker);

#undef ERROR_MSG
}


