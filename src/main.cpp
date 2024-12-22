#include <iostream>
#include "AdjacencyList.h"

using namespace std;

int main() {
    int edge_count, iteration_count;
    string source, destination;

    // Input the number of edges and iterations for PageRank
    cin >> edge_count >> iteration_count;

    // Initialize graph
    AdjacencyList graph;

    // Process each edge
    for (int i = 0; i < edge_count; ++i) {
        cin >> source >> destination;

        // Ensure unique IDs are assigned to URLs
        if (graph.urls().find(source) == graph.urls().end())
            graph.assign_id(source);

        if (graph.urls().find(destination) == graph.urls().end())
            graph.assign_id(destination);

        // Update out-degree for source URL and add edge to the graph
        graph.increment_degree(source);
        graph.add(graph.urls()[source], graph.urls()[destination]);
    }

    // Execute PageRank computation
    graph.calculate_rank(iteration_count);

    return 0;
}
