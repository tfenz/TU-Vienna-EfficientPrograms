#include <iostream>
#include "cache_set.h"

unsigned long cube(unsigned long n) {
    return n * n * n;
}


int main(int argc, char *argv[]) {
    // parse argument for limit N
    unsigned long N = std::stol(argv[1], nullptr, 10);

    cache_set<ramanujan_candidate> cache(N, 100000);

    for (unsigned long i = 0; cube(i) <= N; i++) {
        for (unsigned long j = i + 1; cube(i) + cube(j) <= N; j++) {
            ramanujan_candidate candidate;
            auto sum = cube(i) + cube(j);
            candidate.value = sum;
            cache.insert(candidate);
        }
    }

    std::cout << "Ramanujan candidate bound: " << cache.get_ramanujan_candidate_bound() << std::endl;
    std::cout << "Ramanujan limit N: " << cache.get_ramanujan_limit_n() << std::endl;
    std::cout << "Ramanujan numbers found: " << cache.get_ramanujan_numbers_count() << std::endl;
    std::cout << "Num buckets: " << cache.get_num_cache_buckets() << std::endl;
    std::cout << "Cache line size: " << cache.get_cache_line_size() << std::endl;
    std::cout << "Cache Set size: " << cache.get_size() << std::endl;
    std::cout << "Checksum: " << cache.get_checksum() << std::endl;

    return 0;
}
