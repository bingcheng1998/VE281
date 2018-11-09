//
//  main.cpp
//  VE281 2018 Autumn
//  project3
//  Bingcheng HU
//
#include <iostream>
#include <getopt.h>
#include <tgmath.h>
#include "priority_queue.h"
#include "binary_heap.h"
#include "fib_heap.h"
#include "unsorted_heap.h"

using namespace std;
static int verbose;

class point {
public:
    int x;
    int y;
    int cellweight=0;
    int cost=0;
    bool reached=false;
    point *predecessor=NULL;
    friend bool operator==(const point &p1,const point &p2)
    {
        return (p1.x==p2.x&&p1.y==p2.y&&p1.cellweight==p2.cellweight&&p1.cost==p2.cost&&p1.reached==p2.reached&&p1.predecessor==p2.predecessor);
    }
    friend ostream &operator<<(ostream &out, const point &p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
//     During a dequeueMin() operation, if multiple cells have the same smallest path
// cost, choose the cell with the smallest x-coordinate. Furthermore, if there are multiple
// cells with the same x-coordinate, choose the cell with the smallest y-coordinate.
    struct compare_t
    {
        // bool operator()(const point &a, const point &b) const
        // {
        //     return (a.cost<b.cost)||((a.cost==b.cost)&&(a.x<b.x))||((a.cost==b.cost)&&(a.x==b.x)&&(a.y<b.y));

        //     // if (a.cost != b.cost) return a.cost < b.cost;
        //     // if (a.y != b.y) return a.y < b.y;
        //     // return a.x < b.x;
        // }
        bool operator()(const point &a, const point &b) const {
            if (a.cost != b.cost) return a.cost < b.cost;
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        }
    };
};

void trace_back_path(point *p){
    if(p!=NULL){
        trace_back_path(p->predecessor);
        // cout<<*p<<endl;
    }
    return;
}

void clean_matrix(point **point_A,int y_length, int x_length){
    for(int h=0;h<y_length;++h){
        for(int w=0;w<x_length;++w){
            point_A[h][w].x=w;
            point_A[h][w].y=h;
            point_A[h][w].cost=point_A[h][w].cellweight;
            point_A[h][w].reached = false;
        }
    }
}

clock_t test_time(point **point_A, int y_length, int x_length, int mode){
    int start_y = 0;
    int start_x = 0;
    int end_y = y_length-1;
    int end_x = x_length-1;
    clock_t start_t, end_t;
    start_t = clock();
    // cout<<"start at "<<start_t;
    priority_queue<point,point::compare_t> *priority_q;
    if(mode== 1) //"BINARY")
    {
        priority_q=new binary_heap<point,point::compare_t>();
    }
    else if(mode== 0) //"UNSORTED")
    {
        priority_q=new unsorted_heap<point,point::compare_t>();
    }
    else if(mode== 2) //"FIBONACCI")
    {
        priority_q=new fib_heap<point,point::compare_t>();
    }
    else
    {
        exit(0);
    }
    
    int verbose = 0;
    point_A[start_y][start_x].reached=true;
    priority_q->enqueue(point_A[start_y][start_x]);
    int step=0;
    while(priority_q->empty()==false){
        point C=priority_q->dequeue_min();
        if(verbose==1){
            cout<<"Step "<<step<<endl;
            cout<<"Choose cell ("<<point_A[C.y][C.x].x<<", "<<point_A[C.y][C.x].y
            <<") with accumulated length "<<point_A[C.y][C.x].cost<<"."<<endl;
        }
        step++;
//      The visit of the neighbors starts form the right neighbor and then goes in the
// clockwise direction, i.e., right, down, left, up. For those cells on the boundary, they
// may not have a certain neighbor. Then you just skip it.
        int clockwise_x[4]={1,0,-1,0};
        int clockwise_y[4]={0,1,0,-1};
        for(int i=0;i<4;++i){
            int N_x=point_A[C.y][C.x].x+clockwise_x[i];
            int N_y=point_A[C.y][C.x].y+clockwise_y[i];
            if(N_x<0||N_x>x_length-1||
                N_y<0||N_y>y_length-1||
                point_A[N_y][N_x].reached==true) 
                continue;
            point_A[N_y][N_x].reached=true;
            point_A[N_y][N_x].cost=point_A[C.y][C.x].cost+point_A[N_y][N_x].cellweight;
            point_A[N_y][N_x].predecessor=&point_A[C.y][C.x];
            if(point_A[end_y][end_x].x==point_A[N_y][N_x].x&&point_A[end_y][end_x].y==point_A[N_y][N_x].y){
                
                auto end_node = &point_A[end_y][end_x];
                // cout<<"The shortest path from ("<<point_A[start_y][start_x].x<<", "
                // <<point_A[start_y][start_x].y<<") to ("<<point_A[end_y][end_x].x
                // <<", "<<point_A[end_y][end_x].y<<") is "<<point_A[N_y][N_x].cost<<"."<<endl;
                // cout<<"Path:"<<endl;
                cerr<<"cost = "<< point_A[N_y][N_x].cost<<" ";
                trace_back_path(&point_A[end_y][end_x]);
                delete priority_q;
                end_t = clock();
                return clock() - start_t;
            }
            else{
                priority_q->enqueue(point_A[N_y][N_x]);
            }
        }
    }
    delete priority_q;

    end_t = clock();
    return 0;
}
const string heapName[] = {
    "unsorted_heap","binary_heap","fibonaci_heap", "ERROR_HEAP"
};

int main(int argc,char* argv[])
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
//----------------- Get Operation-------------------
//-------------------get file input-----------------
    
    int x_length = 0,y_length=0;
    cin>>x_length>>y_length;
    int start_x,start_y,end_x,end_y;
    cin>>start_x>>start_y>>end_x>>end_y;
    
    // point point_A[y_length][x_length];
    point** point_A;
    point_A = new point *[x_length];
    for (int i = 0; i < x_length; ++i)
    {
        point_A[i] = new point [y_length];
    }
    for(int h=0;h<y_length;++h){
        for(int w=0;w<x_length;++w){
            cin>>point_A[h][w].cellweight;
        }
    }
    
//-------------------calculate path------------------
//     int verbose = 0;
//     point_A[start_y][start_x].reached=true;
//     priority_q->enqueue(point_A[start_y][start_x]);
//     int step=0;
//     while(priority_q->empty()==false){
//         point C=priority_q->dequeue_min();
//         if(verbose==1){
//             cout<<"Step "<<step<<endl;
//             cout<<"Choose cell ("<<point_A[C.y][C.x].x<<", "<<point_A[C.y][C.x].y
//             <<") with accumulated length "<<point_A[C.y][C.x].cost<<"."<<endl;
//         }
//         step++;
// //      The visit of the neighbors starts form the right neighbor and then goes in the
// // clockwise direction, i.e., right, down, left, up. For those cells on the boundary, they
// // may not have a certain neighbor. Then you just skip it.
//         int clockwise_x[4]={1,0,-1,0};
//         int clockwise_y[4]={0,1,0,-1};
//         for(int i=0;i<4;++i){
//             int N_x=point_A[C.y][C.x].x+clockwise_x[i];
//             int N_y=point_A[C.y][C.x].y+clockwise_y[i];
//             if(N_x<0||N_x>x_length-1||
//                 N_y<0||N_y>y_length-1||
//                 point_A[N_y][N_x].reached==true) 
//                 continue;
//             point_A[N_y][N_x].reached=true;
//             point_A[N_y][N_x].cost=point_A[C.y][C.x].cost+point_A[N_y][N_x].cellweight;
//             point_A[N_y][N_x].predecessor=&point_A[C.y][C.x];
//             if(point_A[end_y][end_x].x==point_A[N_y][N_x].x&&point_A[end_y][end_x].y==point_A[N_y][N_x].y){
                
//                 auto end_node = &point_A[end_y][end_x];
//                 cout<<"The shortest path from ("<<point_A[start_y][start_x].x<<", "
//                 <<point_A[start_y][start_x].y<<") to ("<<point_A[end_y][end_x].x
//                 <<", "<<point_A[end_y][end_x].y<<") is "<<point_A[N_y][N_x].cost<<"."<<endl;
//                 cout<<"Path:"<<endl;
//                 trace_back_path(&point_A[end_y][end_x]);
//                 delete priority_q;
//                 return 0;
//             }
//             else{
//                 priority_q->enqueue(point_A[N_y][N_x]);
//             }
//         }
//     }
//     delete priority_q;


    // clean_matrix(point_A, y_length, x_length);
    // x_length = 100
    // y_length = 100;
    // test_time(point_A, y_length, x_length, 1);

    for (int i = 0; i < 12; ++i)
    {
        int size_of_matrix = x_length*pow(2,i+1)/4096;
        cout <<size_of_matrix<<", ";
        for (int j = 0; j < 3; ++j)
        {
            
            int x_len = size_of_matrix;
            int y_len = size_of_matrix;
            clock_t time_run = test_time(point_A, y_len, x_len, j);
            clean_matrix(point_A, y_length, x_length);
            cerr<<"run time of "<<heapName[j]<< "  \tat size "<< size_of_matrix <<"\tis "<<time_run<<endl;
            cout<<time_run<<",";
        }
        cout<<endl;
    }

    for(int i=0;i<y_length;i++)
        delete []point_A[i]; 
        delete []point_A;
    return 0;
}
