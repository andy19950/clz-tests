CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall -fopenmp -mavx 
EXECUTABLE = \
	time_test_clz time_test_clz_Harley benchmark_clock_gettime

default: clz.o
	$(CC) $(CFLAGS) clz.o time_test.c -DCLZ -o time_test_clz
	$(CC) $(CFLAGS) clz.o time_test.c -DHARLEY -o time_test_clz_Harley
	$(CC) $(CFLAGS) clz.o benchmark_clock_gettime.c -o benchmark_clock_gettime

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

check: default
	time ./time_test_clz
	time ./time_test_clz_Harley

gencsv: default
	for i in `seq 100000 10000 1000000`; do \
		printf "%d " $$i;\
		./benchmark_clock_gettime $$i; \
	done > result_clock_gettime.csv
	gnuplot runtime.gp
	eog runtime.png	

clean:
	rm -f $(EXECUTABLE) *.o *.s result_clock_gettime.csv
