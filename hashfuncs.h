#ifndef __HASH_FUNCS__
#define __HASH_FUNCS__

#include <string.h>
#include <stdint.h>

#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U

// define the hash functions 
uint32_t FNV32(const char *);
uint32_t murmurhash (const char *, uint32_t, uint32_t);

#endif