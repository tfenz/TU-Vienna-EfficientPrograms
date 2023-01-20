

#ifndef RAMANUJAN_NUMBERS_CACHE_SET_OPT_H
#define RAMANUJAN_NUMBERS_CACHE_SET_OPT_H

#include <utility>
#include <cmath>
#include <vector>


class cache_set_no_struct {
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
    std::vector<std::vector<unsigned long>> cache_candidates{};
    std::vector<std::vector<char>> cache_counts{};


    void init_cache_sections();

public:
    cache_set_no_struct(unsigned long ramanujan_limit_n, size_t avg_bucket_size);

    void insert(unsigned long candidate);

    size_t get_size();

    size_t get_num_cache_buckets();

    unsigned long get_ramanujan_candidate_bound();

    unsigned long get_ramanujan_limit_n();

    unsigned long get_cache_line_size();

    unsigned long get_checksum();

    size_t get_capacity();

    unsigned long get_ramanujan_numbers_count();

    std::vector<unsigned long> get_cache_candidates();
    std::vector<char> get_cache_counts();

};

size_t cache_set_no_struct::get_num_cache_buckets() {
    return this->num_cache_buckets;
}

cache_set_no_struct::cache_set_no_struct(unsigned long ramanujan_limit_n,
                                          size_t avg_bucket_size) {
    this->ramanujan_limit_n = ramanujan_limit_n;
    this->avg_bucket_size = avg_bucket_size;
    this->ramanujan_candidates_bound = std::exp(
            std::log((double) this->ramanujan_limit_n) * (2.0 / 3.0)) / 2 + 100;
    // initiliaze cache's buckets
    this->init_cache_sections();
}


void cache_set_no_struct::init_cache_sections() {
    this->num_cache_buckets = std::ceil(this->ramanujan_candidates_bound / float(this->avg_bucket_size));

    this->cache_candidates.reserve(this->num_cache_buckets);
    this->cache_counts.reserve(this->num_cache_buckets);

    for (size_t i = 0; i < this->cache_candidates.capacity(); ++i) {
        this->cache_candidates[i].reserve(this->avg_bucket_size);
        this->cache_counts.reserve(this->num_cache_buckets);
    }
}


void cache_set_no_struct::insert(unsigned long candidate) {
    auto cache_bucket_idx = candidate % this->num_cache_buckets;
    // search through bucket, if value is already stored -> increase count
    for (size_t i = 0; i < this->cache_candidates[cache_bucket_idx].size(); ++i) {
        if (this->cache_candidates[cache_bucket_idx][i] == candidate) {
            cache_counts[cache_bucket_idx][i]++;
            if (this->cache_counts[cache_bucket_idx][i] == 2) {
                this->checksum += candidate;
                this->ramanujan_numbers_count += 1;
            }
            return;
        }
    }

    // candidate.count++;
    this->cache_candidates[cache_bucket_idx].push_back(candidate);
    this->cache_counts[cache_bucket_idx].push_back(1);
    this->size++;
}

size_t cache_set_no_struct::get_capacity() {
    auto capacity = 0;

    for (size_t i = 0; i < this->cache_counts.size(); ++i) {
        capacity += cache_counts[i].capacity();
        capacity += cache_candidates[i].capacity();
    }
    return capacity;
}


size_t cache_set_no_struct::get_size() {
    return this->size;
}


unsigned long cache_set_no_struct::get_ramanujan_candidate_bound() {
    return this->ramanujan_candidates_bound;
}

unsigned long cache_set_no_struct::get_ramanujan_limit_n() {
    return this->ramanujan_limit_n;
}

unsigned long cache_set_no_struct::get_cache_line_size() {
    return this->avg_bucket_size;
}



unsigned long cache_set_no_struct::get_ramanujan_numbers_count() {
    return this->ramanujan_numbers_count;
}


unsigned long cache_set_no_struct::get_checksum() {
    return this->checksum;
}


#endif //RAMANUJAN_NUMBERS_CACHE_SET_OPT_H
