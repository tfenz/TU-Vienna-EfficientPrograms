#include <iostream>
#include <cmath>
#include <set>

long cube(long n) {
    return n * n * n;
}

long hash_improved(long h, long bound) {
    h ^= (h >> 20) ^ (h >> 12);
    h = h ^ (h >> 7) ^ (h >> 4);
    return h % bound;
}


int main(int argc, char **argv) {
    long n = std::stol(argv[1], nullptr, 10);
    long bound = 1 << (long) (log((double) n) * (2.0 / (3.0 * log(2.0))));
    auto *candidates = new std::set<long>[bound];
    std::set<long> rama_numbers;
//    long *counts = new long[bound];
    long i, j;
    long checksum = 0;

//    long total_collision_count = 0; //todo debug only
    for (i = 0; cube(i) <= n; i++) {
        for (j = i + 1; cube(i) + cube(j) <= n; j++) {
            long candidate = cube(i) + cube(j);
            long idx = hash_improved(candidate, bound);
            auto res_candidate = candidates[idx].insert(candidate);
            if (!res_candidate.second){
                auto res_rama = rama_numbers.insert(candidate);
                if (res_rama.second){
                    checksum += candidate;
                }
            }
        }
    }
//    printf("collisioncount: %ld\n", total_collision_count); //todo debug only
    printf("%ld Ramanujan numbers up to %ld, checksum=%ld\n size=%ld\n",
           rama_numbers.size(), n, checksum, bound);
    printf("Memory usage: >=%ld\n", bound * (sizeof(long *)));
    return 0;
}
