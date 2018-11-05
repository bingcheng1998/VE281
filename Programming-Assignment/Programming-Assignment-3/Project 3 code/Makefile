all: main

main: main.cpp
	g++ -std=c++11 -O3 -o main main.cpp

run:
	./main --verbose -i FIBONACCI < 1.txt

val:


op: getop_test.cpp
	g++ -std=c++11 -O3 -o getop_test getop_test.cpp
	./getop_test --implementation BINARY
	./getop_test --i BINARY
	./getop_test --verbose -i UNSORTED
	./getop_test --v -i UNSORTED
	./getop_test --verbose -i FIBONACCI
	./getop_test --test -i BINARY
	
un: unsorted_heap.cpp
	g++ -std=c++11 -O3 -o unsorted_heap unsorted_heap.cpp
	./unsorted_heap

clean:
	rm -f *.o
