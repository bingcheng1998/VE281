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
    unsigned int N_num;
    unsigned int maxDegree;
    struct Node{
        TYPE key;
        unsigned int degree;
        Node *left;
        Node *right;
        Node *child;
        Node *parent;
        Node(TYPE t_value=TYPE()):key(t_value),parent(NULL),child(NULL),
                                  left(this),right(this),degree(0)
        {}
    };
    Node *min;
    std::vector<Node*> root;
    void Insert_l(Node *a,Node *b);
    void Fibonacci_Heap_Link(Node *y,Node *x);
    void Consolidate();
    // Add any additional member functions or data you require here.
    // You may want to define a strcut/class to represent nodes in the heap and a
    // pointer to the min node in the heap.

};

// Add the definitions of the member functions here. Please refer to
// binary_heap.h for the syntax.

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> ::Insert_l(Node *a, Node *b) {
    if(a!=NULL){
        b->left->right=b->right;
        b->right->left=b->left;
        a->right->left=b;
        b->right=a->right;
        a->right=b;
        b->left=a;
        b->parent=a->parent;
        if(a->parent!=NULL) a->parent->degree+=1;
    }
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> ::Fibonacci_Heap_Link(Node *y,Node *x){
    unsigned int id;
    for(int i=0;i<root.size();i++){
        if(root[i]==y) id=i;
    }
    Node *tmp=root[id];
    root[id]=root[root.size()-1];
    root.pop_back();
    if(x->child==NULL){
        x->child=tmp;
        tmp->parent=x;
        tmp->left->right=tmp->right;
        tmp->right->left=tmp->left;
        tmp->left=tmp;
        tmp->right=tmp;
        x->degree+=1;
    }
    else{
        Insert_l(x->child,y);
    }
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> ::Consolidate() {
    int size_of_root=N_num;
    std::vector<Node*> A(size_of_root,NULL);
    for(int i=0;i<root.size();i++){
        Node *x=root[i];
        unsigned int d=x->degree;
        while(A[d]!=NULL){
            Node *y=A[d];
            if(compare(x->key,y->key)){
                Node *tmp=x;
                x=y;
                y=tmp;
            }
            Fibonacci_Heap_Link(y,x);
            A[d]=NULL;
            d+=1;
        }
        A[d]=x;
    }
    this->min=NULL;
    for(int j=0;j<root.size();j++){
        Node *t=root[j];
        if(this->min==NULL) this->min=root[j];
        else{
            if(compare(this->min->key,t->key)) this->min=root[j];
        }
    }
}

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> ::fib_heap(COMP comp) {
    compare = comp;
    this->min=NULL;
    this->N_num=0;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    Node *tmp=new Node(val);
    tmp->degree=0;
    tmp->child=NULL;
    tmp->parent=NULL;
    if(this->min==NULL){
        root.push_back(tmp);
        this->min=tmp;
        tmp->left=tmp;
        tmp->right=tmp;
    }
    else{
        root.push_back(tmp);
        Insert_l(min,tmp);
        if(compare(this->min->key,tmp->key)) this->min=tmp;
    }
    this->N_num+=1;
};

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP> :: dequeue_min(){
    Node *z=this->min;
    if(z!=NULL){
        if(z->child!=NULL){
            Node *x=z->child;
            do{
                root.push_back(x);
                x->parent=NULL;
                x=x->right;
            }while(x!=z->child);
            x->left->right=z->right;
            z->right->left=x->left;
            x->left=z->left;
            z->left->right=x;
        }
        unsigned int id;
        for(int i=0;i<root.size();i++){
            if(root[i]==z) id=i;
        }
        root[id]=root[root.size()-1];
        root.pop_back();
        this->N_num-=1;
        if(this->N_num==0)this->min=NULL;
        else Consolidate();
    }
    return z->key;
};

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP> :: get_min() const{
    return this->min->key;
};

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP> :: size() const {
    return this->N_num;
    // Fill in the body.
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP> :: empty() const {
    return this->min==NULL;
    // Fill in the body.
}
#endif //FIB_HEAP_H
