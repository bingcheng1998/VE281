#ifndef SELECTION_H
#define SELECTION_H

int random_selection(int* arr, const int n, const int order);
// Randomized selection algorithm
// MODIFIES: *arr
// EFFECTS: select i-th smallest element in the array

int deterministric_selection(int* arr, const int n, const int order);
// Deterministic selection algorithm
// MODIFIES: *arr
// EFFECTS: select i-th smallest element in the array

#endif