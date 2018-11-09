#include <iostream>
#include <getopt.h>
#include "priority_queue.h"
#include "binary_heap.h"
#include "fib_heap.h"
#include "unsorted_heap.h"

using namespace std;

class point {
public:
    int x;
    int y;
    int cellweight=0;
    int pathcost=0;
    bool reached=false;
    point *predecessor=NULL;
    friend bool operator==(const point &p1,const point &p2)
    {
        return (p1.x==p2.x&&p1.y==p2.y&&p1.cellweight==p2.cellweight&&p1.pathcost==p2.pathcost&&p1.reached==p2.reached&&p1.predecessor==p2.predecessor);
    }
    friend bool operator<(const point &p1,const point &p2)
    {
        return p1.pathcost<p2.pathcost;
    }
    friend bool operator>(const point &p1,const point &p2)
    {
        return p1.pathcost>p2.pathcost;
    }
    // struct compare_t
    // {
    //     bool operator()(const point &a, const point &b) const
    //     {
    //         return (a.pathcost<b.pathcost)||((a.pathcost==b.pathcost)&&(a.x<b.x))||((a.pathcost==b.pathcost)&&(a.x==b.x)&&(a.y<b.y));
    //     }
    // };
};

int main(int argc, char *argv[]) {
	
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int width,height=0;
    cin>>width;
    cin>>height;
    int start_point_x,start_point_y,end_point_x,end_point_y;
    cin>>start_point_x>>start_point_y>>end_point_x>>end_point_y;
    point p_array[height][width];
    for(int h=0;h<height;++h)
    {
        for(int w=0;w<width;++w)
        {
            cin>>p_array[h][w].cellweight;
        }
    }
    for(int h=0;h<height;++h)
    {
        for(int w=0;w<width;++w)
        {
            p_array[h][w].x=w;
            p_array[h][w].y=h;
            p_array[h][w].pathcost=p_array[h][w].cellweight;
        }
    }
    


    bool verbose=false;
    string mode;
    while(true)
    {
        static struct option long_options[]=
        {
            {"verbose",no_argument,NULL,'v'},
            {"implementation",required_argument,NULL,'i'},
            {0, 0, 0, 0}
        };
        int c=getopt_long(argc,argv,"vi:",long_options,NULL);
        if(c==-1)
        {
            break;
        }
        if(c=='v')
        {
            verbose=true;
        }
        if(c=='i')
        {
            mode=optarg;
        }
    }
    priority_queue<point,point::compare_t> *priority_q;
    if(mode=="BINARY")
    {
        priority_q=new binary_heap<point,point::compare_t>();
    }
    else if(mode=="UNSORTED")
    {
        priority_q=new unsorted_heap<point,point::compare_t>();
    }
    else if(mode=="FIBONACCI")
    {
        priority_q=new fib_heap<point,point::compare_t>();
    }
    else
    {
        exit(0);
    }







}











