#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class AdjacencyList {
private:
    int id_counter = 1;  // Counter to assign unique IDs to URLs
    map<int, vector<pair<int, double>>> adj_list; // List of connections with weights
    map<string, int> url_ids; // Maps URLs to their IDs
    map<string, int> out_degree; // Tracks the out-degree for each URL
    map<int, double> page_rank; // Stores the PageRank score for each URL ID

public:
    void add(int origin, int destination); // Adds a directed link between nodes
    map<string, int>& urls(); // Provides access to the URL-ID mapping
    void assign_id(const string& url); // Assigns a new ID to a URL
    void show_ids(); // Prints URLs and their assigned IDs

    map<string, int>& degrees(); // Returns the out-degree mapping
    void increment_degree(const string& url); // Increases out-degree of a URL

    void set_weights(); // Sets initial weights on edges
    void calculate_rank(int iterations); // Runs the PageRank algorithm
    map<int, double>& rank(); // Accesses the PageRank scores
    void display_rank(); // Prints URLs with their PageRank scores
};
