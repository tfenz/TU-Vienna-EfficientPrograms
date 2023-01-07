#Memory in KB
MEMORY = 9000000
N = 10000000000000
NAIVERAMA = naive_ramanujan
CACHE_SET_RAMANUJAN = cache_set_ramanujan
CXX = g++
CFLAGS = -std=c++17 -O3 -Wall
SRC_DIR = ./src/
INCLUDE_DIR=-I./include/

bench-naive_ramanujan: $(NAIVERAMA)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(NAIVERAMA) $(N)

bench-cache_set_ramanujan: $(CACHE_SET_RAMANUJAN)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(CACHE_SET_RAMANUJAN) $(N)


clean:
	rm naive_ramanujan cache_set_ramanujan

naive_ramanujan:
	$(CXX) $(CFLAGS) $(SRC_DIR)naive_ramanujan.cpp -lm -o naive_ramanujan

cache_set_ramanujan:
	$(CXX) $(CFLAGS) $(INCLUDE_DIR) $(SRC_DIR)optimized_ramanujan.cpp -lm -o cache_set_ramanujan

