#ifndef BLOOM_H
#define BLOOM_H

#include <stdbool.h>
#include <stddef.h>

/** Opaque type defining a bloom filter. */
typedef struct bloom_struct bloom_t;


/** Create a new bloom filter. */
bloom_t *bloom_init(size_t size);

/** Add value to an existing bloom filter. */
void bloom_add(bloom_t *bloom, int value);

/** Free the memory allocated by a bloom filter. */
void bloom_free(bloom_t *bloom);

/** Query if a bloom filter contains the given value.  This function may return
 * false positives, but no false negatives. */
bool bloom_query(const bloom_t *bloom, int value);

#endif
