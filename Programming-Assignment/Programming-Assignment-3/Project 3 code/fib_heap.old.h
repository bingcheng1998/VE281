//
//  fib_heap.h
//  VE281 2018 Autumn
//  project3
//  Bingcheng HU
//
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
    struct Node{
        TYPE key;
        unsigned int degree;
        Node *child;
        Node *parent;
        Node *left;
        Node *right;
        Node(TYPE t_value=TYPE()):
        key(t_value),parent(NULL),child(NULL),
        left(this),right(this),degree(0){}
    };
    unsigned int Node_count;
    Node *min;
    std::vector<Node*> root;
    TYPE empty_fib=TYPE();
    virtual void Insert2left(Node *origin_node, Node *new_node);
    virtual void Fibonacci_Heap_Link(Node *y,Node *x);
    virtual void Consolidate();

};

// Add the definitions of the member functions here. Please refer to
// binary_heap.h for the syntax.

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> ::Insert2left(Node *origin_node, Node *new_node) {
    if(origin_node!=NULL){
        new_node->left->right=new_node->right;
        new_node->right->left=new_node->left;
        origin_node->right->left=new_node;
        new_node->right=origin_node->right;
        origin_node->right=new_node;
        new_node->left=origin_node;
        new_node->parent=origin_node->parent;
        if(origin_node->parent!=NULL) origin_node->parent->degree+=1;
    }
}


template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> ::Fibonacci_Heap_Link(Node *y,Node *x){
    unsigned int id;
    for(int i=0;i<root.size();i++){
        if(root[i]==y) id=i;
    }
    Node *N=root[id];
    root[id]=root[root.size()-1];
    root.pop_back();
    if(x->child==NULL){
        x->degree+=1;
        x->child=N;
        N->parent=x;
        N->left->right=N->right;
        N->right->left=N->left;
        N->left=N;
        N->right=N;
    }
    else Insert2left(x->child,y);
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> ::Consolidate() {
    int root_size = Node_count;
    std::vector<Node*> A(root_size,NULL);
    for(int i=0; i<root.size(); ++i){
        Node *x=root[i];
        unsigned int d=x->degree;
        while(A[d]!=NULL){
            Node *y=A[d];
            if(compare(y->key,x->key)){
                Node *N=x;
                x=y;
                y=N;
            }
            Fibonacci_Heap_Link(y,x);
            A[d]=NULL;
            d++;
        }
        A[d]=x;
    }
    this->min=NULL;
    for(int j=0;j<root.size();j++){
        Node *t=root[j];
        if(this->min==NULL) this->min=root[j];
        else if(compare( t->key,this->min->key)) 
            this->min=root[j];
    }
}

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> ::fib_heap(COMP comp) {
    this->Node_count=0;
    compare = comp;
    this->min=NULL;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    Node *N=new Node(val);
    N->degree=0;
    N->child=NULL;
    N->parent=NULL;
    if(this->min==NULL){
        root.push_back(N);
        this->min=N;
        N->right=N;
        N->left=N;
    }
    else{
        root.push_back(N);
        Insert2left(min,N);
        if(compare(N->key,this->min->key)) this->min=N;
    }
    this->Node_count+=1;
};


template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP> :: dequeue_min(){
    TYPE key_out = min->key;
    Node *mid_node=this->min;
    if(mid_node!=NULL){
        if(mid_node->child!=NULL){
            Node *new_mid=mid_node->child;
            do{
                root.push_back(new_mid);
                new_mid->parent=NULL;
                new_mid=new_mid->right;
            }while(new_mid!=mid_node->child);
            new_mid->left->right=mid_node->right;
            mid_node->right->left=new_mid->left;
            new_mid->left=mid_node->left;
            mid_node->left->right=new_mid;
        }
        // delete mid_node;
        unsigned int id;
        for(int i=0;i<root.size();i++){
            if(root[i]==mid_node) id=i;
        }


        root.erase(root.begin()+id);
        // delete mid_node;
        this->Node_count-=1;
        if(this->Node_count==0)this->min=NULL;
        else Consolidate();
    }
    return key_out;
};

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP> :: get_min() const{
    if(this->empty())
    {
        return empty_fib;
    }
    return min->key;
};

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP> :: size() const {
    return Node_count;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP> :: empty() const {
    return this->size()==0;
}

#endif //FIB_HEAP_H
