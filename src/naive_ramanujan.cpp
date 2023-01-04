#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int cube(int n) {
    return n * n * n;
}

std::vector<int> generate_ramanujan_numbers(unsigned int limit) {
    std::vector<int> ramanujan_candidates;
    ramanujan_candidates.reserve(limit * limit);
    for (size_t i = 0; i < limit; i++) {
        for (size_t j = i + 1; j < limit; j++) {
            auto res = cube(i) + cube(j);
            ramanujan_candidates.push_back(res);
        }
    }
    return ramanujan_candidates;
}

int main() {
    const unsigned int N = 30;
    auto ramanujan_candidates = generate_ramanujan_numbers(N);
    std::set<int> uniques;
    std::vector<int> rama_numbers;
    for (auto &i: ramanujan_candidates) {
        auto res = uniques.insert(i);
        if (!res.second) {
            rama_numbers.push_back(i);
        }
    }
    std::cout << "Ramanujan numbers up to " << N << ": " << rama_numbers.size() << std::endl;

    return 0;
}
