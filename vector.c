#include "vector.h"

struct vector * vector_init(size_t initialSize){
    struct vector * v = (struct vector *) malloc(sizeof(struct vector));
    char ** array = malloc(initialSize * sizeof(char *));

    v->array = array;
    v->size = initialSize;
    v->used = 0;
    v->bytes_used = 0;

    return v;
}
void vector_insert(struct vector * v, char * word, int n){
    // Realloc array
    if(v->size == v->used){
        v->size *= 2;
        v->array = realloc(v->array, v->size * sizeof(char *));
    }

    v->array[v->used] = malloc(n * sizeof(char));
    v->bytes_used += n;

    // Copy word
    for(int i = 0; i< n; i++){
        v->array[v->used][i] = word[i];
    }
    v->used++;
}

// Returns the number of elements used by the vector
uint32_t vector_size(struct vector * v){
    return v->used;
}

char * vector_at(struct vector * v, uint32_t pos){
    if(pos >= v->used){
        return NULL;
    }
    return v->array[pos];
}

void vector_free(struct vector * v){
    for(int i = 0; i< v->used; i++){
        free(v->array[i]);
    }
    free(v->array);
    v->array = NULL;
    v->used = 0;
    v->size = 0;
    free(v);
}

// Return bytes used by vector structure in use
uint32_t vector_bytes_used(struct vector * v){
    return v->bytes_used + v->used;
}