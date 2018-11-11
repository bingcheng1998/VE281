all: main

main: main.cpp
	g++ -std=c++11 -O3 -o main main.cpp

run: all
	./main --implementation BINARY < in.txt >1.out
	./lyh --implementation BINARY < in.txt >2.out
	diff 1.out 2.out
	./main --implementation UNSORTED < in.txt >1.out
	./lyh --implementation UNSORTED < in.txt >2.out
	diff 1.out 2.out
	./main --implementation FIBONACCI < in.txt >1.out
	./lyh --implementation FIBONACCI < in.txt >2.out
	diff 1.out 2.out

runv: all
	./main -v -i BINARY < in.txt >1.out
	./lyh --verbose -i BINARY < in.txt >2.out
	diff 1.out 2.out
	./main -v -i UNSORTED < in.txt >1.out
	./lyh -v -i UNSORTED < in.txt >2.out
	diff 1.out 2.out
	./main -v -i FIBONACCI < in.txt >1.out
	./lyh --verbose -i FIBONACCI < in.txt >2.out
	diff 1.out 2.out


chack_memory_leak: all
	valgrind --leak-check=full ./main --verbose -i FIBONACCI < in.txt >1.out

clean:
	rm -f *.o *.out fib_heap binary_heap unsorted_heap fib_heap_sw main performance


tar:
	tar czvf p3.tar Makefile main.cpp binary_heap.h fib_heap.h priority_queue.h unsorted_heap.h P3.pdf
