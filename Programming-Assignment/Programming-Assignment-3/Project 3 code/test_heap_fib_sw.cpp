#include <iostream>
#include "priority_queue.h"
#include "fib_heap_sw.h"
#include <list>
#include <algorithm>
#include <ctime>

using namespace std;

struct compare_t {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

int main(int argc, char *argv[]) {
    const int size = 10;
    vector<int> a(size);
    for (int i = 0; i < size; i++) {
        a[i] = rand()%100;
    }
    int i;
    cout << "Input: ";
    for (i = 0; i < size; i++)
    cout << a[i] << " " << flush;
    cout << endl;

    auto c = clock();

    priority_queue<int, compare_t> *pql = new fib_heap<int, compare_t>;
    for (i = 0; i < size; i++)
        pql->enqueue(a[i]);

    cout << "Sort in descending order: " << flush;
    for (i = 0; i < size; i++) {
        int val = pql->dequeue_min();
        cout << val << " " << flush;
    }
    cout << endl;
    // cout << clock() - c << endl;
    delete pql;

    priority_queue<int> *pqs = new fib_heap<int>;
    for (i = 0; i < size; i++)
        pqs->enqueue(a[i]);

    cout << "Sort in ascending order: " << flush;
    for (i = 0; i < size; i++) {
        int val = pqs->dequeue_min();
        cout << val << " " << flush;
    }
    cout << endl;


    delete pqs;
    return 0;
}
