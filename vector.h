#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <stdint.h>

// A simple dynamic array implementation for strings, currently does not support removal

struct vector{
    char ** array;
    size_t used;
    size_t bytes_used;
    size_t size;
};
struct vector * vector_init(size_t initialSize);
void vector_insert(struct vector * v, char * word, int n);
uint32_t vector_size(struct vector * v);
void vector_free(struct vector * v);
char * vector_at(struct vector * v, uint32_t pos);
uint32_t vector_bytes_used(struct vector * v);

#endif