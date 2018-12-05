all: main.o graph_test.o
	g++ -std=c++11 -O3 -Wall -g -o main main.o graph_test.o

main.o: main.cpp
	g++ -std=c++11 -O3 -Wall -g -c main.cpp

graph_test.o: graph_test.cpp
	g++ -std=c++11 -O3 -Wall -g -c graph_test.cpp


test: clean all
	./main < ./test_files/g1.in > ./test_files/g1.test
	diff ./test_files/g1.test ./test_files/g1.out

t: all
	bash simple_test.sh

ht: all
	bash test.sh

clean:
	rm -f *.o main result.txt ./test_files/*.test

tar:
	tar czvf p5.tar Makefile main.cpp graph_test.h graph_test.cpp

v:
	valgrind --leak-check=full ./main < ./test_files/g1.in > ./test_files/g1.test
