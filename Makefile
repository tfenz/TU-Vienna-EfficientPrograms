#Memory in KB
MEMORY = 100000
N = 1000000000000
BUCKET_SIZE = 1024
NAIVERAMA = naive_ramanujan
CACHE_SET_RAMANUJAN = cache_set_ramanujan
CACHE_SET_NO_STRUCT = cache_set_no_struct
CXX = g++
CFLAGS = -std=c++17 -O3 -Wall
SRC_DIR = ./src/
INCLUDE_DIR=-I./include/

bench-naive_ramanujan: $(NAIVERAMA)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(NAIVERAMA) $(N)

bench-cache_set_ramanujan: $(CACHE_SET_RAMANUJAN)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(CACHE_SET_RAMANUJAN) $(N) $(BUCKET_SIZE)

bench-cache_set_no_struct: $(CACHE_SET_NO_STRUCT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(CACHE_SET_NO_STRUCT) $(N) $(BUCKET_SIZE)

clean:
	rm naive_ramanujan cache_set_ramanujan cache_set_no_struct

naive_ramanujan:
	$(CXX) $(CFLAGS) $(SRC_DIR)naive_ramanujan.cpp -lm -o naive_ramanujan

cache_set_ramanujan:
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(SRC_DIR)optimized_ramanujan.cpp -lm -o cache_set_ramanujan

cache_set_no_struct:
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(SRC_DIR)optimized_ramanujan_no_struct.cpp -lm -o cache_set_no_struct

