all: main

main: main.cpp
	g++ -std=c++11 -O3 -o main main.cpp

run: all
	./main --implementation BINARY < in.txt >1.out
	./lyh --implementation BINARY < in.txt >2.out
	diff 1.out 2.out
	diff 1.out 2.txt
	./main --implementation UNSORTED < in.txt >1.out
	./lyh --implementation UNSORTED < in.txt >2.out
	diff 1.out 2.out
	diff 1.out 2.txt
	./main --implementation FIBONACCI < in.txt >1.out
	./lyh --implementation FIBONACCI < in.txt >2.out
	diff 1.out 2.out
	diff 1.out 2.txt

runv: all
	./main --verbose -i BINARY < in.txt >1.out
	./lyh --verbose -i BINARY < in.txt >2.out
	diff 1.out 2.out
	./main --verbose -i UNSORTED < in.txt >1.out
	./lyh --verbose -i UNSORTED < in.txt >2.out
	diff 1.out 2.out
	./main --verbose -i FIBONACCI < in.txt >1.out
	./lyh --verbose -i FIBONACCI < in.txt >2.out
	diff 1.out 2.out

op: getop_test.cpp
	g++ -std=c++11 -O3 -o getop_test getop_test.cpp
	./getop_test --implementation BINARY
	./getop_test --i BINARY
	./getop_test --verbose -i UNSORTED
	./getop_test --v -i UNSORTED
	./getop_test --verbose -i FIBONACCI
	./getop_test --test -i BINARY

gen: gen_rand.cpp
	g++ -std=c++11 -O2 -o gen_rand_matrix gen_rand.cpp
	./gen_rand_matrix > matrix.in
	
un: test_heap_unsorted.cpp
	g++ -std=c++11 -O3 -o unsorted_heap test_heap_unsorted.cpp
	./unsorted_heap

bi: test_heap_binary.cpp
	g++ -std=c++11 -O3 -o binary_heap test_heap_binary.cpp
	./binary_heap

fib: test_heap_fib.cpp fib_heap.h
	g++ -std=c++11 -O3 -o fib_heap test_heap_fib.cpp
	./fib_heap

fibsw: test_heap_fib_sw.cpp
	g++ -std=c++11 -O3 -o fib_heap_sw test_heap_fib_sw.cpp
	./fib_heap_sw

perf: test_heap_performance.cpp
	g++ -std=c++11 -g -o performance test_heap_performance.cpp
	./performance

per: performance.cpp
	g++ -std=c++11 -O3 -o perform performance.cpp
	./perform < matrix.in > out.csv

v: test_heap_performance.cpp
	g++ -std=c++11 -g -o performance test_heap_performance.cpp
	valgrind --leak-check=full ./performance

vfi: test_heap_fib.cpp
	g++ -std=c++11 -O3 -o fib_heap test_heap_fib.cpp
	valgrind --leak-check=full ./fib_heap

vp: performance.cpp
	g++ -std=c++11 -O3 -o perform performance.cpp
	valgrind --leak-check=full ./perform < matrix.in > out.csv

clean:
	rm -f *.o fib_heap binary_heap unsorted_heap fib_heap_sw main performance
