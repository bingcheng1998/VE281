#include <iostream>
#include <cstdlib>
#include <cassert>
#include "sort.h"


// #define TEST_ORDER //test whether arr[] is well sorted.
using namespace std;

#ifdef TEST_ORDER
static void order_test(int *arr, const int n){
    // EFFECTS: assert if arr is not in ascending order.
	for (int i = 1; i < n; ++i)
	{
		if (arr[i] < arr[i-1])
		{
			cerr<<arr[i-1]<<", "<<arr[i]<<endl;
		}
		assert(arr[i] >= arr[i-1]);
	}
}
#endif

void bubble_sort(int *arr, const int n){
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

void insertion_sort(int *arr, const int n){
	for (int i = 1; i < n; ++i)
	{
		int t = arr[i];
		int j = i;
		while (j >= 1)
        {
            if (arr[j - 1] > t)
            {
                arr[j] = arr[j - 1];
                j--;
            }
            else break;
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
		int k = i;
		for (int j = i; j < n; j++)
		{
			if(arr[j] < t) {
				k = j;
				t = arr[k];
			}
		}
		swap(arr[k], arr[i]);
	}
	#ifdef TEST_ORDER
	order_test(arr, n);
	#endif
}

static void int_append(int *arrA, const int *arrB, const int s){
	// MODIFIES: *arrA
    // EFFECTS: append first "s" int in arrB tp the biginning if arrA.
	assert(s >= 0);
	if(s == 0) return;
	for (int i = 0; i < s; ++i)
	{
		arrA[i] = arrB[i];
	}
}

static void merge(int *arr, int left, int mid, int right){
	// MODIFIES: *arr
    // EFFECTS: merge [left, mid] and (mid, right] together.
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
	// MODIFIES: *arr
    // EFFECTS: helper of the merge_sort function.
	if (left >= right) return;
	int mid = (left+right)/2;
    merge_helper(arr, left, mid);
    merge_helper(arr, mid+1, right);
	merge(arr, left, mid, right);
}

void merge_sort(int *arr, const int n){
	merge_helper(arr, 0, n-1);
	#ifdef TEST_ORDER
	order_test(arr, n);
	#endif
}

static int partition_array(int *arr, int left, int right){
	// MODIFIES: *arr
	// EFFECTS: choose a pivotat then Move pivot to its correct place in the array.
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
	// MODIFIES: *arr
    // EFFECTS: helper of the quick_sort_array function.
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
	// MODIFIES: *arr
	// EFFECTS: choose a pivotat then Move pivot to its correct place in the array.
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
	}
	swap(A[0], A[AR]);
	return left + AR;
}

static void quick_sort_in_place_helper(int *arr, int left, int right) {
	// MODIFIES: *arr
    // EFFECTS: quick_sort_in_place_helper
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










