all: main.o equity_transfer.o
	g++ -std=c++11 -O2 -g -Wall -o main main.o equity_transfer.o

main.o: main.cpp
	g++ -std=c++11 -O2 -g -Wall -c main.cpp

equity_transfer.o: equity_transfer.cpp
	g++ -std=c++11 -O2 -g -Wall -c equity_transfer.cpp

test: all
	./main --verbose --median --midpoint --transfers --ttt AMZN < test.txt > result.txt
	diff result.txt out.txt

clean:
	rm -f *.o main result.txt

tar:
	tar czvf p4.tar Makefile main.cpp equity_transfer.cpp equity_transfer.h