CC = g++
CFLAGS = \
	-O0 -std=gnu99 -Wall
LDFLAGS = \
	-lm
EXECUTABLE = \
	time_test_clz_recur time_test_clz_itera time_test_clz_Harley benchmark_clock_gettime

default: clz.o
	$(CC) $(CFLAGS) clz.o time_test.c -DRECUR -o time_test_clz_recur
	$(CC) $(CFLAGS) clz.o time_test.c -DITERA -o time_test_clz_itera
	$(CC) $(CFLAGS) clz.o time_test.c -DHARLEY -o time_test_clz_Harley
	$(CC) $(CFLAGS) clz.o benchmark_clock_gettime.c -o benchmark_clock_gettime

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

check: default
	time ./time_test_clz_recur
	time ./time_test_clz_itera
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
