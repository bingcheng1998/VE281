#ifndef GRAPH_TEST_H
#define GRAPH_TEST_H
#define INFINITY INT_MAX

#include <iostream>
#include <sstream>
#include <algorithm>
#include <climits>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <vector>

using namespace std;
struct Node;
struct Edge;

struct Node {
    int degree = 0;
    int order_num = 0;
    int smallest_weight = 0;
    list<Edge> adjacent_list;
    list<Edge> undirected_list;
};

struct Edge {
    int weight = 0;
    Node *end_node;
};

struct Edge_comp {
    bool operator()(const Node *a, const Node *b) const {
        return a->order_num < b->order_num;
    }
};

struct Graph {
    vector<Node *> node_vec;
    multimap<Node *, Edge, Edge_comp> edge_map;
    multimap<Node *, Edge, Edge_comp> undirected_edge_map;
};

struct smallest_weight_comp {
    bool operator()(const Node *a, const Node *b) const {
        return a->smallest_weight < b->smallest_weight;
    }
};

bool degree_comp(const Node *a, const Node *b);

bool order_comp(const Node *a, const Node *b);

void set_graph(Graph &graph, Edge &edge_temp, int node_start_code, int node_end_code);

void tell_DAG(Graph graph);

void calculate_MST(Graph graph);

#endif