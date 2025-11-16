#ifndef BITSET_H_
#define BITSET_H_

#include "error.h"
#include "mem.h"
#include <stddef.h>

typedef struct Bitset
{
  size_t nbytes;
  unsigned char *buf;
} Bitset;

static inline Bitset *B_create (size_t nbits);
static inline void B_set (Bitset *b, size_t bit, int val);
static inline int B_get (Bitset *b, size_t bit);
static inline void B_free (Bitset *b);

#define UCHAR_BITS 8

static inline Bitset *
B_create (size_t nbits)
{
  size_t nbytes = (nbits + (UCHAR_BITS - 1)) / UCHAR_BITS;

  Bitset *b = NEW (Bitset);
  b->buf = (unsigned char *)CALLOC (nbytes, sizeof (unsigned char));
  b->nbytes = nbytes;

  return b;
}

static inline void
B_set (Bitset *b, size_t bit, int val)
{
  size_t idx = bit / UCHAR_BITS;
  size_t offset = bit % UCHAR_BITS;
  assert (idx < b->nbytes);

  if (val)
    b->buf[idx] |= (1U << offset);
  else
    b->buf[idx] &= ~(1U << offset);
}

static inline int
B_get (Bitset *b, size_t bit)
{
  size_t idx = bit / UCHAR_BITS;
  size_t offset = bit % UCHAR_BITS;
  assert (idx < b->nbytes);

  return (b->buf[idx] >> offset) & 1U;
}

static inline void
B_free (Bitset *b)
{
  FREE (b->buf);
  FREE (b);
}

#endif // BITSET_H_
