#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

unsigned long cube(unsigned long n) {
    return n * n * n;
}

using result_type = std::pair<std::set<unsigned long>, std::vector<unsigned long>>;

result_type generate_ramanujan_numbers(unsigned long n) {
    std::set<unsigned long> ramanujan_candidates;
    std::vector<unsigned long> ramanujan_numbers;

    for (unsigned long i = 0; cube(i) <= n; i++) {
        for (unsigned long j = i + 1; cube(i) + cube(j) <= n; j++) {
            auto sum = cube(i) + cube(j);
            auto res = ramanujan_candidates.insert(sum);
            if (!res.second) {
                ramanujan_numbers.push_back(sum);
            }
        }
    }
    return {ramanujan_candidates, ramanujan_numbers};
}

int main(int argc, char *argv[]) {
    // parse argument for limit N
    auto N = std::stol(argv[1], nullptr, 10);
    auto [candidates, ramanujans] = generate_ramanujan_numbers(N);

    std::cout << "Ramanujan numbers up to " << N << ": " << ramanujans.size() << std::endl;
    auto memory_usage = sizeof(std::vector<unsigned long>) + (sizeof(unsigned long) * ramanujans.size());
    memory_usage += sizeof(std::set<unsigned long>) + (sizeof(unsigned long) * candidates.size());
    std::cout << "Memory usage: >=" << memory_usage;
    return 0;
}
