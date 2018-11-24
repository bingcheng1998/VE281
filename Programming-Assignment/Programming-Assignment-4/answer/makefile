all: main.o Stock.o Client.o Market.o
	g++ -std=c++11 -O2 -g -Wall -o main main.o Stock.o Client.o Market.o

main.o: main.cpp
	g++ -std=c++11 -O2 -g -Wall -c main.cpp

Client.o: Client.cpp
	g++ -std=c++11 -O2 -g -Wall -c Client.cpp

Stock.o: Stock.cpp
	g++ -std=c++11 -O2 -g -Wall -c Stock.cpp

Market.o: Market.cpp
	g++ -std=c++11 -O2 -g -Wall -c Market.cpp

run: all
	./main --verbose --median --midpoint --transfers --ttt AMZN < test.txt > result.txt
	diff result.txt out.txt

clean:
	rm -f *.o main result.txt

tar:
	tar czvf p4.tar Makefile main.cpp Client.cpp Stock.cpp Market.cpp Median.h Client.h Stock.h Market.h