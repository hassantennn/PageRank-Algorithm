#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "AdjacencyList.h"
using namespace std;

void AdjacencyList::add(int source, int target) {
    // Adds a directed edge from 'source' to 'target' with default weight zero
    if (!adj_list.count(source)) {
        adj_list[source] = vector<pair<int, double>>();
    }
    adj_list[target].emplace_back(source, 0.0);
}

map<string, int>& AdjacencyList::urls() {
    // Returns a reference to the URL-ID mapping
    return url_ids;
}

void AdjacencyList::assign_id(const string& link) {
    // Assigns a unique ID to each URL and advances the counter
    url_ids[link] = id_counter;
    id_counter++;
}

void AdjacencyList::show_ids() {
    // Outputs URLs and their corresponding IDs
    for (auto url_it = url_ids.cbegin(); url_it != url_ids.cend(); ++url_it) {
        cout << url_it->first << " " << url_it->second << endl;
    }
}

map<string, int>& AdjacencyList::degrees() {
    // Returns the map for out-degrees of URLs
    return out_degree;
}

void AdjacencyList::increment_degree(const string& link) {
    // Increments the out-degree count for a given URL
    out_degree[link]++;
}

void AdjacencyList::set_weights() {
    // Computes initial weights for all edges based on out-degrees
    for (auto adj_it = adj_list.begin(); adj_it != adj_list.end(); ++adj_it) {
        for (auto& connection : adj_it->second) {
            int origin_id = connection.first;
            double& weight_ref = connection.second;
            string origin_url = "";

            // Find URL for each ID
            for (auto map_it = url_ids.cbegin(); map_it != url_ids.cend(); ++map_it) {
                if (map_it->second == origin_id) {
                    origin_url = map_it->first;
                    break;
                }
            }
            weight_ref = 1.0 / out_degree[origin_url];
        }
    }
}

void AdjacencyList::calculate_rank(int num_iterations) {
    // Calculate PageRank over specified iterations
    set_weights();
    const int total_links = url_ids.size();

    // Initialize PageRank values uniformly
    for (int idx = 1; idx <= total_links; ++idx) {
        page_rank[idx] = 1.0 / total_links;
    }

    for (int iteration = 0; iteration < num_iterations - 1; ++iteration) {
        map<int, double> temp_rank;

        // Update rank based on incoming edges
        for (auto adj_it = adj_list.cbegin(); adj_it != adj_list.cend(); ++adj_it) {
            int node = adj_it->first;
            double accumulated_rank = 0.0;

            for (const auto& edge : adj_it->second) {
                int from_node = edge.first;
                double edge_weight = edge.second;
                accumulated_rank += edge_weight * page_rank[from_node];
            }
            temp_rank[node] = accumulated_rank;
        }

        page_rank = std::move(temp_rank);
    }

    display_rank();
}

map<int, double>& AdjacencyList::rank() {
    // Provides access to PageRank values
    return page_rank;
}

void AdjacencyList::display_rank() {
    // Organizes URLs alphabetically and prints each with its PageRank
    vector<pair<string, double>> rank_data;

    // Prepare URL and rank pairs for sorting
    for (auto url_iter = url_ids.cbegin(); url_iter != url_ids.cend(); ++url_iter) {
        const string& url = url_iter->first;
        int url_id = url_iter->second;
        rank_data.emplace_back(url, page_rank[url_id]);
    }

    // Sort URLs alphabetically
    sort(rank_data.begin(), rank_data.end(),
         [](const pair<string, double>& lhs, const pair<string, double>& rhs) {
             return lhs.first < rhs.first;
         });

    // Output URLs with their calculated PageRank values
    for (auto rank_iter = rank_data.cbegin(); rank_iter != rank_data.cend(); ++rank_iter) {
        cout << rank_iter->first << " " << fixed << setprecision(2) << rank_iter->second << endl;
    }
}
