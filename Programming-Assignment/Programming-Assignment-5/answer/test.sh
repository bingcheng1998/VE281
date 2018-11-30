#/bin/bash
testNum=21
acNum=0
for i in `seq 0 $(($testNum-1))`; do
    ./main <./test_files/$i.in >./test_files/$i.test
    diff ./test_files/$i.test ./test_files/$i.out
    if [ $? = 0 ]; then
        echo "testcase $i: Accepted"
        acNum=$((acNum+1))
    else
        echo "testcase $i: Wrong Answer"
    fi
done

echo "Accepted $acNum/$testNum"
if [ "$acNum" = "$testNum" ]; then
    echo "All test cases accepted"
else
    echo "Some test cases failed, work hard and try again!"
fi 
