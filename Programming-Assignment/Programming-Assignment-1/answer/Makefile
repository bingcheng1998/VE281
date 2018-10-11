all: main.o sort.o
	g++ -std=c++11 -O2 -g -Wall -o main main.o sort.o

main.o: main.cpp
	g++ -std=c++11 -O2 -g -Wall -c main.cpp

sort.o: sort.cpp
	g++ -std=c++11 -O2 -g -Wall -c sort.cpp

v:
	valgrind --leak-check=full ./main < 1000num

tar:
	tar czvf p1.tar main.cpp sort.cpp sort.h Makefile repo_1.pdf

clean:
	rm -f ./main *.o
