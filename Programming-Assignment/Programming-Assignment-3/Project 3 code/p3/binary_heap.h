//
//  binary_heap.h
//  VE281 2018 Autumn
//  project3
//  Bingcheng HU
//
#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <algorithm>
#include "priority_queue.h"

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a binary
//           heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class binary_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  binary_heap(COMP comp = COMP());

  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(1)
  virtual const TYPE &get_min() const;

  // EFFECTS: Get the number of elements in the heap.
  // RUNTIME: O(1)
  virtual size_type size() const;

  // EFFECTS: Return true if the heap is empty.
  // RUNTIME: O(1)
  virtual bool empty() const;

private:
  // Note: This vector *must* be used in your heap implementation.
  std::vector<TYPE> data;
  // Note: compare is a functor object
  COMP compare;

private:
  // Add any additional member functions or data you require here.
  virtual void percolateUp(int node_num);

  virtual void percolateDown(int node_num);
};

template<typename TYPE,typename COMP>
void binary_heap<TYPE,COMP>::percolateUp(int node_num)
{
    while(node_num>1&&compare(data[node_num],data[node_num/2]))
    {
        std::swap(data[node_num],data[node_num/2]);
        node_num=node_num/2;
    }
}

template<typename TYPE,typename COMP>
void binary_heap<TYPE,COMP>::percolateDown(int node_num)
{
    int j;
    int size = this->size()-1;
    for(j=2*node_num; j<=size; j=2*node_num)
    {
        if(j<size && compare(data[j+1],data[j])) j++;
        if(compare(data[node_num],data[j])) break;
        std::swap(data[node_num],data[j]);
        node_num=j;
    }
}

template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP> :: binary_heap(COMP comp) {
    compare = comp;
    // Fill in the remaining lines if you need.
    data.push_back(TYPE());
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    // Fill in the body.
    data.push_back(val);
    percolateUp(size());
}

template<typename TYPE, typename COMP>
TYPE binary_heap<TYPE, COMP> :: dequeue_min() {
    // Fill in the body.
    if (this->empty()) return data[0];
    std::swap(data[1],data.back());
    percolateDown(1);
    TYPE dequeue_min = data.back();
    data.pop_back();
    return dequeue_min;
}

template<typename TYPE, typename COMP>
const TYPE &binary_heap<TYPE, COMP> :: get_min() const {
    // Fill in the body.
    if (this->empty()) return data[0];
    return data[1];
}

template<typename TYPE, typename COMP>
bool binary_heap<TYPE, COMP> :: empty() const {
    // Fill in the body.
    return this->size() == 0;
}

template<typename TYPE, typename COMP>
unsigned binary_heap<TYPE, COMP> :: size() const { 
    // Fill in the body.
    return data.size()-1;
}

#endif //BINARY_HEAP_H
