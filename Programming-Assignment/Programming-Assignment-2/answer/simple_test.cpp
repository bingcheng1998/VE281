#include <iostream>
#include "selection.h"

using namespace std;
int main(int argc, char *argv[]) {
	int[] arr = {2, 3, 6, 24, -12, 0, 243, -34, 23, 56, -3, 123};
	cout<<Deterministic_pivot(arr, 12);
}