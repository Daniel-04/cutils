#ifndef M_ALLOCATOR_H_
#define M_ALLOCATOR_H_

#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>

typedef struct __attribute__ ((aligned (__alignof__ (max_align_t)))) Mem_Node
{
  size_t size;
  struct Mem_Node *next;
} Mem_Node;

typedef struct Buff_T
{
  Mem_Node *free_list;
} Buff_T;

static inline Buff_T Buff_from_buffer (void *buf, size_t nbytes);
static inline void *M_malloc (Buff_T *B, size_t nbytes);
static inline void M_free (Buff_T *B, void *ptr);

#define ALIGNMENT (alignof (max_align_t))

static inline Buff_T
Buff_from_buffer (void *buf, size_t nbytes)
{
  Buff_T buff = { NULL };

  uintptr_t addr = (uintptr_t)buf;
  uintptr_t aligned_addr = (addr + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
  size_t alignment_padding = aligned_addr - addr;

  if (nbytes <= alignment_padding + sizeof (Mem_Node) * 2)
    return buff;

  nbytes -= alignment_padding;
  buf = (void *)aligned_addr;

  Mem_Node *dummy_head = (Mem_Node *)buf;
  Mem_Node *free_head = dummy_head + 1;

  dummy_head->size = 0;
  dummy_head->next = free_head;

  free_head->size = nbytes - sizeof (Mem_Node) * 2;
  free_head->next = NULL;

  buff.free_list = dummy_head;
  return buff;
}

static inline void *
M_malloc (Buff_T *buff, size_t nbytes)
{
  if (buff->free_list == NULL)
    return NULL;

  void *ptr = NULL;
  size_t usage
      = (nbytes + sizeof (Mem_Node) + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
  Mem_Node *prev = buff->free_list;
  Mem_Node *curr = prev->next;
  while (curr != NULL && curr->size < usage)
    {
      prev = curr;
      curr = curr->next;
    }

  if (curr != NULL)
    {
      size_t remainder = curr->size - usage;
      Mem_Node *used, *free;
      if (remainder <= sizeof (Mem_Node))
        {
          prev->next = curr->next;
        }
      else
        {
          free = (Mem_Node *)(((char *)curr) + usage);
          free->size = remainder;
          free->next = curr->next;
          prev->next = free;
        }

      used = curr;
      used->size = usage - sizeof (Mem_Node);
      ptr = ((char *)used) + sizeof (Mem_Node);
    }

  return ptr;
}

static inline void
M_free (Buff_T *buff, void *ptr)
{
  if (buff == NULL || buff->free_list == NULL || ptr == NULL)
    return;

  Mem_Node *target = (Mem_Node *)(((char *)ptr) - sizeof (Mem_Node));
  Mem_Node *prev = buff->free_list;
  Mem_Node *next = prev->next;

  while (next && next < target)
    {
      prev = next;
      next = next->next;
    }

  if (prev != buff->free_list
      && ((char *)prev) + sizeof (Mem_Node) + prev->size == ((char *)target))
    {
      prev->size += sizeof (Mem_Node) + target->size;
      target = prev;
    }
  else
    {
      prev->next = target;
    }

  if (((char *)target) + sizeof (Mem_Node) + target->size == ((char *)next))
    {
      target->size += sizeof (Mem_Node) + next->size;
      target->next = next->next;
    }
  else
    {
      target->next = next;
    }
}

#endif // M_ALLOCATOR_H_
