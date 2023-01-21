#Memory in KB
MEMORY = 100000
N = 1000000000000
BUCKET_SIZE = 1024
NAIVERAMA = naive_ramanujan
CACHE_SET_RAMANUJAN = cache_set_ramanujan
CACHE_SET_NO_STRUCT = cache_set_no_struct
RAMASORT_OPT = ramasort_opt
RAMANUJAN_OPT = ramanujan_opt
#C++ compiler flags
CXX = g++
CFLAGS = -std=c++17 -O3 -Wall
#C compiler flags
CC = gcc
CFLAGS = -O3 -Wall
SRC_DIR = ./src/
INCLUDE_DIR=-I./include/

bench-naive_t1: $(NAIVERAMA)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(NAIVERAMA) $(N)

bench-naive_ramanujan: $(NAIVERAMA)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(NAIVERAMA) $(N)

bench-cache_set_ramanujan: $(CACHE_SET_RAMANUJAN)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(CACHE_SET_RAMANUJAN) $(N) $(BUCKET_SIZE)

bench-cache_set_no_struct: $(CACHE_SET_NO_STRUCT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(CACHE_SET_NO_STRUCT) $(N) $(BUCKET_SIZE)

bench-ramasort_opt: $(RAMASORT_OPT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMASORT_OPT) $(N)

bench-ramanujan_opt: $(RAMANUJAN_OPT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMANUJAN_OPT) $(N)


clean:
	rm naive_ramanujan cache_set_ramanujan cache_set_no_struct ramasort_opt ramanujan_opt

naive_ramanujan:
	$(CXX) $(CFLAGS) $(SRC_DIR)naive_ramanujan.cpp -lm -o naive_ramanujan

cache_set_ramanujan:
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(SRC_DIR)optimized_ramanujan.cpp -lm -o cache_set_ramanujan

cache_set_no_struct:
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(SRC_DIR)optimized_ramanujan_no_struct.cpp -lm -o cache_set_no_struct

ramasort_opt:
	$(CC) $(CFLAGS) src/ramasort_opt.c -lm -o ramasort_opt

ramanujan_opt:
	$(CC) $(CFLAGS) src/ramanujan_opt.c -lm -o ramanujan_opt

