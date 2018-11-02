#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <time.h> 
#include "sort.h"

using namespace std;

// #define TEST_ORDER //test whether arr[] is well sorted.

static void order_test(int arr[], const int n){
	for (int i = 1; i < n; ++i)
	{
		if (arr[i] < arr[i-1])
		{
			cerr<<arr[i-1]<<", "<<arr[i]<<endl;
		}
		assert(arr[i] >= arr[i-1]);
	}
	cout << "They sort integers in ascending⬆️ order success!" <<endl;
}

// static void print_arr(int arr[], const int n){
// 	for (int i = 0; i < n; ++i)
// 	{
// 		if (!i%10)
// 		{
// 			cout<<endl;
// 		}
// 		cout<<arr[i]<<", ";
// 	}
// 	cout<<endl;
// }

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










