#ifndef MEM_H_
#define MEM_H_

#include "defs.h"
#include "error.h"
#include <stdlib.h>

static const Except_T Mem_Failed = { "Memory allocation failed" };

static inline void *Mem_alloc (size_t nbytes, const char *file, u32 line);
static inline void *Mem_calloc (size_t count, size_t nbytes, const char *file,
                                u32 line);
static inline void Mem_free (void **ptr, const char *file, u32 line);
static inline void *Mem_resize (void *ptr, size_t nbytes, const char *file,
                                u32 line);

#define ALLOC(nbytes) Mem_alloc ((nbytes), __FILE__, __LINE__)

#define CALLOC(count, nbytes)                                                 \
  Mem_calloc ((count), (nbytes), __FILE__, __LINE__)

#define FREE(ptr) Mem_free ((void **)&(ptr), __FILE__, __LINE__)

#define RESIZE(ptr, nbytes)                                                   \
  ((ptr) = Mem_resize ((ptr), (nbytes), __FILE__, __LINE__));

#define NEW(type) ((type *)ALLOC (sizeof (type)))

#define NEW0(type) ((type *)CALLOC (1, sizeof (type)))

#define INIT(p) ((p) = ALLOC (sizeof (*p)))

#define INIT0(p) ((p) = CALLOC (1, sizeof (*p)))

static inline void *
Mem_alloc (size_t nbytes, const char *file, u32 line)
{
  void *ptr;

  assert (nbytes > 0);
  ptr = malloc (nbytes);
  if (!ptr)
    {
      if (!file)
        RAISE (Mem_Failed);
      else
        Except_raise (&Mem_Failed, file, line);
    }

  return ptr;
}

static inline void *
Mem_calloc (size_t count, size_t nbytes, const char *file, u32 line)
{
  void *ptr;

  assert (count > 0);
  assert (nbytes > 0);
  ptr = calloc (count, nbytes);
  if (!ptr)
    {
      if (!file)
        RAISE (Mem_Failed);
      else
        Except_raise (&Mem_Failed, file, line);
    }

  return ptr;
}

static inline void
Mem_free (void **ptr, const char *file, u32 line)
{
  if (*ptr)
    free (*ptr);
  *ptr = NULL;
}

static inline void *
Mem_resize (void *ptr, size_t nbytes, const char *file, u32 line)
{
  assert (ptr);
  assert (nbytes > 0);
  ptr = realloc (ptr, nbytes);
  if (!ptr)
    {
      if (!file)
        RAISE (Mem_Failed);
      else
        Except_raise (&Mem_Failed, file, line);
    }

  return ptr;
}

#endif // MEM_H_
