#!/bin/bash  

for((i=13;i<=66;i++))
do   
	echo ☺ $i.in is input file\! 
	./ll   -v -m -p -t -g TG -g GE -g GO -g nn< ./testfile/$i.in > ./output/l.txt
	./a    -v -m -p -t -g TG -g GE -g GO -g nn< ./testfile/$i.in > ./output/a.txt
	./main -v -m -p -t -g TG -g GE -g GO -g nn< ./testfile/$i.in > ./output/b.txt
	echo ✋ lxh \<\> hbc
	diff ./output/a.txt ./output/b.txt
	echo 🏠 lyh \<\> hbc
	diff ./output/l.txt ./output/b.txt;
done 
 
