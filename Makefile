#Memory in KB
MEMORY = 102400
N = 1000000
NAIVERAMA = naive_ramanujan
CXX = g++
CFLAGS = -O3 -Wall
SRC_DIR = ./src/

bench-naive_ramanujan: $(NAIVERAMA)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(NAIVERAMA) $(N)

clean:
	rm naive_ramanujan

naive_ramanujan:
	$(CXX) $(CFLAGS) $(SRC_DIR)naive_ramanujan.cpp -lm -o naive_ramanujan

