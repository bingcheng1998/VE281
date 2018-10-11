#include <iostream>
#include "selection.h"

using namespace std;

static int random_pivot(int* arr, int n){
// Choose pivot p from arr uniformly at random;
// Partition arr using pivot p;
// Let j be the index of p, return j;

}

static void insertion_sort(int *arr, const int n){
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
}

static int Deterministic_pivot_helper(int* arr, int n){
	if(n == 1) return arr[0]; 
	int full_bucket = n/5;
	int arr_medians_size = full_bucket+1;
	int* arr_medians = new int [arr_medians_size];
	int incomplete_bucket = n - full_bucket;
	for (int i = 0; i < full_bucket; ++i)
	{
		int* arr_break_5 = arr + i*5;
		insertion_sort(arr_break_5, 5);
		arr_medians[i] = arr_break_5[2];
	}
	if (incomplete_bucket != 0)
	{
		int incomplete_bucket_size = n%5;
		int* arr_break_5 = arr + full_bucket*5;
		insertion_sort(arr_break_5, incomplete_bucket_size);
		arr_medians[full_bucket] = arr_break_5[incomplete_bucket_size/2];
	}
	int pivot = Deterministic_pivot_helper(arr_medians, arr_medians_size);
	return pivot;
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

static int partition_array(int *arr, const int n, const int pivot){
	// MODIFIES: *arr
	// EFFECTS: choose a pivotat then Move pivot to its correct place in the array.
	const int size = n;
	int BL = 0, BR = size-1;
	int * B = new int[size];
	int * A = arr;
	const int t = pivot;
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
	return BL;
}

static int Deterministic_pivot(int* arr, int n){
// Choose pivot p from arr uniformly at deterministic;
// Partition arr using pivot p;
// Let j be the index of p, return j;
	int pivot = Deterministic_pivot_helper(arr, n);
	int j = partition_array (arr, n, pivot);
	return j;
}

static int Rselect(int* arr, int n, int order){

}

int random_selection(int* arr, int n, int order){

}

int deterministric_selection(int* arr, int n, int order){
	if(n == 1) return arr[0];
	int j = Deterministic_pivot(arr, n);
	if(j == order) return arr[order];
	if(j > order) {
		int* arr_left = arr;
		int length = j;
		return deterministric_selection(arr_left, length, order);
	}
	else{
		int* arr_right = arr + j + 1;
		int length = n - j - 1;
		return deterministric_selection(arr_right, length, order-j-1);
	}
}

