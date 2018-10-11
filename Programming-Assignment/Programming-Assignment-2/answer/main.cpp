#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <ctime>
#include "selection.h"

#define SELECTION_WAY_SIZE 2
#define SELECTION_DEBUG

using namespace std;

const string selectionName[] = {
	"R selection","D selection","ERROR_SELECTION_Name"
};

#ifdef SELECTION_DEBUG
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
}
#endif


int main(int argc, char *argv[]) {
	int (*const fn[SELECTION_WAY_SIZE])(int*, const int, const int) = {
        random_selection,
        deterministric_selection
    };
    int selection_algorithm;
	cin >> selection_algorithm;
	assert(selection_algorithm >= 0 && selection_algorithm < SELECTION_WAY_SIZE);
	#ifdef SELECTION_DEBUG
	cout<<"selection algorithm is ["<<selectionName[selection_algorithm]<<"],"<<endl;
	#endif

	int n;
	cin >> n;
	int order;
	cin >> order;
	int *arr = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin>>arr[i];
	}
	int i_th_small;
	clock_t start, end;
	start = clock();
	i_th_small = fn[selection_algorithm](arr, n, order);
	end = clock();

	#ifdef SELECTION_DEBUG
	int arr_copy[n];
	//use deep copy to make arr_copy evry turn
	memset(arr_copy,0, n*sizeof(int));
	memcpy(arr_copy,arr, n*sizeof(int));
	insertion_sort(arr_copy, n);
	cout << "总共运行时间：" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	cout << "第["<<order<<"]小的数是：["<<i_th_small<<"], 真实是["<<arr_copy[order]<<"]"<<endl;
	#endif
	cout<<"The order-"<<order<<" item is "<<i_th_small<<endl;
	delete[] arr;
	return 0;
}