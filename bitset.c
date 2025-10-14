#include "bitset.h"
#include "error.h"
#include "mem.h"

Bitset *
B_create (size_t nbits)
{
  size_t nbytes = (nbits + (UCHAR_BITS - 1)) / UCHAR_BITS;

  Bitset *b = NEW (Bitset);
  b->buf = CALLOC (nbytes, sizeof (unsigned char));
  b->nbytes = nbytes;

  return b;
}

void
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

int
B_get (Bitset *b, size_t bit)
{
  size_t idx = bit / UCHAR_BITS;
  size_t offset = bit % UCHAR_BITS;
  assert (idx < b->nbytes);

  return (b->buf[idx] >> offset) & 1U;
}

void
B_free (Bitset *b)
{
  FREE (b->buf);
  FREE (b);
}
