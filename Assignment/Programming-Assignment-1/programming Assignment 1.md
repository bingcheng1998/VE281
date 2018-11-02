# VE281 Project One Report

Bingcheng HU 516021910219

## 1 Introduction

In order to study the performances of these six sorting algorithms, I generated different size of
arrays and compared the running speed of them (including the std::sort function in STL). Since it’s
a waste of time to wrote a comparison script written in C++, I chose node-gyp to build the sorting
algorithm into a C++ addon of node, and then wrote some Javascript code to benchmark them. Small
size of arrays were run for several times so that the result can be more accurate.

##2 Comparison of algorithms

The limitation of runtime was set to 1s for all algorithms, so some meaningless and slow running
were dropped (eg. large array size for bubble sort). Then I used MATLAB to plot two graphs, one of
small test cases, and another of all cases.

### 2.1 General analysis

![Big case 9_22](/Users/bingcheng/Documents/Datagraph/Big%20case%209_22.svg)

From Figure 1, we can find that bubble sort, insertion sort and selection sort have the similar
running speed, while merge sort and quick sort are also similar on running speed, but faster. The
result satisfy the theory that bubble sort, insertion sort and selection sort have time complexity of
O(n2), while merge sort and quick sort have time complexity of O(nlogn).



### 2.2 Small data analysis

![Small cases 9_22](/Users/bingcheng/Documents/Datagraph/Small%20cases%209_22.svg)

From Figure 2, we can find that when the data size is small (from 10 to 100), the running speed
of merge sort and quick sort is slower than insertion sort. It is because when n is small, the constant
c acts a more important role. However, the cpp standard sort have a similar performance as insertion
sort in this period, so it probably apply insertion sort to the data when n is small enough. That’s why
the cpp standard sort is always quicker than my algorithms in Figure 1.

##3 Appendix

###3.1 The project files

####3.1.1 sort.h

```c++
#ifndef SORT_H
#define SORT_H

#include <cstdlib>

void bubble_sort(int arr[], const int n);

void insertion_sort(int arr[], const int n);

void selection_sort(int arr[], const int n);

void merge_sort(int arr[], const int n);

void quick_sort_array(int arr[], const int n);

void quick_sort_in_place(int arr[], const int n);

#endif //SORT_H
```

3.1.2 sort.cpp

```c++
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <time.h> 
#include "sort.h"

#define TEST_ORDER //test whether arr[] is well sorted.
using namespace std;
static void order_test(int arr[], const int n){
	for (int i = 1; i < n; ++i)
	{
		if (arr[i] < arr[i-1])
		{
			cerr<<arr[i-1]<<", "<<arr[i]<<endl;
		}
		assert(arr[i] >= arr[i-1]);
	}
}

void bubble_sort(int arr[], const int n){
	for (int i = n-1; i >0; i--)
	{
		for (int j = 0; j < i; ++j)
		{
			if (arr[j]>arr[j+1]){
				swap(arr[j], arr[j+1]);
			}
		}
	}
	#ifdef TEST_ORDER
	order_test(arr, n);
	#endif
}

void insertion_sort(int arr[], const int n){
	for (int i = 1; i < n; ++i)
	{
		int t = arr[i];
		int j;
		for (j = i; j > 0; --j)
		{
			if (j == 0){
				break;
			} else if (arr[j-1] > t){
				arr[j] = arr[j-1];
			} else {
				break;
			}
		}
		arr[j] = t;
	}
	#ifdef TEST_ORDER
	order_test(arr, n);
	#endif
}

void selection_sort(int* arr, const int n){
	for (int i = 0; i < n; ++i)
	{
		int t = arr[i];
		for (int j = i; j < n; j++)
		{
			if(arr[j] < t) swap(arr[j], arr[i]);
		}
	}
}

static void int_append(int arrA[], const int arrB[], const int s){
	assert(s >= 0);
	if(s == 0) return;
	for (int i = 0; i < s; ++i)
	{
		arrA[i] = arrB[i];
	}
}

static void merge(int *arr, int left, int mid, int right){
	int i = 0, j = 0, k = 0;
	int sizeA = mid - left + 1;
	int sizeB = right - mid;
	int sizeC = right - left + 1;
	int * C = new int[sizeC];
	int * A = arr + left;
	int * B = arr + mid + 1;
	while(i < sizeA && j < sizeB){
		if(A[i] < B[j]) C[k++] = A[i++];
		else C[k++] = B[j++];
	}
	if(i == sizeA) int_append(C+k, B+j, sizeC - k );
	else int_append(C+k, A+i, sizeC - k );
	int_append(arr + left, C, sizeC);
	delete[] C;
}

static void merge_helper(int *arr, int left, int right){
	if (left >= right) return;
	int mid = (left+right)/2;
    merge_helper(arr, left, mid);
    merge_helper(arr, mid+1, right);
	merge(arr, left, mid, right);
}

void merge_sort(int arr[], const int n){
	merge_helper(arr, 0, n-1);
	#ifdef TEST_ORDER
	order_test(arr, n);
	#endif
}

static int partition_array(int *arr, int left, int right){
	//EFFECTS: choose a pivotat then Move pivot to its correct place in the array.
	const int size = right - left + 1;
	int BL = 0, BR = size-1;
	int * B = new int[size];
	int * A = arr + left;
	srand((unsigned)time(NULL));
	const int pivotat = rand()%size;
	const int t = A[pivotat];
	for (int i = 0; i < size; ++i)
	{
		if(i == pivotat) continue;
		if(A[i] > t) B[BR--] = A[i];
		else B[BL++] = A[i];
	}
	assert(BL == BR);
	B[BL] = t;
	int_append(A, B, size);
	delete[] B;
	return BL + left;
}

static void quick_sort_helper(int *arr, int left, int right) {
	int pivotat; // index of the pivot 
	if(left >= right) return;
	pivotat = partition_array(arr, left, right); 
	quick_sort_helper(arr, left, pivotat-1); 
	quick_sort_helper(arr, pivotat+1, right);
}

void quick_sort_array(int arr[], const int n){
	quick_sort_helper(arr, 0, n-1);
	#ifdef TEST_ORDER
	order_test(arr, n);
	#endif
	
}

static int partition_in_place(int *arr, int left, int right){
	//EFFECTS: choose a pivotat then Move pivot to its correct place in the array.
	const int size = right - left + 1;
	int AL = 1, AR = size - 1;
	int * A = arr + left;
	srand((unsigned)time(NULL));
	const int pivotat = rand()%size;
	const int t = A[pivotat];
	swap(A[0], A[pivotat]);
	while(true){
		while(A[AL] < t && AL < size - 1) AL++;
		while(A[AR] >= t && AR > 0) AR--;
	 	if(AL < AR) swap(A[AL], A[AR]);
	 	else break;
	 	// cerr<<"pivotat = "<<t<<" A[AL] = "<<A[AL]<<" A[AR] = "<<A[AR]<<endl;
	}
	swap(A[0], A[AR]);
	// print_arr(A, size);
	return left + AR;
}

static void quick_sort_in_place_helper(int *arr, int left, int right) {
	int pivotat; // index of the pivot 
	if(left >= right) return;
	pivotat = partition_in_place(arr, left, right); 
	quick_sort_in_place_helper(arr, left, pivotat-1); 
	quick_sort_in_place_helper(arr, pivotat+1, right);
}

void quick_sort_in_place(int arr[], const int n){
	quick_sort_in_place_helper(arr, 0, n-1);
	#ifdef TEST_ORDER
	order_test(arr, n);
	#endif
}

```

####3.1.3 main.cpp

```c++
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <ctime>
#include "sort.h"

using namespace std;
#define SORT_WAY_SIZE 6
#define SORT_DEBUG

const string sortName[] = {
	"bubble_sort", "insertion_sort", "selection_sort",
	"merge_sort", "quick_sort_array", "quick_sort_in_place",
	"ERROR_SORT_NAME"
};

int main(int argc, char *argv[]) {
    void (*const fn[SORT_WAY_SIZE])(int*, const int) = {
        bubble_sort,
        insertion_sort,
        selection_sort,
        merge_sort,
        quick_sort_array,
        quick_sort_in_place
    };
	int sort_algorithm;
	cin >> sort_algorithm;
	assert(sort_algorithm >= 0 && sort_algorithm < SORT_WAY_SIZE);
	#ifdef SORT_DEBUG
	cout<<"Sort algorithm is ["<<sortName[sort_algorithm]<<"],"<<endl;
	#endif
	int n;
	cin >> n;
	int *arr = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin>>arr[i];
	}
	clock_t start, end;
	start = clock();
	fn[sort_algorithm](arr, n);
	end = clock();
	#ifdef STANDARD_OUTPUT
	for (int i = 0; i < n; ++i)
	{
		cout << arr[i] <<endl;
	}
	#endif
	#ifdef SORT_DEBUG
	cout << "running time：" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	#endif
	delete[] arr;
	return 0;
}

```

####3.1.4 Makefile

```makefile
all: main.o sort.o
	g++  -g -Wall -o main main.o sort.o

main.o: main.cpp
	g++ -g -Wall -c main.cpp

sort.o: sort.cpp
	g++ -g -Wall -c sort.cpp

run:
	./main < input.txt

val:
	valgrind --leak-check=full ./main < input.txt

clean:
	rm -f ./main *.o ./generate ./g *.txt

```

