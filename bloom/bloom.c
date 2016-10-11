#include "bloom.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bloom_struct {
    size_t size;
    uint8_t* bit_array;
};

static bool get_bit(const bloom_t *bloom, size_t bit);
static void set_bit(bloom_t *bloom, size_t bit, bool value);

bloom_t *bloom_init(size_t size) {
    bloom_t *bloom = malloc(sizeof(bloom_t));

    bloom->size = size;

    size_t bytes = sizeof(uint8_t) * ((size+7)/8);
    bloom->bit_array = malloc(bytes);
    memset(bloom->bit_array, 0, bytes);

    return bloom;
}

void bloom_add(bloom_t *bloom, int value) {
    // TODO: this is a placeholder implementation.

    set_bit(bloom, value, true);
}

void bloom_free(bloom_t *bloom) {
    if (bloom != NULL) {
        free(bloom->bit_array);
        bloom->size = 0;

        free(bloom);
    }
}

bool bloom_query(const bloom_t *bloom, int value) {
    // TODO: this is a placeholder implementation.

    return get_bit(bloom, value);
}

bool get_bit(const bloom_t *bloom, size_t bit) {
    assert(bit < bloom->size);

    size_t byte_offset = bit / 8;
    size_t bit_offset = bit % 8;

    uint8_t byte = bloom->bit_array[byte_offset];
    uint8_t mask = 1 << bit_offset;

    return (byte & mask) > 0;
}

void set_bit(bloom_t *bloom, size_t bit, bool value) {
    assert(bit < bloom->size);

    size_t byte_offset = bit / 8;
    size_t bit_offset = bit % 8;

    uint8_t byte = bloom->bit_array[byte_offset];

    if (value) {
        uint8_t mask = 1 << bit_offset;
        bloom->bit_array[byte_offset] = (byte | mask);
    } else {
        uint8_t mask = 0xff & ~(1 << bit_offset);
        bloom->bit_array[byte_offset] = (byte & mask);
    }
}
