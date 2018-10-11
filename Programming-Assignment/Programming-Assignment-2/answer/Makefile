all: main.o selection.o
	g++ -std=c++11 -O3 -g -Wall -o main main.o selection.o

auto: make_auto
	./autogen

make_auto: auto_gen.o
	g++ -std=c++11 -O3 -g -Wall -o autogen auto_gen.o

auto_gen.o: auto_gen.cpp
	g++ -std=c++11 -O3 -g -Wall -c auto_gen.cpp

t: make_test
	./test

make_test: simple_test.o selection.o
	g++ -std=c++11 -O3 -g -Wall -o test simple_test.o selection.o

simple_test.o: simple_test.cpp
	g++ -std=c++11 -O3 -g -Wall -c simple_test.cpp

test0: gen all
	./generate 0 40000 2000 > input.data
	./main < input.data

test1: gen all
	./generate 1 40000 2000 > input.data
	./main < input.data

gen:
	g++ -std=c++11 -O3 -Wall -o generate gen_rand.cpp

p: perf
	./perform 

perf: performance.o selection.o
	g++ -std=c++11 -O3 -g -Wall -o perform performance.o selection.o

performance.o: performance.cpp
	g++ -std=c++11 -O3 -g -Wall -c performance.cpp

main.o: main.cpp
	g++ -std=c++11 -O3 -g -Wall -c main.cpp

selection.o: selection.cpp
	g++ -std=c++11 -O3 -g -Wall -c selection.cpp

run: all
	./main < input.data

v:
	valgrind --leak-check=full ./main < 1000num

tar:
	tar czvf p1.tar main.cpp sort.cpp sort.h

clean:
	rm -f ./main *.o *.data test
