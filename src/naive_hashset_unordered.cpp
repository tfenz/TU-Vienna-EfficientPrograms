#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <cmath>

unsigned long cube(unsigned long n) {
    return n * n * n;
}

using result_type = std::pair<std::unordered_set<unsigned long>, std::unordered_set<unsigned long>>;

result_type generate_ramanujan_numbers(unsigned long n, unsigned long *checksum, long bound) {
    std::unordered_set<unsigned long> ramanujan_candidates;

    ramanujan_candidates.reserve(bound);
    std::unordered_set<unsigned long> ramanujan_numbers;

    for (unsigned long i = 0; cube(i) <= n; i++) {
        for (unsigned long j = i + 1; cube(i) + cube(j) <= n; j++) {
            auto sum = cube(i) + cube(j);
            auto res = ramanujan_candidates.insert(sum);
            if (!res.second) {
                auto rama_res = ramanujan_numbers.insert(sum);
                if (rama_res.second) {
                    *checksum += sum;
                }
            }
        }
    }
    return {ramanujan_candidates, ramanujan_numbers};
}

int main(int argc, char *argv[]) {
    // parse argument for limit N
    auto N = std::stol(argv[1], nullptr, 10);
    unsigned long checksum = 0;
    long bound = 1 << (long) (log((double) N) * (2.0 / (3.0 * log(2.0))));
    // calculate ramanujan candidates and numbers
    auto [candidates, ramanujans] = generate_ramanujan_numbers(N, &checksum, bound);
    // estimate memory usage
    auto memory_usage = sizeof(std::unordered_set<unsigned long>) + (sizeof(unsigned long) * ramanujans.size());
    memory_usage += sizeof(std::unordered_set<unsigned long>) + (sizeof(unsigned long) * bound);

    std::cout << ramanujans.size() << " Ramanujan numbers up to " << N << ", checksum=" << checksum << std::endl;
    std::cout << "Memory usage: >=" << memory_usage;

    return 0;
}
