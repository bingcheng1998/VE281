#include <iostream>

#include "graph_test.h"

using namespace std;

bool degree_comp(const Node *a, const Node *b) {
    return a->degree < b->degree;
}

bool order_comp(const Node *a, const Node *b) {
    return a->order_num < b->order_num;
}

static void printDAG(bool isDAG) {
    if (!isDAG) {
        cout << "The graph is not a DAG" << endl;
    } else {
        cout << "The graph is a DAG" << endl;
    }
}

static void printMST(bool MST_exist, int weight_all){
    if (!MST_exist) {
        cout << "The total weight of MST is " << weight_all << endl;
    } else {
        cout << "No MST exists!" << endl;
    }
}

void set_graph(Graph &graph, Edge &edge_temp, int node_start_code, int node_end_code){
    Edge edge_undirected_I;
    Edge edge_undirected_II;
    edge_undirected_I.weight = edge_undirected_II.weight = edge_temp.weight;
    graph.node_vec[node_start_code]->order_num = node_start_code;
    graph.node_vec[node_end_code]->order_num = node_end_code;
    graph.node_vec[node_end_code]->degree++;
    graph.node_vec[node_end_code]->smallest_weight = 0;
    graph.node_vec[node_start_code]->smallest_weight = graph.node_vec[node_end_code]->smallest_weight;
    edge_temp.end_node = graph.node_vec[node_end_code];
    edge_undirected_I.end_node = graph.node_vec[node_end_code];
    edge_undirected_II.end_node = graph.node_vec[node_start_code];
    graph.node_vec[node_start_code]->adjacent_list.push_back(edge_temp);
    graph.node_vec[node_start_code]->undirected_list.push_back(edge_undirected_I);
    graph.node_vec[node_end_code]->undirected_list.push_back(edge_undirected_II);
    graph.edge_map.insert(make_pair(graph.node_vec[node_start_code], edge_temp));
    graph.undirected_edge_map.insert(make_pair(graph.node_vec[node_start_code], edge_undirected_I));
    graph.undirected_edge_map.insert(make_pair(graph.node_vec[node_end_code], edge_undirected_II));
}

void tell_DAG(Graph graph) {
    std::sort(graph.node_vec.begin(), graph.node_vec.end(), degree_comp);
    vector<Node *> S;
    for (auto &it : graph.node_vec) {
        if (it->degree == 0) {
            S.push_back(it);
        } else {
            break;
        }
    }
    std::sort(graph.node_vec.begin(), graph.node_vec.end(), order_comp);
    while (!S.empty()) {
        auto n = *S.begin();
        S.erase(S.begin());
        for (auto it = n->adjacent_list.begin(); it != n->adjacent_list.end(); ++it) {
            auto m = it->end_node;
            for (auto tt = graph.edge_map.begin(); tt != graph.edge_map.end(); ++tt) {
                if (tt->first == n && tt->second.end_node == m) {
                    graph.edge_map.erase(tt);
                    break;
                }
            }
            m->degree--;
            if (!m->degree) {
                S.push_back(m);
            }
        }
    }
    printDAG(graph.edge_map.empty());
}

void calculate_MST(Graph graph) {
    multiset<Node *, smallest_weight_comp> connected_nodes;
    multiset<Node *, smallest_weight_comp> disperse_nodes;
    std::sort(graph.node_vec.begin(),
              graph.node_vec.end(),
              order_comp);
    auto size = graph.node_vec.size();
    for (int i = 0; i < size; ++i) {
        graph.node_vec[i]->smallest_weight = INFINITY;
    }
    graph.node_vec[0]->smallest_weight = 0;
    connected_nodes.clear();
    for (int i = 0; i < size; ++i) {
        disperse_nodes.insert(graph.node_vec[i]);
    }
    int weight_all = 0;
    bool MST_exist = false;
    while (!disperse_nodes.empty()) {
        auto v = *disperse_nodes.begin();
        if (v->smallest_weight == INFINITY) {
            MST_exist = true;
            break;
        }
        weight_all += v->smallest_weight;
        connected_nodes.insert(v);
        disperse_nodes.erase(disperse_nodes.begin());
        for (auto undirected_list_it = v->undirected_list.begin(); undirected_list_it != v->undirected_list.end();
             ++undirected_list_it) {
            auto u = undirected_list_it->end_node;
            for (auto disperse_nodes_it = disperse_nodes.begin(); disperse_nodes_it != disperse_nodes.end();
                ++disperse_nodes_it) {
                if ((*disperse_nodes_it) == u) {
                    auto it_u = disperse_nodes_it;
                    int current_weight = 0;
                    for (auto it = graph.undirected_edge_map.begin(); it != graph.undirected_edge_map.end();) {
                        if (it->second.end_node == u && it->first == v) { // Edge from v to u
                            current_weight = it->second.weight;
                            it = graph.undirected_edge_map.erase(it);
                            break;
                        } else {
                            it++;
                        }
                    }
                    if (u->smallest_weight > current_weight) {
                        u->smallest_weight = current_weight;
                    }
                    for (auto it = graph.undirected_edge_map.begin(); it != graph.undirected_edge_map.end();) {
                        if (it->first == u && it->second.end_node == v) { // Edge from u to v
                            it = graph.undirected_edge_map.erase(it);
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
                    disperse_nodes.erase(it_u); // erase and insert Node u to get the correct order in next loop
                    disperse_nodes.insert(u);
                    break;
                }
            }
        }
    }
    printMST(MST_exist, weight_all);
}