#include <iostream>
#include "cache_set_no_struct.h"

unsigned long cube(unsigned long n) {
    return n * n * n;
}


int main(int argc, char *argv[]) {
    // parse argument for limit N, avg_bucket_size
    unsigned long N = std::stol(argv[1], nullptr, 10);
    size_t avg_bucket_size = std::stol(argv[2], nullptr, 10);

    cache_set_no_struct cache(N, avg_bucket_size);
    std::cout << "Number of buckets: " << cache.get_num_cache_buckets() << std::endl;
    std::cout << "Ramanujan candidate bound: " << cache.get_ramanujan_candidate_bound() << std::endl;

    for (unsigned long i = 0; cube(i) <= N; i++) {
        for (unsigned long j = i + 1; cube(i) + cube(j) <= N; j++) {
            auto candidate = cube(i) + cube(j);
            cache.insert(candidate);
        }
    }

    std::cout << cache.get_ramanujan_numbers_count()
              << " Ramanujan numbers up to "
              << cache.get_ramanujan_limit_n()
              << ", checksum=" << cache.get_checksum() << std::endl;
    auto memory_usage = sizeof(cache_set_no_struct) + (sizeof(unsigned long) * cache.get_capacity())
            + (sizeof(char) * cache.get_capacity());
    std::cout << "Memory usage> >=" << memory_usage << std::endl;

    //std::cout << "===============================================" << std::endl;

    return 0;
}

