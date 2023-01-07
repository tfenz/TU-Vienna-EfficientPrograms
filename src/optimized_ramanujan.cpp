#include <iostream>
#include "cache_set.h"

unsigned long cube(unsigned long n) {
    return n * n * n;
}


int main(int argc, char *argv[]) {
    // parse argument for limit N
    unsigned long N = std::stol(argv[1], nullptr, 10);

    cache_set<ramanujan_candidate> cache(N, 100000);
    std::cout << "Number of buckets: " << cache.get_num_cache_buckets() << std::endl;

    for (unsigned long i = 0; cube(i) <= N; i++) {
        for (unsigned long j = i + 1; cube(i) + cube(j) <= N; j++) {
            ramanujan_candidate candidate;
            auto sum = cube(i) + cube(j);
            candidate.value = sum;
            cache.insert(candidate);
        }
    }

    std::cout << cache.get_ramanujan_numbers_count()
              << " Ramanujan numbers up to "
              << cache.get_ramanujan_limit_n()
              << ", checksum=" << cache.get_checksum() << std::endl;
    auto memory_usage = sizeof(cache_set<ramanujan_candidate>) + (sizeof(ramanujan_candidate) * cache.get_capacity());
    std::cout << "Memory usage> >=" << memory_usage << std::endl;
    return 0;
}
