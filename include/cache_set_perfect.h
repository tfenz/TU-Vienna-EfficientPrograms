//
// Created by david on 20.01.23.
//

#include <utility>
#include <cmath>
#include <vector>

#ifndef RAMANUJAN_NUMBERS_CACHE_SET_PERFECT_H
#define RAMANUJAN_NUMBERS_CACHE_SET_PERFECT_H

struct ramanujan_candidate {
    unsigned long value{};
    char count{};
};

template <typename T>
class cache_set_perfect {
private:
    size_t size{};
    unsigned long limit_n{};
    unsigned long init_table_size{};

public:
    explicit cache_set_perfect(unsigned long limit_n);

    size_t get_size();

    unsigned long get_limit_n();

    unsigned long get_init_table_size();

    std::vector<T> table{};
};

template<typename T>
unsigned long cache_set_perfect<T>::get_init_table_size() {
    return this->init_table_size;
}

template<typename T>
unsigned long cache_set_perfect<T>::get_limit_n() {
    return this->limit_n;
}

template<typename T>
size_t cache_set_perfect<T>::get_size() {
    return this->size;
}

template<typename T>
cache_set_perfect<T>::cache_set_perfect(unsigned long limit_n) {
    this->limit_n = limit_n;
    this->init_table_size = std::exp(std::log((double) this->limit_n ) * (2.0 / 3.0)) / 2 + 100;
    this->table.reserve(this->init_table_size);
}



#endif //RAMANUJAN_NUMBERS_CACHE_SET_PERFECT_H
