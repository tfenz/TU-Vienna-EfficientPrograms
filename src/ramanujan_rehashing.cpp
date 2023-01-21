#include <iostream>
#include <cmath>

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
    char *counts = new char[bound];
    long i, j;
    long checksum = 0;
    long count_ramanujan = 0;

//    long total_collision_count = 0; //todo debug only
    for (i = 0; cube(i) <= n; i++) {
        for (j = i + 1; cube(i) + cube(j) <= n; j++) {
            long current_candidate = cube(i) + cube(j);
            long idx = hash_improved(current_candidate, bound);

            int collision_count = 0;
            while ((candidates[idx]) && candidates[idx] != current_candidate) {
                idx = hash_improved(current_candidate + (++collision_count) * 51679, bound);
            }
//            total_collision_count += collision_count; //todo debug only
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
//    printf("collisioncount: %ld\n", total_collision_count); //todo debug only
    auto memory_usage = bound * (sizeof(long *));
    memory_usage += bound * (sizeof(char *));

    printf("%ld Ramanujan numbers up to %ld, checksum=%ld\n size=%ld\n",
           count_ramanujan, n, checksum, bound);
    printf("Memory usage: >=%ld\n", memory_usage);
    return 0;
}
