#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <ctime>
#include "selection.h"

#define SELECTION_WAY_SIZE 2

using namespace std;

int main(int argc, char *argv[]) {
	int (*const fn[SELECTION_WAY_SIZE])(int*, const int, const int) = {
        random_selection,
        deterministric_selection
    };
    int selection_algorithm;
	cin >> selection_algorithm;
	assert(selection_algorithm >= 0 && selection_algorithm < SELECTION_WAY_SIZE);
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
	i_th_small = fn[selection_algorithm](arr, n, order);
	cout<<"The order-"<<order<<" item is "<<i_th_small<<endl;
	delete[] arr;
	return 0;
}