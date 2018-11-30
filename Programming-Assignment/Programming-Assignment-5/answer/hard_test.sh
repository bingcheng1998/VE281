#!/bin/bash 
# 胡炳城 写于2018年11月30日 
echo ======================
echo hard test VE281 【program 5】
echo ======================
for((i=0;i<=20;i++))
do   
	echo g$i.in is input file\! 
	./main < ./test_files/$i.in > ./test_files/$i.test
	diff ./test_files/$i.test ./test_files/$i.out
done 
echo ======================
echo \ \ ----  THE END  ----
echo ======================
