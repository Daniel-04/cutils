#ifndef ERROR_H_
#define ERROR_H_

#include "defs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define panic(reason_fmt, ...)                                                \
  (fprintf (stderr, "%s:%u: Panic: " reason_fmt "\n", __FILE__,               \
            (u32)__LINE__, ##__VA_ARGS__),                                    \
   abort ())

#define panic_fl(file, line, reason_fmt, ...)                                 \
  (fprintf (stderr, "%s:%u: Panic: " reason_fmt "\n", file, line,             \
            ##__VA_ARGS__),                                                   \
   abort ())

#endif // ERROR_H_
