#include <iostream>
#include "cache_set.h"

long cube(long n) {
    return n * n * n;
}

long hash1(long a, long candidate_bound) {
    a = (a ^ 0xdeadbeef) + (a << 4);
    a = a ^ (a >> 10);
    a = a + (a << 7);
    a = a ^ (a >> 13);
    return a % candidate_bound;
}

long hash2(long a, long candidate_bound) {
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a % candidate_bound;
}

long hash3(long a, long bound) {
    a = a ^ (a >> 4);
    a = (a ^ 0xdeadbeef) + (a << 5);
    a = a ^ (a >> 11);
    return a % bound;
}

long hash4(long h, long bound) {
    h ^= (h >> 20) ^ (h >> 12);
    h = h ^ (h >> 7) ^ (h >> 4);
    return h % bound;
}

int main(int argc, char **argv) {
    long n = std::stol(argv[1], nullptr, 10);
    long bound2 = 1 << (long) (log((double) n) * (2.0 / (3.0 * log(2.0))));
    long bound = 4 << (long) (log((double) n) * (2.0 / (3.0 * log(2.0))));
    long *candidates = new long[bound];
    long *counts = new long[bound];
    long i, j;
    long checksum = 0;
    long count_ramanujan = 0;

    long total_collision_count = 0; //todo debug only
    for (i = 0; cube(i) <= n; i++) {
        for (j = i + 1; cube(i) + cube(j) <= n; j++) {
            long current_candidate = cube(i) + cube(j);
            long idx = hash3(current_candidate, bound);

            int collision_count = 0;
            while ((candidates[idx]) && candidates[idx] != current_candidate) {
                idx = hash3(current_candidate + (++collision_count) * 51679, bound);
            }
            total_collision_count += collision_count; //todo debug only
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
    printf("collisioncount: %ld", total_collision_count);//todo debug only
    printf("%ld Ramanujan numbers up to %ld, checksum=%ld\n size=%ld\n",
           count_ramanujan, n, checksum, bound);
    printf("Memory usage: >=%ld\n", bound * (sizeof(long *)));
    return 0;
}
