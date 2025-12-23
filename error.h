#ifndef ERROR_H_
#define ERROR_H_

#include "defs.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Except_T
{
  const char *reason;
} Except_T;

typedef struct Except_Frame
{
  struct Except_Frame *prev;
  jmp_buf env;
  const Except_T *exception;
} Except_Frame;

enum
{
  Except_entered = 0,
  Except_raised
};

extern Except_Frame *Except_stack;

void Except_raise (const Except_T *e, const char *file, u32 line);

#ifndef assert
#ifdef NDEBUG
#define assert(e) ((void)(0))
#else
#define assert(e)                                                             \
  ((void)((e)                                                                 \
          || (fprintf (stderr, "%s:%u: Assertion failed: %s\n", __FILE__,     \
                       (u32)__LINE__, #e),                                    \
              abort (), 0)))
#endif
#endif

#define RAISE(e) Except_raise (&(e), __FILE__, __LINE__)

#define TRY                                                                   \
  do                                                                          \
    {                                                                         \
      volatile u32 Except_flag;                                               \
      Except_Frame Except_frame;                                              \
      Except_stack = &Except_frame;                                           \
      Except_flag = setjmp (Except_frame.env);                                \
      if (Except_flag == Except_entered)                                      \
        {

#define EXCEPT(e)                                                             \
  Except_stack = Except_stack->prev;                                          \
  }                                                                           \
  else if (Except_frame.exception == &(e))                                    \
  {                                                                           \
    const Except_T *e = Except_frame.exception;

#define ELSE                                                                  \
  Except_stack = Except_stack->prev;                                          \
  }                                                                           \
  else                                                                        \
  {

#define END_TRY                                                               \
  }                                                                           \
  }                                                                           \
  while (0)

#endif // ERROR_H_
