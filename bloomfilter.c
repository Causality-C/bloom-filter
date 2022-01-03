#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// https://layerlab.org/2018/06/07/My-bitmap.html
#include "bitmap.h"
#include "bloomfilter.h"
#include "hashfuncs.h"

#define SEED 42


struct bloom_filter * bloom_filter_init(uint64_t bits, uint32_t hashes){
    struct bloom_filter * b = (struct bloom_filter * ) malloc(sizeof(struct bloom_filter));
    struct bit_map * bf = bit_map_init(bits);

    // Initalizing the struct fields
    b->bf = bf;
    b->bits = bits;
    b->num_entries = 0;
    b->num_hashes = hashes;

    // Return the bloom filter
    return b;
}

// Returns if the insertion was successful
bool bloom_filter_insert(struct bloom_filter * b, char * word){
    uint32_t bits = b->bits;
    struct bit_map * bm = b->bf;
    uint32_t num_hashes = b->num_hashes;

    for(unsigned int seed = 0; seed < num_hashes; seed++){
        uint32_t index = murmurhash(word,sizeof(word),seed) % bits;
        bit_map_set(bm,index);
    }
    
    b->num_entries++;

    return true; 
}

bool bloom_filter_search(struct bloom_filter * b, char * word){
    uint32_t bits = b->bits;
    struct bit_map * bm = b->bf;
    uint32_t num_hashes = b->num_hashes;
    bool all_found = true;

    for(unsigned int seed = 0; seed < num_hashes; seed++){
        uint32_t index = murmurhash(word,sizeof(word),seed) % bits;
        all_found &= bit_map_get(bm,index);
    }
    return all_found;
}

void bloom_filter_bitmap_print(struct bloom_filter * b){
    struct bit_map * bm = b->bf;
    uint32_t bits = bm->num_bits;

    for(unsigned int i = 0; i< bits; i++){
        printf("%d",bit_map_get(bm,i));
    }
    printf("\n");
}

void bloom_filter_destroy(struct bloom_filter *b){
    bit_map_destroy(&(b->bf));
    free(b);
    b = NULL;
}

/**
 *  Calculations found at https://hur.st/bloomfilter/?n=20&p=&m=10&k=2
 *  m: number of bits in the filter
 *  n: number of elements in the filter
 *  k: number of hash functions
 *  p: probability of false_positive
 */
double bloom_filter_false_positive_rate(uint32_t m, uint32_t n, uint32_t k){
    return pow(1.0 - exp(-(double) k / ((double)m / (double)n)), (double)k);
}

uint32_t bloom_filter_bit_array_size_optimum(uint32_t n, double p){
    return ceil(((double) n * log((double) p)) / log(1.0 / pow(2.0, log(2))));
}

uint32_t bloom_filter_optimum_hash_functions(uint32_t m, uint32_t n){
    return round(((double) m / (double) n) * log(2.0));
}