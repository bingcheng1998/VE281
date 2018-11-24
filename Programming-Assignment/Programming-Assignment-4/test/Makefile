all: test

test: 
	./a --verbose --median --midpoint --transfers < ./testfile/28.in > ./output/a.txt
	./b --verbose --median --midpoint --transfers < ./testfile/28.in > ./output/b.txt
	diff ./output/a.txt ./output/b.txt

clean:
	rm -f *.o main result.txt

tar:
	tar czvf p4.tar Makefile main.cpp equity_transfer.cpp equity_transfer.h