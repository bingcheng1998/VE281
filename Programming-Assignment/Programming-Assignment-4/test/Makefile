all: test

test: 
	./a --verbose --median --midpoint --transfers < ./testfile/14.in > ./output/a.txt
	./b --verbose --median --midpoint --transfers < ./testfile/14.in > ./output/b.txt
	diff ./output/a.txt ./output/b.txt

s:
	./a -v -m -p -t -g E_D -g E_B -g E_C< ./testfile/15.in > ./output/a.txt
	./b -v -m -p -t -g E_D -g E_B -g E_C< ./testfile/15.in > ./output/b.txt
	diff ./output/a.txt ./output/b.txt

clean:
	rm -f *.o main result.txt

tar:
	tar czvf p4.tar Makefile main.cpp equity_transfer.cpp equity_transfer.h