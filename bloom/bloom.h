#ifndef BLOOM_H
#define BLOOM_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Opaque type defining a bloom filter.
 */
typedef struct bloom_struct bloom_t;


/**
 * Create a new bloom filter.
 *
 * @param size the number of bits used by the created bloom filter.  This is
      generally called 'm' in theoretical texts.  Notice that the actual memory
      use will be a little larger than this.
 * @param hashes the number of hash functions to be used.
 *
 * @return a bloom filter with all bits set to zero.
 */
bloom_t *bloom_init(size_t size, size_t hashes);

/**
 * Add value to an existing bloom filter.  This function expects an int as
 * argument, but in theory any hashable value could be used.
 *
 * @param bloom the bloom filter to which the value will be added.
 * @param value the value to be added
 */
void bloom_add(bloom_t *bloom, int value);

/**
 * Free the memory allocated by a bloom filter.  Do not use a filter that has
 * been freed, although it is safe to call bloom_free on it again.
 *
 * @param bloom the bloom filter to be freed.
 */
void bloom_free(bloom_t *bloom);

/**
 * Query if a bloom filter contains the given value.  This function may return
 * false positives, but no false negatives.  It expects an int as argument, but
 * in theory any hashable value could be used.
 *
 * @param bloom the bloom filter to be queried.
 * @param value the value to be queried.
 */
bool bloom_query(const bloom_t *bloom, int value);

#endif
