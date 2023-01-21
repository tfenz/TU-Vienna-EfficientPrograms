#Memory in KB
MEMORY = 100000
N = 1000
BUCKET_SIZE = 32

NAIVE_HASHSET = naive_hashset
REHASHING = ramanujan_rehashing
BUCKET_HASHING = bucket_hashing
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

bench-bucket_hashing: $(BUCKET_HASHING)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(BUCKET_HASHING) $(N) $(BUCKET_SIZE)

bench-ramasort_opt: $(RAMASORT_OPT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMASORT_OPT) $(N)

bench-ramanujan_opt: $(RAMANUJAN_OPT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMANUJAN_OPT) $(N)


ramanujan_rehashing:
	$(CXX) $(CFLAGS) $(SRC_DIR)ramanujan_rehashing.cpp -lm -o ramanujan_rehashing

3loops:
	$(CXX) $(CFLAGS) $(SRC_DIR)3loops.cpp -lm -o naive_ramanujan

naive_hashset:
	$(CXX) $(CFLAGS) $(SRC_DIR)naive_hashset.cpp -lm -o naive_ramanujan

bucket_hashing:
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(SRC_DIR)bucket_hashing.cpp -lm -o bucket_hashing

ramasort_opt:
	$(CC) $(CFLAGS) $(SRC_DIR)ramasort_opt.c -lm -o ramasort_opt

ramanujan_opt:
	$(CC) $(CFLAGS) $(SRC_DIR)ramanujan_opt.c -lm -o ramanujan_opt



clean:
	rm naive_ramanujan cache_set_ramanujan cache_set_no_struct ramasort_opt ramanujan_opt