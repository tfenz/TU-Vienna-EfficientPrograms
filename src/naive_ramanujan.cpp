#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int cube(int n) {
    return n * n * n;
}

std::vector<int> generate_ramanujan_numbers(unsigned int n) {
    std::set<int> ramanujan_candidates;
    std::vector<int> ramanujan_numbers;
    auto limit = cube(n);
    for (size_t i = 0; cube(i) <= n; i++) {
        for (size_t j = i + 1; cube(i) + cube(j) <= n; j++) {
            auto num = cube(i) + cube(j);
            auto res = ramanujan_candidates.insert(num);
            if (!res.second) {
                ramanujan_numbers.push_back(num);
            }
        }
    }
    return ramanujan_numbers;
}

int main(int argc, char *argv[]) {
    // parse argument for limit N
    auto N = std::stol(argv[1], nullptr, 10);
    auto ramanujans = generate_ramanujan_numbers(N);
    std::cout << "Ramanujan numbers up to " << N << ": " << ramanujans.size() << std::endl;
    return 0;
}
