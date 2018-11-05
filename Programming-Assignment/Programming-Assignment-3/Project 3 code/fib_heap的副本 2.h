#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include <list>
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
      // node parent;
      int degree=0;
  };
  typename std::list<node> root;
  typename std::list<node>::iterator min;
  int n=0;
  TYPE empty_fib=TYPE();

  void virtual void Consolidate(typename std::list<node>::iterator A[], 
  typename std::list<node>::iterator it, 
  typename std::list<node>::iterator y
  int d);
  virtual void Fibonacci_Heap_Link(typename std::list<node>::iterator x, typename std::list<node>::iterator y);
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
    min = root.begin();
    n=0;
}

template<typename TYPE,typename COMP>
fib_heap<TYPE,COMP>::~fib_heap()
{
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
    // x.parent = NULL;
    // x.child = NULL;
    if(root.empty()==true)
    {
        root.push_back(x);
        min=root.begin();
    }
    else
    {
        typename std::list<node>::iterator it;
        it=root.insert(root.end(),x);
        if(compare(x.key,(*min).key))
        {
          // typename std::list<node>::iterator it;
          // root.end();
          min = it;
        }
    }
    n++;
};

// Fibonacci_Heap_Dequeue_Min(H) { z = H.min;
//   if(z != NULL) {
//      for(each child x of z) {
//        add x to the root list of H;
//        x.parent = NULL;
//      }
//      remove z from the root list of H;
//      H.n = H.n – 1;
//      if(H.n == 0) H.min = NULL;
   
//   else Consolidate(H);
//     }
//   return z; 
// }

// template<typename TYPE,typename COMP>
// TYPE fib_heap<TYPE,COMP>::dequeue_min()
// {
//     if(root.empty()==true)
//     {
//         return empty_fib;
//     }

// };

template<typename TYPE,typename COMP>
TYPE fib_heap<TYPE,COMP>::dequeue_min()
{
    if(root.empty()==true)
    {
        return empty_fib;
    }
    
//    std::cout<<std::endl;
    
    node z;
    z=*min;
    typename std::list<node>::iterator temp;
    if(min!=root.end())
    {
        temp=z.child.begin();
        while(temp!=z.child.end())
        {
            root.push_back(*temp);
            temp=z.child.erase(temp);
        }
        min=root.erase(min);
        n--;
        if(n==0)
        {
            min=root.end();
        }
        else
        {
//=-------------------------------------------------------------
            int size=int((log(n))/(log((1+sqrt(5))/2)))+1;
            typename std::list<node>::iterator A[size];
            for(int i=0;i<size;++i)
            {
                A[i]=root.end();
            }
//            typename std::list<node>::iterator x;
            typename std::list<node>::iterator y;
            int d=0;
            typename std::list<node>::iterator it;
            for(it=root.begin();it!=root.end();++it)
            {
                
//                std::cout<<"item in A ";
//                for(int i=0;i<size;++i)
//                {
//                    if(A[i]==root.end()){
//                        std::cout<<"NULL"<<" ";
//                    }
//                    else{
//                        std::cout<<(*A[i]).val<<" ";
//                    }
//                }
//                std::cout<<std::endl;
                
                d=(*it).degree;
                while(A[d]!=root.end())
                {
                    y=A[d];
                    
//                    std::cout<<"item in A ";
//                    for(int i=0;i<size;++i)
//                    {
//                        if(A[i]==root.end()){
//                            std::cout<<"NULL"<<" ";
//                        }
//                        else{
//                            std::cout<<(*A[i]).val<<" ";
//                        }
//                    }
//                    std::cout<<std::endl;
                    
                    if(compare((*y).key,(*it).key))
                    {
                        root.insert(y,*it);
                        root.insert(it,*y);
                        it=root.erase(it);
                        y=root.erase(y);
                        it--;
                        y--;
                    }
                                
        // fib_heap<TYPE,COMP>::Consolidate(A, it, y, d);     
//=-------------------------------------------------------------                 
//                    std::cout<<"item in A ";
//                    for(int i=0;i<size;++i)
//                    {
//                        if(A[i]==root.end()){
//                            std::cout<<"NULL"<<" ";
//                        }
//                        else{
//                            std::cout<<(*A[i]).val<<" ";
//                        }
//                    }
//                    std::cout<<std::endl;
//=-------------------------------------------------------------
                    // (*it).child.push_back((*y));
                    // y=root.erase(y);
                    // (*it).degree++;
Fibonacci_Heap_Link(it, y);

                    A[d]=root.end();
//=-------------------------------------------------------------
//                    std::cout<<"item in A ";
//                    for(int i=0;i<size;++i)
//                    {
//                        if(A[i]==root.end()){
//                            std::cout<<"NULL"<<" ";
//                        }
//                        else{
//                            std::cout<<(*A[i]).val<<" ";
//                        }
//                    }
//                    std::cout<<std::endl;
//                    typename std::list<node>::iterator ttt;
//                    int testt=0;
//                    for(ttt=root.begin();ttt!=root.end();++ttt)
//                    {
//                        printf("The %d item in rootlost is %d\n",testt,(*ttt).val);
//                        typename std::list<node>::iterator tttt;
//                        for(tttt=(*ttt).child.begin();tttt!=(*ttt).child.end();++tttt)
//                        {
//                            std::cout<<(*tttt).val<<" ";
//                        }
//                        testt++;
//                        std::cout<<std::endl;
//                    }
//                    std::cout<<"END"<<std::endl;
                    
                    d++;
                }
                A[d]=it;
            }
            min=root.end();
            for(int i=0;i<size;++i)
            {
                if(A[i]!=root.end())
                {
                    if(min==root.end())
                    {
                        min=A[i];
                    }
                    else
                    {
                        if(compare((*A[i]).key,(*min).key))
                        {
                            min=A[i];
                        }
                    }
                }
            }
        }
    }
    return z.key;
};




// Consolidate(H) {
// let A[0..D(H.n)] be a new array; 
//   // D(N) is the maximum degree of
//   // any node in a Fibonacci heap of N nodes
//   for(i = 0 to D(H.n))
//   A[i] = NULL;
//   for(each node w in the root list of H) {
//     x = w;
//     d = x.degree;
//     while(A[d] != NULL) {
//        y = A[d];
//        if(x.key > y.key) exchange x with y;
//        Fibonacci_Heap_Link(H, y, x);
//        A[d] = NULL;
//        d = d + 1;
//     }
//     A[d] = x;
//   }
//   H.min = NULL;
//   for(i = 0 to D(H.n)) {
//     if(A[i] != NULL) {
//       if(H.min == NULL) {
//         create a root list for H only containing A[i];
//         H.min = A[i];
//       }
//      else {
//         add A[i] to the root list of H;
//         if(A[i].key < H.min.key)
//                  H.min = A[i];
//         }
//     }
//   }
// }

template<typename TYPE,typename COMP>
void fib_heap<TYPE,COMP>::Consolidate(typename std::list<node>::iterator A[], 
  typename std::list<node>::iterator it, 
  typename std::list<node>::iterator y
  int d)
{
            int size=int((log(n))/(log((1+sqrt(5))/2)))+1;
            // typename std::list<node>::iterator A[size];
            for(int i=0;i<size;++i)
            {
                A[i]=root.end();
            }
//            typename std::list<node>::iterator x;
            // typename std::list<node>::iterator y;
            // int d=0;
            // typename std::list<node>::iterator it;
            for(it=root.begin();it!=root.end();++it)
            {
                
//                std::cout<<"item in A ";
//                for(int i=0;i<size;++i)
//                {
//                    if(A[i]==root.end()){
//                        std::cout<<"NULL"<<" ";
//                    }
//                    else{
//                        std::cout<<(*A[i]).val<<" ";
//                    }
//                }
//                std::cout<<std::endl;
                
                d=(*it).degree;
                while(A[d]!=root.end())
                {
                    y=A[d];
                    
//                    std::cout<<"item in A ";
//                    for(int i=0;i<size;++i)
//                    {
//                        if(A[i]==root.end()){
//                            std::cout<<"NULL"<<" ";
//                        }
//                        else{
//                            std::cout<<(*A[i]).val<<" ";
//                        }
//                    }
//                    std::cout<<std::endl;
                    
                    if(compare((*y).key,(*it).key))
                    {
                        root.insert(y,*it);
                        root.insert(it,*y);
                        it=root.erase(it);
                        y=root.erase(y);
                        it--;
                        y--;
                    }
}



// Fibonacci_Heap_Link(H, y, x) {
//   remove y from the root list of H;
//   make y a child of x;
//   x.degree = x.degree + 1;
//   // y.mark = FALSE; // This statement is commented out, because you
//                        // do not need it in this project.
// }

template<typename TYPE,typename COMP>
void fib_heap<TYPE,COMP>::Fibonacci_Heap_Link(typename std::list<node>::iterator x, typename std::list<node>::iterator y){
  (*x).child.push_back((*y));
  y=root.erase(y);
  (*x).degree++;
  // A[d]=root.end();
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
