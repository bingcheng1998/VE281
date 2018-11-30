#include <iostream>

#include "graph_test.h"
using namespace std;

bool comp_node_degree(const Node *a, const Node *b) {
  return a->degree < b->degree;
}

bool comp_node_code(const Node *a, const Node *b) {
  return a->code < b->code;
}

static void printDAG(bool isDAG){
  if (!isDAG) {
    cout << "The graph is not a DAG" << endl;
  } else {
    cout << "The graph is a DAG" << endl;
  }
}

void DAG(Graph graph) {
  std::sort(graph.NodeAll_vec.begin(), graph.NodeAll_vec.end(), comp_node_degree);
  vector<Node *> S; // construct a vector to store nodes whose in_degree is zero
  for (auto &it : graph.NodeAll_vec) {
    if (it->degree == 0) {
      S.push_back(it);
    } else {
      break;
    }
  }
  std::sort(graph.NodeAll_vec.begin(), graph.NodeAll_vec.end(), comp_node_code);
  while (!S.empty()) {
    auto n = *S.begin();
    S.erase(S.begin());
    for (auto it = n->adjacent_list.begin(); it != n->adjacent_list.end(); ++it) {
      auto m = it->end_node;
      for (auto tt = graph.EdgeAll_map.begin(); tt != graph.EdgeAll_map.end(); ++tt) {
        if (tt->first == n && tt->second.end_node == m) { // Edges from n to m
          graph.EdgeAll_map.erase(tt); // erase this Edges
          break;
        }
      }
      m->degree--;
      if (!m->degree) {
        S.push_back(m);
      }
    }
  }
  printDAG(graph.EdgeAll_map.empty());
}

void MST(Graph graph) {
  multiset<Node *, comp_D> T; // construct a set T to store the used Node
  multiset<Node *, comp_D> T_; // construct a set T_ to store the unused Node
  std::sort(graph.NodeAll_vec.begin(),
            graph.NodeAll_vec.end(),
            comp_node_code); // make NodeAll.vec ordered by node_code
  auto size = graph.NodeAll_vec.size();
  for (int i = 0; i < size; ++i) {
    graph.NodeAll_vec[i]->D = INT_MAX;
  }
  graph.NodeAll_vec[0]->D = 0;
  T.clear();
  for (int i = 0; i < size; ++i) {
    T_.insert(graph.NodeAll_vec[i]);
  }
  int len = 0;
  int flag = 0;
  while (!T_.empty()) {
    auto v = *T_.begin();
    if (v->D == INT_MAX) {
      flag = 1;
      break;
    }
    len += v->D;
    T.insert(v);
    T_.erase(T_.begin());
    for (auto v_neighbor_it = v->undirected_list.begin(); v_neighbor_it != v->undirected_list.end();
         ++v_neighbor_it) {
      auto u = v_neighbor_it->end_node; // u is v's neighbor
      for (auto it_T_ = T_.begin(); it_T_ != T_.end(); ++it_T_) {
        if ((*it_T_) == u) {
          auto it_u = it_T_;
          int W_u_v = 0;
          for (auto it = graph.Undirected_EdgeAll_map.begin(); it != graph.Undirected_EdgeAll_map.end();) {
            if (it->second.end_node == u && it->first == v) { // Edges from v to u
              W_u_v = it->second.weight;
              it = graph.Undirected_EdgeAll_map.erase(it);
              break;
            } else {
              it++;
            }
          }
          if (u->D > W_u_v) { // update u's D
            u->D = W_u_v;
          }
          for (auto it = graph.Undirected_EdgeAll_map.begin(); it != graph.Undirected_EdgeAll_map.end();) {
            if (it->first == u && it->second.end_node == v) { // Edges from u to v
              it = graph.Undirected_EdgeAll_map.erase(it);
              break;
            } else {
              it++;
            }
          }
          for (auto it = u->undirected_list.begin(); it != u->undirected_list.end();) {
            if (it->end_node == v) { // remove v from u's neighbor
              it = u->undirected_list.erase(it);
              break;
            } else {
              it++;
            }
          }
          T_.erase(it_u); // erase and insert Node u to get the correct order in next loop
          T_.insert(u);
          break;
        }
      }
    }
  }
  if (!flag) {
    cout << "The total weight of MST is " << len << endl;
  } else {
    cout << "No MST exists!" << endl;
  }
}