#include <iostream>
#include "selection.h"

using namespace std;

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

int main(int argc, char *argv[]) {
	int size = 12;
	int arr[] = {2, 3, 6, 24, -12, 0, 0, -34, 23, 0, -3, 123};
	int arr_copy[size];
	//use deep copy to make arr_copy evry turn
	memset(arr_copy,0, size*sizeof(int));
	memcpy(arr_copy,arr, size*sizeof(int));
	selection_sort(arr_copy, size);
	for (int i = 0; i < size; ++i)
	{
		int selection = random_selection(arr, 12, i);
		// int selection = deterministric_selection(arr, 12, i);
		cout<<"# "<<i<<" selection ["<<selection<<"], sort ["<<arr_copy[i]<<"]"<<endl;
	}
	
}