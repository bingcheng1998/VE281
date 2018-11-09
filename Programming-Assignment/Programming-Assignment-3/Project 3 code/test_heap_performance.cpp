#include <iostream>
#include "priority_queue.h"
#include "binary_heap.h"
#include "unsorted_heap.h"
#include "fib_heap.h"
#include <list>
#include <algorithm>
#include <cassert>


using namespace std;

#define ROUND_TIME 10

struct compare_t {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

const string heapName[] = {
    "unsorted_heap","binary_heap","fib_heap", "ERROR_HEAP"
};

int main(int argc, char *argv[]) {

    clock_t start, end, time_all;
    const int size = 50;
    vector<int> a(size);
    for (int i = 0; i < size; i++) {
        a[i] = rand()%100;
    }
    int i;
    int valmin, valmax;

    for (int round = 1; round < ROUND_TIME; ++round)
    {
        int current_size = size*round/ROUND_TIME;
        cerr<<"current_size = "<<current_size<<endl;
//-----------------------------------------------------------
//                         unsorted_heap
//-----------------------------------------------------------
        cerr<<"heap way is: ["<< heapName[0]<<"]"<<endl;
        start = clock();
        priority_queue<int, compare_t> *pql = new unsorted_heap<int, compare_t>;
        for (i = 0; i < current_size; i++)
            pql->enqueue(a[i]);

        valmax = pql->dequeue_min();
        //cout << "Sort in descending order: " << flush;
        for (i = 1; i < current_size; i++) {
            int val = pql->dequeue_min();
            assert(val <= valmax);
            valmax = val;
            //cout << val << " " << flush;
        }
        //cout << endl;
        delete pql;
//-----------------------------------------------------------
        priority_queue<int> *pqs = new unsorted_heap<int>;
        for (i = 0; i < current_size; i++)
            pqs->enqueue(a[i]);

        valmin = pqs->dequeue_min();
        //cout << "Sort in ascending order: " << flush;
        for (i = 1; i < current_size; i++) {
            int val = pqs->dequeue_min();
            assert(val >= valmin);
            valmin = val;
            //cout << val << " " << flush;
        }
        //cout << endl;
        delete pqs;
        end = clock();
        time_all = end - start;
        cout <<"run_time = "<< time_all << endl;
//-----------------------------------------------------------
//                         binary_heap
//-----------------------------------------------------------
        cerr<<"heap way is: ["<< heapName[1]<<"]"<<endl;
        start = clock();
        pql = new binary_heap<int, compare_t>;
        for (i = 0; i < current_size; i++)
            pql->enqueue(a[i]);

        valmax = pql->dequeue_min();
        
        cout << "Sort in descending order: " << flush;
        cout << valmax << " " << flush;
        for (i = 1; i < current_size; i++) {
            int val = pql->dequeue_min();
            assert(val <= valmax);
            valmax = val;
            cout << val << " " << flush;
        }
        cout << endl;
        delete pql;
//-----------------------------------------------------------
        pqs = new binary_heap<int>;
        for (i = 0; i < current_size; i++)
            pqs->enqueue(a[i]);

        valmin = pqs->dequeue_min();
        cout << "Sort in ascending order: " << flush;
        cout << valmin << " " << flush;
        for (i = 1; i < current_size; i++) {
            int val = pqs->dequeue_min();
            assert(val >= valmin);
            valmin = val;
            cout << val << " " << flush;
        }
        cout << endl;
        delete pqs;
        end = clock();
        time_all = end - start;
        cout <<"run_time = "<< time_all << endl;
//-----------------------------------------------------------
//                         fib heap
//-----------------------------------------------------------
        cerr<<"heap way is: ["<< heapName[2]<<"]"<<endl;
        start = clock();
        pql = new fib_heap<int, compare_t>;
        for (i = 0; i < current_size; i++)
            pql->enqueue(a[i]);

        valmax = pql->dequeue_min();
        
        cout << "Sort in descending order: " << flush;
        cout << valmax << " " << flush;
        for (i = 1; i < current_size; i++) {
            int val = pql->dequeue_min();
            assert(val <= valmax);
            valmax = val;
            cout << val << " " << flush;
        }
        cout << endl;
        delete pql;
//-----------------------------------------------------------
        pqs = new fib_heap<int>;
        for (i = 0; i < current_size; i++)
            pqs->enqueue(a[i]);

        valmin = pqs->dequeue_min();
        cout << "Sort in ascending order: " << flush;
        cout << valmin << " " << flush;
        for (i = 1; i < current_size; i++) {
            int val = pqs->dequeue_min();
            assert(val >= valmin);
            valmin = val;
            cout << val << " " << flush;
        }
        cout << endl;
        delete pqs;
        end = clock();
        time_all = end - start;
        cout <<"run_time = "<< time_all << endl;
//-----------------------------------------------------------

    }







    // priority_queue<int, compare_t> *pql = new fib_heap<int, compare_t>;



    // for (i = 0; i < size; i++)
    //     pql->enqueue(a[i]);

    // //cout << "Sort in descending order: " << flush;
    // for (i = 0; i < size; i++) {
    //     int val = pql->dequeue_min();
    //     //cout << val << " " << flush;
    // }
    // //cout << endl;
    // cout << clock() - c << endl;



    // delete pql;

    // // For some built-in types or library types, they may define a default less
    // // than operator. In this case, when you declare a priority queue, you can
    // // omit the second template parameter COMP and it will still work. See
    // // priority_queue.h, binary_heap.h, and unsorted_heap.h, from which you
    // // will notice that by default COMP =  std::less<TYPE>.
    // //
    // // For the following example, we omit the second template parameter, so the
    // // priority queue uses the default less than operator defined on int. In
    // // this queue, the smaller the int value is, the less prior it is.
    // priority_queue<int> *pqs = new fib_heap<int>;
    // for (i = 0; i < size; i++)
    //     pqs->enqueue(a[i]);

    // //cout << "Sort in ascending order: " << flush;
    // for (i = 0; i < size; i++) {
    //     int val = pqs->dequeue_min();
    //     //cout << val << " " << flush;
    // }
    // //cout << endl;


    // delete pqs;
    return 0;
}
