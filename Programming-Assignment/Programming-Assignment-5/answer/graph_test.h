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
struct Edge;

struct Node {
  int code = 0;
  int D = 0;
  list<Edge> adjacent_list;
  list<Edge> undirected_list;
  int degree = 0;
};

struct Edge {
  Node *end_node;
  int weight = 0;
};

struct Edge_comp {
  bool operator()(const Node *a, const Node *b) const {
    return a->code < b->code;
  }
};

struct Graph {
  vector<Node *> NodeAll_vec; // compare by in_degree
  multimap<Node *, Edge, Edge_comp> EdgeAll_map; // compare by code
  multimap<Node *, Edge, Edge_comp> Undirected_EdgeAll_map; //compare by code
};

struct comp_D {
  bool operator()(const Node *a, const Node *b) const {
    return a->D < b->D;
  }
};

bool comp_node_degree(const Node *a, const Node *b);
bool comp_node_code(const Node *a, const Node *b);

void tell_DAG(Graph graph);

// void Shortest_Path(Graph graph, int source_node_code, int destination_node_code);

void calculate_MST(Graph graph);

#endif