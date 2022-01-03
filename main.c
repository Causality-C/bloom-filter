#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bloomfilter.h"
#include "bitmap.h"
#include "vector.h"


#define VECTOR_SIZE 10
#define FALSE_POSITIVE_RATE 0.7

// Test bloom filter by reading file, determining optimal paramters based upon a false positive rate,
// and constructing a bloom filter based on those optimal parameters. 
// Ideally, the contents of this file should be duplicate free

int main(int argc, char * argv[]){

    // 2 arguments required, second one being the file name
    if(argc != 2){
        printf("Expected number of arguments: 2\nRecieved: %d\n",argc);
        exit(1);
    }

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;

    // Open Files and handle errors
    fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("File not found\n");
        exit(1);
    }


    // Store Words in Dynamic Array
    struct vector * arr = vector_init(VECTOR_SIZE);

    // Read in words to get 
    while ((read = getline(&line, &len, fp)) != -1) {
        vector_insert(arr,line,read);
    }

    // Determine Bloom Filter Optimal values
    uint32_t m_bits = bloom_filter_bit_array_size_optimum(arr->used, FALSE_POSITIVE_RATE);
    uint32_t k_hashes = bloom_filter_optimum_hash_functions(m_bits, arr->used);

    // Create Bloom filter 
    struct bloom_filter * bf = bloom_filter_init(m_bits,k_hashes);
    uint32_t duplicates = 0;
    printf("Constructed Bloom Filter with optimal settings...\nm_bits: %d\nn_elements: %ld\nk_hashes: %d\ntarget_false_positive_rate: %f\n\n", m_bits, arr->used, k_hashes, FALSE_POSITIVE_RATE);

    // Insert Word and print out duplicates
    for(int i = 0; i < vector_size(arr); i++){
        char * word = vector_at(arr,i);
        if(bloom_filter_search(bf,word)){
            #ifdef DEBUG
                printf("Duplicate Word Found: %s\n", word);
            #endif
            duplicates++;
        }
        bloom_filter_insert(bf,word);
    }
    
    // Print array vs bloomfilter space comparison
    printf("Size of array/hashmap: %d\n", vector_bytes_used(arr));
    printf("Size of bloom filter: %d\n\n", bit_map_in_bytes(bf->bf));

    // Print True False Positive Values
    printf("Duplicates/False Positives: %d/%ld\n", duplicates, bf->num_entries);
    printf("Empirical False Positive Rate: %f\n", (double) duplicates / (double) bf->num_entries);
    printf("Expected False Positives: %f\n",FALSE_POSITIVE_RATE * bf->num_entries);

    // Free everything
    vector_free(arr);
    bloom_filter_destroy(bf);
    fclose(fp);
    free(line);

    return 0;
}