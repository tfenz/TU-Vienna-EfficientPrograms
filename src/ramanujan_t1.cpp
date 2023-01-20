#include <iostream>
#include "cache_set.h"

long cube(long n) {
    return n * n * n;
}

long hash(long x, long candidate_bound) {
    // good hash function for integers as evaluated here:
    // https://github.com/h2database/h2database/blob/master/h2/src/test/org/h2/test/store/CalculateHashConstant.java
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % candidate_bound;
}

int main(int argc, char **argv) {
    long n = std::stol(argv[1], nullptr, 10);
    long bound = 1 << (long) (log((double) n) * (2.0 / (3.0 * log(2.0))));
    long *candidates = new long[bound];
    long *counts = new long[bound];
    long i, j;
    long checksum = 0;
    long count_ramanujan = 0;

    long total_collision_count = 0; //todo debug only
    for (i = 0; cube(i) <= n; i++) {
        for (j = i + 1; cube(i) + cube(j) <= n; j++) {
            long current_candidate = cube(i) + cube(j);
            long idx = hash(current_candidate, bound);

            int collision_count=0;
            while ((candidates[idx]) && candidates[idx] != current_candidate) {
                idx = hash(current_candidate+(++collision_count)*17, bound);
            }
            total_collision_count += collision_count;
            if (!candidates[idx]) {
                candidates[idx] = current_candidate;
                counts[idx] = 1;
            } else {
                if (++counts[idx] == 2) {
                    count_ramanujan++;
                    checksum += current_candidate;
                }
            }
        }
    }
    printf("collisioncount: %ld", total_collision_count);
    printf("%ld Ramanujan numbers up to %ld, checksum=%ld\n size=%ld\n",
           count_ramanujan, n, checksum, bound);
    printf("Memory usage: >=%ld\n", bound * (sizeof(long *)));
    return 0;
}
