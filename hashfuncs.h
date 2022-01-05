#ifndef __HASHFUNCS_H__
#define __HASHFUNCS_H__

/**
 * Defines and implements hash functions used for bloom filters/hash tables
 * Currenly supports murmurhash3 and FNV32
 */

#include <string.h>
#include <stdint.h>

#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U

//https://github.com/jwerle/murmurhash.c
uint32_t FNV32(const char *);
uint32_t murmurhash (const char *, uint32_t, uint32_t);

#endif