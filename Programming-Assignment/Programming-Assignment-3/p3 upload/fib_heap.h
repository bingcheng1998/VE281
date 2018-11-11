//
//  fib_heap.h
//  VE281 2018 Autumn
//  project3
//  Bingcheng HU
//
#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include "priority_queue.h"

// OVERVIEW: A specialized version of the 'heap' ADT that is implemented with
//           an underlying unordered array-based container. Every time a min
//           is required, a linear search is performed.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  fib_heap(COMP comp = COMP());

  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(1)
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: O(n)
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(n)
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
  TYPE is_empty = TYPE();
};

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> :: fib_heap(COMP comp) {
    compare = comp;
    // Fill in the remaining lines if you need.
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    // Fill in the body.
    data.push_back(val);
}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP> :: dequeue_min() {
    // Fill in the body.
    if (empty()) return is_empty;
    auto min = std::min_element(data.begin(), data.end(), compare);
    int dis = std::distance(data.begin(), min);
    std::swap(data[dis], data.back());
    TYPE dequeue_min = std::move(data.back());
    data.pop_back();
    return dequeue_min;
}

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP> :: get_min() const {
    // Fill in the body.
    if (empty()) return is_empty;
    auto min = std::min_element(data.begin(), data.end(), compare);
    return *min;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP> :: empty() const {
    // Fill in the body.
    return data.empty();
}

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP> :: size() const { 
    // Fill in the body.
    return data.size();
}

#endif //fib_HEAP_H
