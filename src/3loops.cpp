#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

#define CUBE(n) (n*n*n)

int main(int argc, char *argv[]) {
    long N = std::stol(argv[1], nullptr, 10);
    long checksum = 0;
    long count = 0;
    long i, x, y, k;

    for (i = 0; i < N; i++) {
        k = 0;
        for (x = 1; CUBE(x) < i; x++) {
            for (y = x + 1; CUBE(x) + CUBE(y) <= i; y++) {
                if (CUBE(x) + CUBE(y) == i) {
                    k++;
                    x++;
                }
            }
        }
        if (k == 2) {
            checksum += i;
            count++;
        }
    }

    auto memory_usage = 8 * (sizeof(long));
    printf("%ld Ramanujan numbers up to %ld, checksum=%ld\n size=%ld\n",
           count, N, checksum, memory_usage);
    return 0;
}