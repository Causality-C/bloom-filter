#ifndef __BLOOMFLITER_H__
#define __BLOOMFLITER_H__

/**
 * Defines and Implements basic bloom filter functionality:
 * - Creation of filter 
 * - Insertion -- uses murmur3 hash with different seeds
 * - Search: will never produce false negatives, it is possible to produce false positives
 * - Printing of the bitmap used in the filter
 * - Optimal creation parameters based on # of words in the filter
 */

#include <stdint.h>
#include <stdbool.h>

struct bloom_filter
{
    uint64_t num_entries;
    uint64_t bits;
    uint32_t num_hashes;
    struct bit_map * bf;
};

struct bloom_filter * bloom_filter_init(uint64_t bits, uint32_t num_hashes);
bool bloom_filter_insert(struct bloom_filter * b, char * word);
bool bloom_filter_search(struct bloom_filter *b, char * word);
void bloom_filter_bitmap_print(struct bloom_filter * b);
void bloom_filter_destroy(struct bloom_filter *b);

// Optimal Calculations
double bloom_filter_false_positive_rate(uint32_t m, uint32_t n, uint32_t k);
uint32_t bloom_filter_bit_array_size_optimum(uint32_t n, double p);
uint32_t bloom_filter_optimum_hash_functions(uint32_t m, uint32_t n);

#endif