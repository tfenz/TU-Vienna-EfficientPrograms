#include <iostream>
#include <cmath>


long cube(long n) {
    return n * n * n;
}


long hash_ref(long h, long bound) {
    return h & (bound - 1);
}

long hashThomasWang(long h, long bound) {
    h += ~(h << 15);
    h ^= (h >> 10);
    h += (h << 3);
    h ^= (h >> 6);
    h += ~(h << 11);
    h ^= (h >> 16);
    return h % bound;
}

long hashLowBitOpt(long h, long bound) {
    h ^= (h >> 20) ^ (h >> 12);
    h = h ^ (h >> 7) ^ (h >> 4);
    return h % bound;
}

long hash4shift(long h, long bound) {
    h = (h ^ 0xdeadbeef) + (h << 4);
    h = h ^ (h >> 10);
    h = h + (h << 7);
    h = h ^ (h >> 13);
    return h % bound;
}

long hashTomWang2(long h, long bound) {
    h = (h + 0x7ed55d16) + (h << 12);
    h = (h ^ 0xc761c23c) ^ (h >> 19);
    h = (h + 0x165667b1) + (h << 5);
    h = (h + 0xd3a2646c) ^ (h << 9);
    h = (h + 0xfd7046c5) + (h << 3);
    h = (h ^ 0xb55a4f09) ^ (h >> 16);
    return h % bound;
}

int main(int argc, char **argv) {
// print header
    printf("N,");
    printf("hash_ref,");
    printf("hashThomasWang,");
    printf("hashLowBitOpt,");
    printf("hash4shift");
    printf("\n");

    for (long n = 1000000; n < 10000000000001; n *= 10) {
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
//                long idx_hash_ref = hash_ref(current_candidate, bound);
//                int collision_count_hash_ref = 0;
//                while ((c1[idx_hash_ref]) && c1[idx_hash_ref] != current_candidate) {
//                    idx_hash_ref = hash_ref(current_candidate + (++collision_count_hash_ref) * 51679, bound);
//                }
//                total_collision_count_hash_ref += collision_count_hash_ref;
//                if (!c1[idx_hash_ref]) {
//                    c1[idx_hash_ref] = current_candidate;
//                }

                //
                long idx_hashThomasWang = hashThomasWang(current_candidate, bound);
                int collision_count_hashThomasWang = 0;
                while ((c2[idx_hashThomasWang]) && c2[idx_hashThomasWang] != current_candidate) {
                    idx_hashThomasWang = hashThomasWang(current_candidate + (++collision_count_hashThomasWang) * 51679, bound);
                }
                total_collision_count_hashThomasWang += collision_count_hashThomasWang;
                if (!c2[idx_hashThomasWang]) {
                    c2[idx_hashThomasWang] = current_candidate;
                }

                //
                long idx_hashLowBitOpt = hashLowBitOpt(current_candidate, bound);
                int collision_hashLowBitOpt = 0;
                while ((c3[idx_hashLowBitOpt]) && c3[idx_hashLowBitOpt] != current_candidate) {
                    idx_hashLowBitOpt = hashLowBitOpt(current_candidate + (++collision_hashLowBitOpt) * 51679, bound);
                }
                total_collision_count_hashLowBitOpt += collision_hashLowBitOpt;
                if (!c3[idx_hashLowBitOpt]) {
                    c3[idx_hashLowBitOpt] = current_candidate;
                }


                //
                long idx_hash4shift = hash4shift(current_candidate, bound);
                int collision_hash4shift = 0;
                while ((c4[idx_hash4shift]) && c4[idx_hash4shift] != current_candidate) {
                    idx_hash4shift = hash4shift(current_candidate + (++collision_hash4shift) * 51679, bound);
                }
                total_collision_count_hash4shift += collision_hash4shift;
                if (!c4[idx_hash4shift]) {
                    c4[idx_hash4shift] = current_candidate;
                }
            }
        }
        printf("%ld,", n);
        printf("%ld,", total_collision_count_hash_ref);
        printf("%ld,", total_collision_count_hashThomasWang);
        printf("%ld,", total_collision_count_hashLowBitOpt);
        printf("%ld", total_collision_count_hash4shift);
        printf("\n");
    }
}