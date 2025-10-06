#ifndef MEM_H_
#define MEM_H_

#include "error.h"

extern const Except_T Mem_Failed;

void *Mem_alloc (long nbytes, const char *file, int line);
void *Mem_calloc (long count, long nbytes, const char *file, int line);
void Mem_free (void **ptr, const char *file, int line);
void *Mem_resize (void *ptr, long nbytes, const char *file, int line);

#define ALLOC(nbytes) Mem_alloc ((nbytes), __FILE__, __LINE__)

#define CALLOC(count, nbytes)                                                 \
  Mem_calloc ((count), (nbytes), __FILE__, __LINE__)

#define FREE(ptr) Mem_free ((void **)&(ptr), __FILE__, __LINE__)

#define RESIZE(ptr, nbytes)                                                   \
  ((ptr) = Mem_resize ((ptr), (nbytes), __FILE__, __LINE__));

#define NEW(type) ((type *)MALLOC (sizeof (type)))

#define NEW0(type) ((type *)CALLOC (1, sizeof (type)))

#define INIT(p) ((p) = ALLOC (sizeof (*p)))

#define INIT0(p) ((p) = CALLOC (1, sizeof (*p)))

#endif // MEM_H_
