#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

#define CUBE(n) (n*n*n)

 std::vector<int> ramanujan( int b) {
    std::vector<int> ramanujan_numbers;
    int i, x, y, k;

    for (i = 0; i < b; i++) {
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
            ramanujan_numbers.push_back(i);
        }
    }
    return  ramanujan_numbers;
}

int main(int argc, char *argv[]) {
    auto N = std::stol(argv[1], nullptr, 10);
    auto ramanujans = ramanujan(N);

    std::cout << "Ramanujan numbers up to " << N << ": " << ramanujans.size() << std::endl;
    auto memory_usage = sizeof(std::vector<int>) + (sizeof(int) * ramanujans.size());
    memory_usage += 5 * (sizeof(int));
    std::cout << "Memory usage: >=" << memory_usage;
    return 0;
}