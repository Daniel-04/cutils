#ifndef BITSET_H_
#define BITSET_H_

#include <stddef.h>

typedef struct Bitset
{
  size_t nbytes;
  unsigned char *buf;
} Bitset;

Bitset *B_create (size_t nbits);
void B_set (Bitset *b, size_t bit, int val);
int B_get (Bitset *b, size_t bit);
void B_free (Bitset *b);

#define UCHAR_BITS 8

#endif // BITSET_H_
