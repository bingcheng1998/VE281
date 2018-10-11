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

int Deterministic_pivot(int* arr, int n){
// Choose pivot p from arr uniformly at deterministic;
// Partition arr using pivot p;
// Let j be the index of p, return j;
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
	if (incomplete_bucket ! = 0)
	{
		int incomplete_bucket_size = n%5;
		int* arr_break_5 = arr + full_bucket*5;
		insertion_sort(arr_break_5, incomplete_bucket_size);
		arr_medians[full_bucket] = arr_break_5[incomplete_bucket_size/2];
	}
	int pivot = Deterministic_pivot(arr_medians, arr_medians_size);
	return pivot;
}

static int Rselect(int* arr, int n, int order){

}

int random_selection(int* arr, int n, int order){

}

int deterministric_selection(int* arr, int n, int order){

}

