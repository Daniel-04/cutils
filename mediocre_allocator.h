#ifndef M_ALLOCATOR_H_
#define M_ALLOCATOR_H_

#include <stdalign.h>
#include <stddef.h>

typedef struct __attribute__ ((aligned (__alignof__ (max_align_t)))) Mem_Node
{
  size_t size;
  struct Mem_Node *next;
} Mem_Node;

typedef struct Buff_T
{
  Mem_Node *free_list;
} Buff_T;

Buff_T Buff_from_buffer (void *buf, size_t nbytes);
void *M_malloc (Buff_T *B, size_t nbytes);
void M_free (Buff_T *B, void *ptr);

#define ALIGNMENT (alignof (max_align_t))

#endif // M_ALLOCATOR_H_
