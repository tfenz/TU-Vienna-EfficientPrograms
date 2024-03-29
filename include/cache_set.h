//
// Created by david on 06.01.23.
//

#include <utility>
#include <cmath>
#include <vector>

#ifndef RAMANUJAN_NUMBERS_CACHE_SET_H
#define RAMANUJAN_NUMBERS_CACHE_SET_H


struct ramanujan_candidate {
    unsigned long value{};
    char count{};
};

template<typename ramanujan_candidate>
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
    size_t avg_bucket_size{};
    // stored ramanujan candidate numbers
    size_t size{};
    // number of cache buckets -> cache_buckets = this->ramanujan_limit_n / avg_bucket_size
    size_t num_cache_buckets{};
    // cache indexer
    std::vector<std::vector<ramanujan_candidate>> caches{};

    void init_cache_sections();

    size_t hash4(unsigned long candidate);

public:
    cache_set(unsigned long ramanujan_limit_n, size_t avg_bucket_size);

    void insert(ramanujan_candidate candidate);

    size_t get_size();

    size_t get_num_cache_buckets();

    unsigned long get_ramanujan_candidate_bound();

    unsigned long get_ramanujan_limit_n();

    unsigned long get_cache_line_size();

    unsigned long get_checksum();

    size_t get_capacity();

    unsigned long get_ramanujan_numbers_count();

    std::vector<std::vector<ramanujan_candidate>> get_cache_buckets();
};

template<typename ramanujan_candidate>
size_t cache_set<ramanujan_candidate>::hash4(unsigned long h) {
    h ^= (h >> 20) ^ (h >> 12);
    h = h ^ (h >> 7) ^ (h >> 4);
    return h % this->num_cache_buckets;
}

template<typename ramanujan_candidate>
size_t cache_set<ramanujan_candidate>::get_num_cache_buckets() {
    return this->num_cache_buckets;
}

template<typename ramanujan_candidate>
cache_set<ramanujan_candidate>::cache_set(unsigned long ramanujan_limit_n,
                                          size_t avg_bucket_size) {
    this->ramanujan_limit_n = ramanujan_limit_n;
    this->avg_bucket_size = avg_bucket_size;
    // this->ramanujan_candidates_bound = std::exp(
    //         std::log((double) this->ramanujan_limit_n) * (2.0 / 3.0)) / 2 + 100;
    this->ramanujan_candidates_bound = 1<<(long)(log((double)this->ramanujan_limit_n)*(2.0/(3.0*log(2.0))));
    // initiliaze cache's buckets
    this->init_cache_sections();
}


template<typename ramanujan_candidate>
void cache_set<ramanujan_candidate>::init_cache_sections() {
    this->num_cache_buckets = std::ceil(this->ramanujan_candidates_bound / float(this->avg_bucket_size));

    this->caches.reserve(this->num_cache_buckets);
    for (size_t i = 0; i < this->caches.capacity(); ++i) {
        this->caches[i].reserve(this->avg_bucket_size);
    }
}

template<typename ramanujan_candidate>
void cache_set<ramanujan_candidate>::insert(ramanujan_candidate candidate) {
    auto cache_bucket_idx = this->hash4(candidate.value);//candidate.value % this->num_cache_buckets;
    // search through bucket, if value is already stored -> increase count
    for (size_t i = 0; i < this->caches[cache_bucket_idx].size(); ++i) {
        if (this->caches[cache_bucket_idx][i].value == candidate.value) {
            caches[cache_bucket_idx][i].count++;
            if (this->caches[cache_bucket_idx][i].count == 2) {
                this->checksum += candidate.value;
                this->ramanujan_numbers_count += 1;
            }
            return;
        }
    }

    candidate.count++;
    this->caches[cache_bucket_idx].push_back(candidate);
    this->size++;
}

template<typename ramanujan_candidate>
size_t cache_set<ramanujan_candidate>::get_capacity() {
    auto capacity = 0;
    for (auto &cache_buckets: this->caches) {
        capacity += cache_buckets.capacity();
    }
    return capacity;
}

template<typename ramanujan_candidate>
size_t cache_set<ramanujan_candidate>::get_size() {
    return this->size;
}

template<typename ramanujan_candidate>
std::vector<std::vector<ramanujan_candidate>> cache_set<ramanujan_candidate>::get_cache_buckets() {
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
    return this->avg_bucket_size;
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
