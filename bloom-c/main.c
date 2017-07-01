#include "bloom.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialize bloom filter with m = 50 bits and k = 7 hash functions.
    bloom_t *bloom = bloom_init(50, 7);

    // Add some values to it.
    bloom_add(bloom, 1);
    bloom_add(bloom, 2);
    bloom_add(bloom, 3);

    // Make a thousand queries and count how many returned true.
    const int queries = 1000;
    int positives = 0;
    for (int i = 0; i < queries; i++) {
        positives += bloom_query(bloom, i) ? 1 : 0;
    }

    // Print the percentage of positive queries.
    printf("Percentage of positives: %.2f%\n", positives * 100 / (double) queries);

    bloom_free(bloom);
    return 0;
}
