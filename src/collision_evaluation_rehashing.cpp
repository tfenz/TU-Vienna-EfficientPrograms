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
    return h % bound;
}

long hashV2(long h, long bound) {
    h ^= (h >> 20) ^ (h >> 12);
    h = h ^ (h >> 7) ^ (h >> 4);
    return h % bound;
}

long hashV3(long h, long bound) {
    h = (h ^ 0xdeadbeef) + (h << 4);
    h = h ^ (h >> 10);
    h = h + (h << 7);
    h = h ^ (h >> 13);
    return h % bound;
}

int main(int argc, char **argv) {
// print header
    printf("N,");
    printf("Name,");
    printf("Collisions\n");

    for (long n = 1000000; n < 1000000000001; n *= 10) {
        long bound = 1 << (long) (log((double) n) * (2.0 / (3.0 * log(2.0))));

        long *c1 = new long[bound];
        long *c2 = new long[bound];
        long *c3 = new long[bound];
        long *c4 = new long[bound];

        long total_collision_count_hash_ref = 0;
        long total_collision_count_hashThomasWang = 0;
        long total_collision_count_hashLowBitOpt = 0;
        long total_collision_count_hash4shift = 0;

        for (long i = 0; cube(i) <= n; i++) {
            for (long j = i + 1; cube(i) + cube(j) <= n; j++) {
                long current_candidate = cube(i) + cube(j);

                //
                long idx_hash_ref = hash_ref(current_candidate, bound);
                int collision_count_hash_ref = 0;
                while ((c1[idx_hash_ref]) && c1[idx_hash_ref] != current_candidate) {
                    idx_hash_ref = hash_ref(current_candidate + (++collision_count_hash_ref) * 51679, bound);
                }
                total_collision_count_hash_ref += collision_count_hash_ref;
                if (!c1[idx_hash_ref]) {
                    c1[idx_hash_ref] = current_candidate;
                }

                //
                long idx_hashThomasWang = hashV1(current_candidate, bound);
                int collision_count_hashThomasWang = 0;
                while ((c2[idx_hashThomasWang]) && c2[idx_hashThomasWang] != current_candidate) {
                    idx_hashThomasWang = hashV1(current_candidate + (++collision_count_hashThomasWang) * 51679, bound);
                }
                total_collision_count_hashThomasWang += collision_count_hashThomasWang;
                if (!c2[idx_hashThomasWang]) {
                    c2[idx_hashThomasWang] = current_candidate;
                }

                //
                long idx_hashLowBitOpt = hashV2(current_candidate, bound);
                int collision_hashLowBitOpt = 0;
                while ((c3[idx_hashLowBitOpt]) && c3[idx_hashLowBitOpt] != current_candidate) {
                    idx_hashLowBitOpt = hashV2(current_candidate + (++collision_hashLowBitOpt) * 51679, bound);
                }
                total_collision_count_hashLowBitOpt += collision_hashLowBitOpt;
                if (!c3[idx_hashLowBitOpt]) {
                    c3[idx_hashLowBitOpt] = current_candidate;
                }


                //
                long idx_hash4shift = hashV3(current_candidate, bound);
                int collision_hash4shift = 0;
                while ((c4[idx_hash4shift]) && c4[idx_hash4shift] != current_candidate) {
                    idx_hash4shift = hashV3(current_candidate + (++collision_hash4shift) * 51679, bound);
                }
                total_collision_count_hash4shift += collision_hash4shift;
                if (!c4[idx_hash4shift]) {
                    c4[idx_hash4shift] = current_candidate;
                }
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