#!/bin/bash 
# 胡炳城 写于2018年11月30日 
echo ======================
echo test VE281 【program 5】
echo ======================
for((i=1;i<=3;i++))
do   
	echo g$i.in is input file\! 
	./main < ./test_files/g$i.in > ./test_files/g$i.test
	diff ./test_files/g$i.test ./test_files/g$i.out
done 
echo ======================
echo \ \ ----  THE END  ----
echo ======================
