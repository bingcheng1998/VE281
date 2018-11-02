#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <ctime>
#include "sort.h"

using namespace std;

#define SORT_WAY_SIZE 6
#define SORT_DEBUG
#define STANDARD_OUTPUT

// enum sort_way
// {
// 	bubble_sort, insertion_sort, selection_sort,
// 	merge_sort, quick_sort_array, quick_sort_in_place,
// 	SORT_WAY_SIZE
// };

const string sortName[] = {
	"bubble_sort", "insertion_sort", "selection_sort",
	"merge_sort", "quick_sort_array", "quick_sort_in_place",
	"ERROR_SORT_NAME"
};

// int sort_helper(void (*fn)(int*, int), int arr[], int n) {
// 	fn(arr, n);
// }

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
	cout << "总共运行时间：" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	#endif
	delete[] arr;
	return 0;
}




