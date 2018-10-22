//
// Created by liu on 17-10-9.
//

#include "selection.h"
#include "selection_0.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {

    size_t size = 100000;
    auto arr = new int[size];
    auto arr2 = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = arr2[i] = rand();
    }
    sort(arr2, arr2 + size);
    int lines = size;
    int c1 = clock();
    for (size_t i = 0; i < 100; i++) {
        int arr_copy[lines];
                //use deep copy to make arr_copy evry turn
        memset(arr_copy,0, lines*sizeof(int));
        memcpy(arr_copy,arr, lines*sizeof(int));
        auto result = random_selection_0(arr_copy, size, i);
        if (result != arr2[i]) cout << "error" << endl;
    }
    int c2 = clock();
    for (size_t i = 0; i < 100; i++) {
        int arr_copy[lines];
                //use deep copy to make arr_copy evry turn
        memset(arr_copy,0, lines*sizeof(int));
        memcpy(arr_copy,arr, lines*sizeof(int));
        auto result = random_selection(arr_copy, size, i);
        if (result != arr2[i]) cout << "error" << endl;
    }
    int c3  = clock();
    cout << "lyh time = "<< c2-c1<<", my time = "<< c3 - c2<<endl;
}

