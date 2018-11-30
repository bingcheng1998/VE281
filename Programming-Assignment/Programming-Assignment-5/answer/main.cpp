#include <iostream>
#include "graph_test.h"

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int node_num;
    cin >> node_num;
    Graph graph = Graph();
    for (int i = 0; i < node_num; i++) {
        graph.node_vec.push_back(new Node);
    }
    getchar();
    stringstream stream_read;
    while (!cin.eof()) {
        string str;
        getline(cin, str);
        if (str.empty()) {
            break;
        }
        stream_read.clear();
        stream_read.str(str);
        int node_start_code, node_end_code;
        Edge edge_temp;
        Edge undirected_edge_temp_1;
        Edge undirected_edge_temp_2;
        stream_read >> node_start_code >> node_end_code >> edge_temp.weight;
        undirected_edge_temp_1.weight = undirected_edge_temp_2.weight = edge_temp.weight;
        graph.node_vec[node_start_code]->code = node_start_code;
        graph.node_vec[node_end_code]->code = node_end_code;
        graph.node_vec[node_end_code]->degree++;
        graph.node_vec[node_start_code]->D = graph.node_vec[node_end_code]->D = 0;
        edge_temp.end_node = graph.node_vec[node_end_code];
        undirected_edge_temp_1.end_node = graph.node_vec[node_end_code];
        undirected_edge_temp_2.end_node = graph.node_vec[node_start_code];
        graph.node_vec[node_start_code]->adjacent_list.push_back(edge_temp);
        graph.node_vec[node_start_code]->undirected_list.push_back(undirected_edge_temp_1);
        graph.node_vec[node_end_code]->undirected_list.push_back(undirected_edge_temp_2);
        graph.edge_map.insert(make_pair(graph.node_vec[node_start_code], edge_temp));
        graph.undirected_edge_map.insert(make_pair(graph.node_vec[node_start_code], undirected_edge_temp_1));
        graph.undirected_edge_map.insert(make_pair(graph.node_vec[node_end_code], undirected_edge_temp_2));
    }
    tell_DAG(graph);
    calculate_MST(graph);
    return 0;
}

