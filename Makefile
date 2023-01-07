#Memory in KB
MEMORY = 102400
N = 1000000
NAIVERAMA = naive_ramanujan
CACHE_SET_RAMANUJAN = cache_set_ramanujan
CXX = g++
CFLAGS = -std=c++17 -O3 -Wall
SRC_DIR = ./src/

bench-naive_ramanujan: $(NAIVERAMA)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(NAIVERAMA) $(N)

bench-cache_set_ramanujan: $(CACHE_SET_RAMANUJAN)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(CACHE_SET_RAMANUJAN) $(N)


clean:
	rm naive_ramanujan

naive_ramanujan:
	$(CXX) $(CFLAGS) $(SRC_DIR)naive_ramanujan.cpp -lm -o naive_ramanujan

cache_set_ramanujan:
	$(CXX) $(CFLAGS) $(SRC_DIR)naive_ramanujan.cpp -lm -o cache_set_ramanujan

