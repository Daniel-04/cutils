#include "error.h"

Except_Frame *Except_stack = NULL;

void
Except_raise (const Except_T *e, const char *file, u32 line)
{
  Except_Frame *p = Except_stack;

  if (!e)
    {
      fprintf (stderr, "Uncaught exception: <null>\n");
      abort ();
    }

  if (!p)
    {
      fprintf (stderr, "Uncaught exception: %s",
               e->reason ? e->reason : "unknown");
      if (file && line > 0)
        fprintf (stderr, " raised at %s:%u", file, line);
      fprintf (stderr, "\n");
      fflush (stderr);
      abort ();
    }

  p->exception = e;
  Except_stack = Except_stack->prev;
  longjmp (p->env, Except_raised);
}
