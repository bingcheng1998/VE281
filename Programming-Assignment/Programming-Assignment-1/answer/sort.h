#ifndef SORT_H
#define SORT_H

#include <cstdlib>

void bubble_sort(int arr[], const int n);
// MODIFIES: *arr
// EFFECTS: sort integers arr[] in ascending order with bubble_sort.

void insertion_sort(int arr[], const int n);
// MODIFIES: *arr
// EFFECTS: sort integers arr[] in ascending order with insertion_sort.

void selection_sort(int arr[], const int n);
// MODIFIES: *arr
// EFFECTS: sort integers arr[] in ascending order with selection_sort.

void merge_sort(int arr[], const int n);
// MODIFIES: *arr
// EFFECTS: sort integers arr[] in ascending order with merge_sort.

void quick_sort_array(int arr[], const int n);
// MODIFIES: *arr
// EFFECTS: sort integers arr[] in ascending order with quick_sort by array.

void quick_sort_in_place(int arr[], const int n);
// MODIFIES: *arr
// EFFECTS: sort integers arr[] in ascending order with quick_sort by in_place.

#endif //SORT_H