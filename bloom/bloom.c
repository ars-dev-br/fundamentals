#include "bloom.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct bloom_struct {
    size_t size;   // this is generally called 'm'.
    size_t hashes; // this is generally called 'k'.
    uint8_t* bit_array;
};

/**
 * Get the value of a bit in a bloom filter.
 *
 * @param bloom the bloom filter from where to get the bit.
 * @param bit the position of the bit to be got.
 */
static bool get_bit(const bloom_t *bloom, size_t bit);

/**
 * Set the value of a bit in a bloom filter to 1.
 *
 * @param bloom the bloom filter from where to set the bit.
 * @param bit the position of the bit to be set.
 */
static void set_bit(bloom_t *bloom, size_t bit);

/**
 * First initial hash function.
 *
 * @param value the value that needs to be hashed to be inserted into a bloom
 *     filter.
 * @return the hash value.
 */
static size_t hash1(int value);

/**
 * Second initial hash function.  Should be independent from the first one,
 * which is a bit hard on this case, because we are working with ints.
 *
 * @param value the value that needs to be hashed to be inserted into a bloom
 *     filter.
 * @return the hash value.
 */
static size_t hash2(int value);


bloom_t *bloom_init(size_t size, size_t hashes) {
    bloom_t *bloom = malloc(sizeof(bloom_t));

    bloom->size = size;
    bloom->hashes = hashes;

    size_t bytes = sizeof(uint8_t) * ((size+7)/8);
    bloom->bit_array = malloc(bytes);
    memset(bloom->bit_array, 0, bytes);

    return bloom;
}

void bloom_add(bloom_t *bloom, int value) {
    size_t x = hash1(value) % bloom->size;
    size_t y = hash2(value) % bloom->size;

    set_bit(bloom, x);

    for (size_t i = 1; i < bloom->hashes; i++) {
        x = (x + y) % bloom->size;
        y = (y + i) % bloom->size;

        set_bit(bloom, x);
    }
}

void bloom_free(bloom_t *bloom) {
    if (bloom != NULL) {
        free(bloom->bit_array);
        free(bloom);
    }
}

bool bloom_query(const bloom_t *bloom, int value) {
    size_t x = hash1(value) % bloom->size;
    size_t y = hash2(value) % bloom->size;

    if (!get_bit(bloom, x)) {
        return false;
    }

    for (size_t i = 1; i < bloom->hashes; i++) {
        x = (x + y) % bloom->size;
        y = (y + i) % bloom->size;

        if (!get_bit(bloom, x)) {
            return false;
        }
    }

    return true;
}

bool get_bit(const bloom_t *bloom, size_t bit) {
    assert(bit < bloom->size);

    size_t byte_offset = bit / 8;
    size_t bit_offset = bit % 8;

    uint8_t byte = bloom->bit_array[byte_offset];
    uint8_t mask = 1 << bit_offset;

    return (byte & mask) > 0;
}

void set_bit(bloom_t *bloom, size_t bit) {
    assert(bit < bloom->size);

    size_t byte_offset = bit / 8;
    size_t bit_offset = bit % 8;

    uint8_t byte = bloom->bit_array[byte_offset];
    uint8_t mask = 1 << bit_offset;

    bloom->bit_array[byte_offset] = (byte | mask);
}

size_t hash1(int value) {
    return value;
}

size_t hash2(int value) {
    // Knuth's multiplicative method.
    return value * 2654435761;
}
