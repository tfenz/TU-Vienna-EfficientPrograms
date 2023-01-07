//
// Created by david on 06.01.23.
//

#include <utility>
#include <cmath>
#include <vector>

#ifndef RAMANUJAN_NUMBERS_CACHE_SET_H
#define RAMANUJAN_NUMBERS_CACHE_SET_H

template<typename T>
class cache_set {
private:
    // N := limit of ramanujan number calculation
    unsigned long ramanujan_candidate_limit{};
    // bound of max. number of candidates up to N (i^3 + j^3 <= N)
    // calculate via: exp(log((double)n)*(2.0/3.0))/2+100;
    unsigned long ramanujan_candidates_bound{};
    // cache size of the hardware
    size_t cache_line_size{};
    // stored ramanujan candidate numbers
    size_t set_size{};
    // number of cache sections -> cache_sections =
    size_t cache_sections_count{};
    // cache indexer
    using cache_type = std::vector<std::vector<T>>;
    cache_type caches{};
    void init_cache_sections();

public:
    cache_set(unsigned long ramanujan_candidates_bound, long long cache_line_size);

    std::pair<int, bool> insert(T value);

    size_t get_size();

    size_t get_cache_sections_count();

    unsigned long get_ramanujan_candidate_bound();

    unsigned long get_ramanujan_candidate_limit();
};


template<typename T>
cache_set<T>::cache_set(unsigned long ramanujan_candidates_bound,
                        long long cache_line_size) {
    this->ramanujan_candidates_bound = ramanujan_candidates_bound;
    this->ramanujan_candidate_limit = std::exp(
            std::log((double) this->ramanujan_candidates_bound) * (2.0 / 3.0)) / 2 + 100;
    // initiliaze caches
    this->init_cache_sections();

}


template<typename T>
void cache_set<T>::init_cache_sections() {

}

template<typename T>
size_t cache_set<T>::get_size() {
    return 0;
}

template<typename T>
size_t cache_set<T>::get_cache_sections_count() {
    return 0;
}

template<typename T>
std::pair<int, bool> cache_set<T>::insert(T value) {

}

template<typename T>
unsigned long cache_set<T>::get_ramanujan_candidate_bound() {
    return this->ramanujan_candidates_bound;
}

template<typename T>
unsigned long cache_set<T>::get_ramanujan_candidate_limit() {
    return this->ramanujan_candidate_limit;
}

#endif //RAMANUJAN_NUMBERS_CACHE_SET_H
