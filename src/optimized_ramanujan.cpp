#include <iostream>
#include "cache_set.h"

unsigned long cube(unsigned long n) {
    return n * n * n;
}


int main(int argc, char *argv[]) {
    // parse argument for limit N, avg_bucket_size
    unsigned long N = std::stol(argv[1], nullptr, 10);
    size_t avg_bucket_size = std::stol(argv[2], nullptr, 10);

    cache_set<ramanujan_candidate> cache(N, avg_bucket_size);
    std::cout << "Number of buckets: " << cache.get_num_cache_buckets() << std::endl;
    std::cout << "Ramanujan candidate bound: " << cache.get_ramanujan_candidate_bound() << std::endl;
    unsigned long ci = 0;
    unsigned long cj = 1;
    for (unsigned long i = 0; ci <= N; i++) {
        ci = cube(i);
        for (unsigned long j = i + 1; ci + cj <= N; j++) {
            cj = cube(j);
            ramanujan_candidate candidate;
            auto sum = ci + cj;
            candidate.value = sum;
            cache.insert(candidate);
        }
    }

    std::cout << cache.get_ramanujan_numbers_count()
              << " Ramanujan numbers up to "
              << cache.get_ramanujan_limit_n()
              << ", checksum=" << cache.get_checksum() << std::endl;
    auto memory_usage = sizeof(cache_set<ramanujan_candidate>) + (sizeof(ramanujan_candidate) * cache.get_size());
    std::cout << "Memory usage> >=" << memory_usage << std::endl;

    std::cout << "===============================================" << std::endl;
    std::pair<unsigned long, char> ts{10, '1'};
    std::cout << "Size of pair: " << sizeof(ts) << std::endl;
    return 0;
}
