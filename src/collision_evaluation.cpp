#include <iostream>
#include <cmath>


long cube(long n) {
    return n * n * n;
}


long hash_ref(long h, long bound) {
    return h & (bound - 1);
}

long hashV1(long h, long bound) {
    h += ~(h << 15);
    h ^= (h >> 10);
    h += (h << 3);
    h ^= (h >> 6);
    h += ~(h << 11);
    h ^= (h >> 16);
    return h & (bound - 1);
}

long hashV2(long h, long bound) {
    h ^= (h >> 20) ^ (h >> 12);
    h = h ^ (h >> 7) ^ (h >> 4);
    return h & (bound - 1);
}

long hashV3(long h, long bound) {
    h = (h ^ 0xdeadbeef) + (h << 4);
    h = h ^ (h >> 10);
    h = h + (h << 7);
    h = h ^ (h >> 13);
    return h & (bound - 1);
}


int main(int argc, char **argv) {
// print header
    printf("N,");
    printf("Name,");
    printf("Collisions\n");

    for (long n = 1000000; n < 10000000000001; n *= 10) {
        long bound = 1 << (long) (log((double) n) * (2.0 / (3.0 * log(2.0))));

        char *c1 = new char[bound];
        char *c2 = new char[bound];
        char *c3 = new char[bound];
        char *c4 = new char[bound];

        long total_collision_count_hash_ref = 0;
        long total_collision_count_hashThomasWang = 0;
        long total_collision_count_hashLowBitOpt = 0;
        long total_collision_count_hash4shift = 0;

        for (long i = 0; cube(i) <= n; i++) {
            for (long j = i + 1; cube(i) + cube(j) <= n; j++) {
                long current_candidate = cube(i) + cube(j);

                long idx_hash_ref = hash_ref(current_candidate, bound);
                long idx_hashThomasWang = hashV1(current_candidate, bound);
                long idx_hashLowBitOpt = hashV2(current_candidate, bound);
                long idx_hash4shift = hashV3(current_candidate, bound);

                if (c1[idx_hash_ref]) total_collision_count_hash_ref++;
                else c1[idx_hash_ref] = 1;

                if (c2[idx_hashThomasWang]) total_collision_count_hashThomasWang++;
                else c2[idx_hashThomasWang] = 1;

                if (c3[idx_hashLowBitOpt]) total_collision_count_hashLowBitOpt++;
                else c3[idx_hashLowBitOpt] = 1;

                if (c4[idx_hash4shift]) total_collision_count_hash4shift++;
                else c4[idx_hash4shift] = 1;
            }
        }
        printf("%ld,", n);
        printf("HF (reference),");
        printf("%ld\n", total_collision_count_hash_ref);

        printf("%ld,", n);
        printf("HF (v1),");
        printf("%ld\n", total_collision_count_hashThomasWang);

        printf("%ld,", n);
        printf("HF (v2),");
        printf("%ld\n", total_collision_count_hashLowBitOpt);

        printf("%ld,", n);
        printf("HF (v3),");
        printf("%ld\n", total_collision_count_hash4shift);
    }
}