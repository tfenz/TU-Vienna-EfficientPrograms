#include <iostream>
#include <math.h>

long cube(long n) {
    return n * n * n;
}

long hash_improved(long h, long bound) {
    h ^= (h >> 20) ^ (h >> 12);
    h = h ^ (h >> 7) ^ (h >> 4);
    return h % bound;
}

long hash(long h, long bound) {
    return h & (bound - 1);
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
    long c_i = 0;
    for (i = 0; c_i <= n; i++) {
        c_i = cube(i);
        long c_j = 0;
        for (j = i + 1; c_i + c_j <= n; j++) {
            c_j = cube(j);
            long current_candidate = c_i + c_j;
            long idx = hash_improved(current_candidate, bound);

            int collision_count = 0;
            while ((candidates[idx]) && candidates[idx] != current_candidate) {
                idx = hash_improved(current_candidate + (++collision_count) * 51679, bound);
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
    printf("collisioncount: %ld", total_collision_count); //todo debug only
    printf("%ld Ramanujan numbers up to %ld, checksum=%ld\n size=%ld\n",
           count_ramanujan, n, checksum, bound);
    printf("Memory usage: >=%ld\n", bound * (sizeof(long *)));
    return 0;
}
