#include <iostream>
#include "graph_test.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int node_num;
    cin >> node_num;
    Graph graph = Graph();
    for (int i = 0; i < node_num; i++) {
        graph.node_vec.push_back(new Node);
    }
    while (!cin.eof()) {
        int node_start_code, node_end_code;
        Edge edge_temp;
        cin >> node_start_code;
        if (cin.eof()) break;
        cin >> node_end_code >> edge_temp.weight;
        set_graph(graph, edge_temp, node_start_code, node_end_code);
    }
    tell_DAG(graph);
    calculate_MST(graph);
    return 0;
}

