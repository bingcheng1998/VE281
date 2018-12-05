# P5 编译方法

![](https://ws3.sinaimg.cn/large/006tNbRwly1fxsgaf6v8ij31440u04qt.jpg)

## Makefile

```ruby
all: main.o graph_test.o
	g++ -std=c++14 -O3 -Wall -g -o main main.o graph_test.o

main.o: main.cpp
	g++ -std=c++14 -O3 -Wall -g -c main.cpp

graph_test.o: graph_test.cpp
	g++ -std=c++14 -O3 -Wall -g -c graph_test.cpp


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
```



## 命令行

1. 编译

   `$ make`

1. 简单测试

   `$ make t`

2. 强度测试

   `$ make ht`

3. 打包

   `$ make tar`

4. 检测内存泄漏

   `$ make v`



## 两个Test

### simple

```ruby
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
```



### hard

```ruby
#!/bin/bash 
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
```



