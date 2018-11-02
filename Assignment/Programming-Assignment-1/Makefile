all: main.o sort.o
	g++  -g -Wall -o main main.o sort.o

auto: make_auto
	./autogen

make_auto: auto_gen.o
	g++  -g -Wall -o autogen auto_gen.o

auto_gen.o: auto_gen.cpp
	g++ -g -Wall -c auto_gen.cpp

gen_all:
	./generate 0 10 > 0.txt
	./generate 0 15 > 1.txt
	./generate 0 20 > 2.txt
	./generate 0 30 > 3.txt
	./generate 0 40 >4.txt
	./generate 0 60 > 5.txt
	./generate 0 80 > 6.txt
	./generate 0 100 > 7.txt
	./generate 0 500 > 8.txt
	./generate 0 1000 > 9.txt
	./generate 0 1500 > 10.txt
	./generate 0 2000 > 11.txt
	./generate 0 4000 > 12.txt
	./generate 0 10000 > 13.txt
	./generate 0 50000 > 14.txt
	./generate 0 100000 > 15.txt
	./generate 0 500000 > 16.txt
	./generate 0 1000000 > 17.txt
	./generate 0 5000000 > 18.txt
	./generate 0 10000000 > 19.txt


test0: gen all
	./generate 0 40000 > input.txt
	./main < input.txt

test1: gen all
	./generate 1 40000 > input.txt
	./main < input.txt

test2: gen all
	./generate 2 40000 > input.txt
	./main < input.txt

test3: gen all
	./generate 3 40000 > input.txt
	./main < input.txt

test4: gen all
	./generate 4 40000 > input.txt
	./main < input.txt

test5: gen all
	./generate 5 40000 > input.txt
	./main < input.txt

gen:
	g++  -g -Wall -o generate gen_rand.cpp

p: perf
	./perform 

perf: performance.o sort.o
	g++  -g -Wall -o perform performance.o sort.o

performance.o: performance.cpp
	g++ -g -Wall -c performance.cpp

main.o: main.cpp
	g++ -g -Wall -c main.cpp

sort.o: sort.cpp
	g++ -g -Wall -c sort.cpp

run:
	./main < input.txt

v:
	valgrind --leak-check=full ./main < input.txt

clean:
	rm -f ./main *.o ./generate ./g *.txt
