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
    unsigned long ramanujan_limit_n{};
    // bound of max. number of candidates up to N (i^3 + j^3 <= N)
    // calculate via: exp(log((double)n)*(2.0/3.0))/2+100;
    unsigned long ramanujan_candidates_bound{};
    // amount of ramanujan numbers found
    unsigned long ramanujan_numbers_count{};
    // checksum
    unsigned long checksum{};
    // cache size of the hardware
    size_t cache_line_size{};
    // stored ramanujan candidate numbers
    size_t size{};
    // number of cache buckets -> cache_buckets = this->ramanujan_limit_n / cache_line_size
    size_t num_cache_buckets{};
    // cache indexer
    std::vector<std::vector<T> *> caches{};

    void init_cache_sections();

public:
    cache_set(unsigned long ramanujan_candidates_bound, long long cache_line_size);

    void insert(T value);

    size_t get_size();

    size_t get_num_cache_buckets();

    unsigned long get_ramanujan_candidate_bound();

    unsigned long get_ramanujan_limit_n();

    unsigned long get_cache_line_size();

    unsigned long get_checksum();

    unsigned long get_ramanujan_numbers_count();

    std::vector<std::vector<T> *> get_cache_buckets();
};

template<typename T>
size_t cache_set<T>::get_num_cache_buckets() {
    return this->num_cache_buckets;
}

template<typename T>
cache_set<T>::cache_set(unsigned long ramanujan_limit_n,
                        long long cache_line_size) {
    this->ramanujan_limit_n = ramanujan_limit_n;
    this->cache_line_size = cache_line_size;
    this->ramanujan_candidates_bound = std::exp(
            std::log((double) this->ramanujan_limit_n) * (2.0 / 3.0)) / 2 + 100;
    // initiliaze cache's buckets
    this->init_cache_sections();
}

template<typename T>
void cache_set<T>::init_cache_sections() {
    this->num_cache_buckets = std::ceil(this->ramanujan_limit_n / cache_line_size);
    this->caches.reserve(num_cache_buckets);
    for (size_t i = 0; i < this->caches.capacity(); ++i) {
        this->caches.push_back(new std::vector<T>);
        this->caches[i]->reserve(this->ramanujan_candidates_bound);
    }
}

template<typename T>
void cache_set<T>::insert(T value) {
    auto cache_bucket_idx = value % this->num_cache_buckets;
    auto bucket = this->caches[cache_bucket_idx];
    bucket->push_back(value);
    this->size++;
}

template<typename T>
size_t cache_set<T>::get_size() {
    return this->size;
}

template<typename T>
std::vector<std::vector<T> *> cache_set<T>::get_cache_buckets() {
    return this->caches;
}


template<typename T>
unsigned long cache_set<T>::get_ramanujan_candidate_bound() {
    return this->ramanujan_candidates_bound;
}

template<typename T>
unsigned long cache_set<T>::get_ramanujan_limit_n() {
    return this->ramanujan_limit_n;
}

template<typename T>
unsigned long cache_set<T>::get_cache_line_size() {
    return this->cache_line_size;
}

template<typename T>
unsigned long cache_set<T>::get_ramanujan_numbers_count() {
    return this->ramanujan_numbers_count;
}

template<typename T>
unsigned long cache_set<T>::get_checksum() {
    return this->checksum;
}

#endif //RAMANUJAN_NUMBERS_CACHE_SET_H
