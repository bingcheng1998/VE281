#!/bin/bash

for((i=0;i<=20;i++))
do   
	echo $i.out 被修改\! 
	sed -i '' '1d' $i.out
done 