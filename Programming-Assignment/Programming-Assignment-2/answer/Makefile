all: main.o selection.o
	g++ -std=c++11 -O3 -o main main.o selection.o

main.o: main.cpp
	g++ -std=c++11 -O3 -c main.cpp

selection.o: selection.cpp
	g++ -std=c++11 -O3 -c selection.cpp

tar:
	tar czvf p2.tar Makefile main.cpp selection.cpp selection.h p2.pdf

clean:
	rm -f ./main *.o

