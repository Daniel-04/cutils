#ifndef DEFS_H_
#define DEFS_H_

#include <stddef.h>
#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef enum
{
  OK = 0,
  ERR = -1,
} Result;

#if !(defined(__GNUC__) || defined(__clang__))
static inline u32 CTZ32 (u32 x);
static inline u64 CTZ64 (u64 x);
static inline u32 CLZ32 (u32 x);
static inline u64 CLZ64 (u64 x);
static inline u32 POPCOUNT32 (u32 x);
static inline u64 POPCOUNT64 (u64 x);
#endif

#define KB(n) ((size_t)(n) << 10)
#define MB(n) ((size_t)(n) << 20)
#define GB(n) ((size_t)(n) << 30)

#define UNUSED(x) (void)(x)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(x, lo, hi) (MAX ((lo), MIN ((x), (hi))))

#define ALIGN_UP(x, a) (((x) + ((a) - 1)) & ~((a) - 1))
#define ALIGN_DOWN(x, a) ((x) & ~((a) - 1))
#define IS_ALIGNED(x, a) (((x) & ((a) - 1)) == 0)

#define ROTL32(x, r) ((x << r) | (x >> (32 - r)))
#define ROTR32(x, r) ((x >> r) | (x << (32 - r)))
#define ROTL64(x, r) ((x << r) | (x >> (64 - r)))
#define ROTR64(x, r) ((x >> r) | (x << (64 - r)))

#define BIT(n) (1ULL << (n))
#define BIT_MASK(len) (BIT (len) - 1)
#define BIT_RANGE(hi, lo) ((BIT ((hi) - (lo) + 1) - 1) << (lo))

#define SET_BIT(x, n) ((x) |= BIT (n))
#define CLEAR_BIT(x, n) ((x) &= ~BIT (n))
#define TEST_BIT(x, n) (((x) & BIT (n)) != 0)

#define SET_BITS(x, mask) ((x) |= (mask))
#define CLEAR_BITS(x, mask) ((x) &= ~(mask))
#define TEST_BITS(x, mask) (((x) & (mask)) == (mask))

#if defined(__GNUC__) || defined(__clang__)
#define CTZ32(x) __builtin_ctz (x)
#define CLZ32(x) __builtin_clz (x)
#define CTZ64(x) __builtin_ctzll (x)
#define CLZ64(x) __builtin_clzll (x)
#define POPCOUNT32(x) __builtin_popcount (x)
#define POPCOUNT64(x) __builtin_popcountll (x)
#endif

#if !(defined(__GNUC__) || defined(__clang__))
static inline u32
CTZ32 (u32 x)
{
  u32 n = 0;
  while ((x & 1u) == 0)
    {
      x >>= 1;
      n++;
    }
  return n;
}
static inline u64
CTZ64 (u64 x)
{
  u64 n = 0;
  while ((x & 1ull) == 0)
    {
      x >>= 1;
      n++;
    }
  return n;
}
static inline u32
CLZ32 (u32 x)
{
  u32 n = 0;
  u32 mask = 1u << 31;
  while ((x & mask) == 0)
    {
      mask >>= 1;
      n++;
    }
  return n;
}
static inline u64
CLZ64 (u64 x)
{
  u64 n = 0;
  u64 mask = 1ull << 63;
  while ((x & mask) == 0)
    {
      mask >>= 1;
      n++;
    }
  return n;
}
static inline u32
POPCOUNT32 (u32 x)
{
  u32 count = 0;
  while (x)
    {
      x &= x - 1;
      count++;
    }
  return count;
}
static inline u64
POPCOUNT64 (u64 x)
{
  u64 count = 0;
  while (x)
    {
      x &= x - 1;
      count++;
    }
  return count;
}
#endif

#endif // DEFS_H_
