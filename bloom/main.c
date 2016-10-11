#include "bloom.h"

#include <assert.h>

int main(int argc, char* argv[]) {
    bloom_t *bloom = bloom_init(100);

    bloom_add(bloom, 5);

    assert(bloom_query(bloom, 5));

    bloom_free(bloom);
    return 0;
}
