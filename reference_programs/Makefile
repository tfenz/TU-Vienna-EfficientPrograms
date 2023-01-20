#Memory in KB
MEMORY = 100000
N = 1000000000000
RAMASORT = ramasort
RAMANUJAN = ramanujan
CC = gcc
CFLAGS = -O3 -Wall

SOURCES = ramasort.c ramanujan.c Makefile

bench-ramasort: $(RAMASORT)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMASORT) $(N)

bench-ramanujan: $(RAMANUJAN)
	ulimit -S -v $(MEMORY); perf stat -e cycles -e instructions -e branch-misses -e LLC-load-misses -e LLC-store-misses ./$(RAMANUJAN) $(N)

clean:
	rm ramasort ramanujan

ramanujan: ramanujan.c
	$(CC) $(CFLAGS) ramanujan.c -lm -o ramanujan

ramasort: ramasort.c
	$(CC) $(CFLAGS) ramasort.c -lm -o ramasort

dist: ../ramanujan.tar.gz

../ramanujan.tar.gz: $(SOURCES)
	cd .. && tar cfz ramanujan.tar.gz ramanujan/ramasort.c ramanujan/ramanujan.c ramanujan/Makefile
