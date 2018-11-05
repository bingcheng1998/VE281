#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include "priority_queue.h"

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a 
//           Fibonacci heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  fib_heap(COMP comp = COMP());

  // EFFECTS: Deconstruct the heap with no memory leak.
  // MODIFIES: this
  // RUNTIME: O(n)
  ~fib_heap();
  
  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(1)
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: Amortized O(log(n))
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
  // Note: compare is a functor object
  COMP compare;

private:
  // Add any additional member functions or data you require here.
  // You may want to define a strcut/class to represent nodes in the heap and a
  // pointer to the min node in the heap.
  struct node
  {
      TYPE key;
      typename std::list<node> child;
      node parent;
      int degree=0;
  };
  typename std::list<node> root;
  typename std::list<node>::iterator min;
  int n=0;
  TYPE empty_fib=TYPE();
};

// Add the definitions of the member functions here. Please refer to
// binary_heap.h for the syntax.



// Make_Fibonacci_Heap() {
//   H.n = 0; // n stores the number of elements in the heap
//   H.min = NULL; // min refers to the minimal element in the heap return H;
// }
template<typename TYPE,typename COMP>
fib_heap<TYPE,COMP>::fib_heap(COMP comp)
{
    compare=comp;
    // Fill in the remaining lines if you need.
    min=NULL;
    n=0;
}

// Fibonacci_Heap_Enqueue(H, key) {
//   create a new node x;
//   x.degree = 0;
//   x.parent = NULL;
//   x.child = NULL;
//   x.key = key;
// // x.mark = FALSE; // This statement is commented out, because you
//                      // do not need it in this project.
//   if(H.min == NULL) {
//       create a root list for H only containing x;
//       H.min = x;
//   }
//   else {
//      insert x into the root list of H;
//      if(x.key < H.min.key)
//       H.min =  x; 
//   }  
//   H.n = H.n + 1; 
// }

template<typename TYPE,typename COMP>
void fib_heap<TYPE,COMP>::enqueue(const TYPE&val)
{
    node x;
    x.key=val;
    x.degree=0;
    x.parent = NULL;
    x.child = NULL;
    if(min == NULL)
    {
        root.push_back(x);
        H_min=x;
    }
    else
    {
        // typename std::list<fib_node>::iterator it;
        // it=root.insert(root.end(),n);
        root.insert(root.end(),n);
        if(compare(x.key,(*H_min).key))
        {
            // H_min=it;
          H_min=x;
        }
    }
    n++;
};

Fibonacci_Heap_Dequeue_Min(H) { z = H.min;
  if(z != NULL) {
     for(each child x of z) {
       add x to the root list of H;
       x.parent = NULL;
     }
     remove z from the root list of H;
     H.n = H.n – 1;
     if(H.n == 0) H.min = NULL;
   
  else Consolidate(H);
    }
  return z; 
}

template<typename TYPE,typename COMP>
TYPE fib_heap<TYPE,COMP>::dequeue_min()
{
    if(root.empty()==true)
    {
        return empty_fib;
    }
    fib_node z;
    z=*min;
    typename std::list<fib_node>::iterator temp;
    if(H_min!=root.end())
    {
        temp=z.child.begin();
        while(temp!=z.child.end())
        {
            root.push_back(*temp);
            temp=z.child.erase(temp);
        }
        H_min=root.erase(H_min);
        H_n--;
        if(H_n==0)
        {
            H_min=root.end();
        }
        else
        {
            int size=int((log(H_n))/(log((1+sqrt(5))/2)))+1;
            typename std::list<fib_node>::iterator A[size];
            for(int i=0;i<size;++i)
            {
                A[i]=root.end();
            }
            typename std::list<fib_node>::iterator y;
            int d=0;
            typename std::list<fib_node>::iterator it;
            for(it=root.begin();it!=root.end();++it)
            {
                d=(*it).degree;
                while(A[d]!=root.end())
                {
                    y=A[d];
                    if(compare((*y).val,(*it).val))
                    {
                        root.insert(y,*it);
                        root.insert(it,*y);
                        it=root.erase(it);
                        y=root.erase(y);
                        it--;
                        y--;
                    }
                    (*it).child.push_back((*y));
                    y=root.erase(y);
                    (*it).degree++;
                    A[d]=root.end();
                    d++;
                }
                A[d]=it;
            }
            H_min=root.end();
            for(int i=0;i<size;++i)
            {
                if(A[i]!=root.end())
                {
                    if(H_min==root.end())
                    {
                        H_min=A[i];
                    }
                    else
                    {
                        if(compare((*A[i]).val,(*H_min).val))
                        {
                            H_min=A[i];
                        }
                    }
                }
            }
        }
    }
    return z.val;
};




Consolidate(H) {
let A[0..D(H.n)] be a new array; // D(N) is the maximum degree of
  for(i = 0 to D(H.n))
  A[i] = NULL;
  // any node in a Fibonacci heap of N nodes
  for(each node w in the root list of H) {
    x = w;
    d = x.degree;
    while(A[d] != NULL) {
       y = A[d];
       if(x.key > y.key) exchange x with y;
       Fibonacci_Heap_Link(H, y, x);
       A[d] = NULL;
       d = d + 1;
    }
    A[d] = x;
  }
  H.min = NULL;
  for(i = 0 to D(H.n)) {
    if(A[i] != NULL) {
      if(H.min == NULL) {
        create a root list for H only containing A[i];
        H.min = A[i];
      }
     else {
        add A[i] to the root list of H;
        if(A[i].key < H.min.key)
                 H.min = A[i];
        }
    }
  }
}



Fibonacci_Heap_Link(H, y, x) {
  remove y from the root list of H;
  make y a child of x;
  x.degree = x.degree + 1;
  // y.mark = FALSE; // This statement is commented out, because you
                       // do not need it in this project.
}


// Fibonacci_Heap_Get_Min(H) { 
//   return H.min;
// }

template<typename TYPE,typename COMP>
const TYPE&fib_heap<TYPE,COMP>::get_min() const
{
    if(this->empty())
    {
        return empty_fib;
    }
    else
    {
        return (*min).key;
    }
};

template<typename TYPE,typename COMP>
bool fib_heap<TYPE,COMP>::empty() const
{
    return this->size()==0;
};

template<typename TYPE,typename COMP>
unsigned fib_heap<TYPE,COMP>::size() const
{
    return n;
};

























#endif //FIB_HEAP_H
