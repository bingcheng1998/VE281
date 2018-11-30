#ifndef GRAPH_TEST_H
#define GRAPH_TEST_H

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
struct Edges;

struct Node {
  int code = 0;
  int D = 0;
  list<Edges> adjacent_list;
  list<Edges> undirected_list;
  int degree = 0;
};

struct Edges {
  Node *end_node;
  int weight = 0;
};

struct comp_Edge {
  bool operator()(const Node *a, const Node *b) const {
    return a->code < b->code;
  }
};

struct Graph {
  vector<Node *> NodeAll_vec; // compare by in_degree
  multimap<Node *, Edges, comp_Edge> EdgeAll_map; // compare by code
  multimap<Node *, Edges, comp_Edge> Undirected_EdgeAll_map; //compare by code
};

struct comp_D {
  bool operator()(const Node *a, const Node *b) const {
    return a->D < b->D;
  }
};


bool comp_node_degree(const Node *a, const Node *b);
bool comp_node_code(const Node *a, const Node *b);

void DAG(Graph graph);

// void Shortest_Path(Graph graph, int source_node_code, int destination_node_code);

void MST(Graph graph);

#endif