//
#include <stdint.h>
#include <stdio.h>
#include "hashfuncs.h"

// https://layerlab.org/2018/06/07/My-bitmap.html
#include "bitmap.h"

#define BLOOM_FILTER_SIZE 100

// Initializes a bloom filter with size BLOOOM_FILTER_SIZE from 
int main(){
    struct bit_map * bloom_filter = bit_map_init(BLOOM_FILTER_SIZE);
    // bit_map_set(bloom_filter,1);

    char * c = "HASH";
    uint32_t d = FNV32(c);
    uint32_t e = murmurhash(c,(uint32_t) strlen(c), 42);

    printf("Size of Bloom Filter: %llu \n", bloom_filter->num_ints);

    // Bloom filter 
    d%= BLOOM_FILTER_SIZE;
    e%= BLOOM_FILTER_SIZE;

}