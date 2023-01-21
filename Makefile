#Memory in KB
MEMORY = 100000
N = 1000
BUCKET_SIZE = 32

NAIVE_HASHSET = naive_hashset
REHASHING = ramanujan_rehashing
CACHE_SET_RAMANUJAN = cache_set_ramanujan
CACHE_SET_NO_STRUCT = cache_set_no_struct
RAMASORT_OPT = ramasort_opt
RAMANUJAN_OPT = ramanujan_opt
THREELOOPS = 3loops

#C++ compiler flags
CXX = g++
CFLAGS = -std=c++17 -O3 -Wall

#C compiler flags
CC = gcc
CFLAGS = -O3 -Wall
SRC_DIR = ./src/
INCLUDE_DIR=-I./include/

bench-rehashing: $(REHASHING)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(REHASHING) $(N)

bench-3loops: $(THREELOOPS)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(THREELOOPS) $(N)

bench-naive_ramanujan: $(NAIVERAMA)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(NAIVERAMA) $(N)

bench-cache_set_ramanujan: $(CACHE_SET_RAMANUJAN)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(CACHE_SET_RAMANUJAN) $(N) $(BUCKET_SIZE)

bench-ramasort_opt: $(RAMASORT_OPT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMASORT_OPT) $(N)

bench-ramanujan_opt: $(RAMANUJAN_OPT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMANUJAN_OPT) $(N)


naive_hashset:
	$(CXX) $(CFLAGS) $(SRC_DIR)naive_hashset.cpp -lm -o naive_ramanujan

ramanujan_rehashing:
	$(CXX) $(CFLAGS) $(SRC_DIR)ramanujan_rehashing.cpp -lm -o ramanujan_rehashing

bucket_hashing:
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(SRC_DIR)bucket_hashing.cpp -lm -o bucket_hashing

ramasort_opt:
	$(CC) $(CFLAGS) $(SRC_DIR)ramasort_opt.c -lm -o ramasort_opt

ramanujan_opt:
	$(CC) $(CFLAGS) $(SRC_DIR)ramanujan_opt.c -lm -o ramanujan_opt

3loops:
	$(CXX) $(CFLAGS) $(SRC_DIR)3loops.cpp -lm -o naive_ramanujan


clean:
	rm naive_ramanujan cache_set_ramanujan cache_set_no_struct ramasort_opt ramanujan_opt