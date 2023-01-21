#Memory in KB
MEMORY = 1000000
N = 1000000
BUCKET_SIZE = 32

REHASHING = ramanujan_rehashing
RAMANUJAN_2HASHSETS_UNORDERED = ramanujan_2hashsets_unordered
THREELOOPS = 3loops
NAIVE_HASHSET = naive_hashset
NAIVE_HASHSET_UNORDERED = naive_hashset_unordered
BUCKET_HASHING = bucket_hashing
RAMASORT_OPT = ramasort_opt
RAMANUJAN_OPT = ramanujan_opt

#C++ compiler flags
CXX = g++
CPPFLAGS = -std=c++17 -O3 -Wall

#C compiler flags
CC = gcc
CFLAGS = -O3 -Wall
SRC_DIR = ./src/
INCLUDE_DIR=-I./include/

bench-rehashing: $(REHASHING)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(REHASHING) $(N)

bench-2hashsets_unordered: $(RAMANUJAN_2HASHSETS_UNORDERED)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMANUJAN_2HASHSETS_UNORDERED) $(N)

bench-3loops: $(THREELOOPS)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(THREELOOPS) $(N)

bench-naive_hashset: $(NAIVE_HASHSET)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(NAIVE_HASHSET) $(N)

bench-naive_hashset_unordered: $(NAIVE_HASHSET_UNORDERED)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(NAIVE_HASHSET_UNORDERED) $(N)

bench-bucket_hashing: $(BUCKET_HASHING)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(BUCKET_HASHING) $(N) $(BUCKET_SIZE)

bench-ramasort_opt: $(RAMASORT_OPT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMASORT_OPT) $(N)

bench-ramanujan_opt: $(RAMANUJAN_OPT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMANUJAN_OPT) $(N)


ramanujan_rehashing:
	$(CXX) $(CPPFLAGS) $(SRC_DIR)ramanujan_rehashing.cpp -lm -o ramanujan_rehashing

ramanujan_2hashsets_unordered:
	$(CXX) $(CPPFLAGS) $(SRC_DIR)ramanujan_2hashsets_unordered.cpp -lm -o ramanujan_2hashsets_unordered

3loops:
	$(CXX) $(CPPFLAGS) $(SRC_DIR)3loops.cpp -lm -o 3loops

naive_hashset:
	$(CXX) $(CPPFLAGS) $(SRC_DIR)naive_hashset.cpp -lm -o naive_hashset

naive_hashset_unordered:
	$(CXX) $(CPPFLAGS) $(SRC_DIR)naive_hashset_unordered.cpp -lm -o naive_hashset_unordered

bucket_hashing:
	$(CXX) $(CPPFLAGS) $(INCLUDE_DIR) $(SRC_DIR)bucket_hashing.cpp -lm -o bucket_hashing

ramasort_opt:
	$(CC) $(CFLAGS) $(SRC_DIR)ramasort_opt.c -lm -o ramasort_opt

ramanujan_opt:
	$(CC) $(CFLAGS) $(SRC_DIR)ramanujan_opt.c -lm -o ramanujan_opt



clean:
	rm ramanujan_rehashing ramanujan_2hashsets_unordered 3loops naive_hashset naive_hashset_unordered bucket_hashing ramasort_opt ramanujan_opt