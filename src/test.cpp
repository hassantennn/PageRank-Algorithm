#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "AdjacencyList.h"

using namespace std;

// Helper function to initialize graph data from a formatted input string
void initializeGraph(AdjacencyList &graph, const string &input) {
    istringstream iss(input);
    int edge_count, iteration_count;
    iss >> edge_count >> iteration_count;

    string source, destination;
    for (int i = 0; i < edge_count; i++) {
        iss >> source >> destination;

        // Assign unique IDs if not yet assigned
        if (graph.urls().find(destination) == graph.urls().end()) {
            graph.assign_id(destination);
        }
        if (graph.urls().find(source) == graph.urls().end()) {
            graph.assign_id(source);
        }

        graph.increment_degree(source);
        graph.add(graph.urls()[source], graph.urls()[destination]);
    }

    graph.calculate_rank(iteration_count);
}

// Helper function to capture the output of display_rank
string getDisplayOutput(AdjacencyList &graph) {
    ostringstream oss;
    auto *originalCoutBuffer = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());
    graph.display_rank();
    cout.rdbuf(originalCoutBuffer);
    return oss.str();
}

// Test Case 1
TEST_CASE("PageRank Test 1", "[PageRank]") {
    string input = R"(71 13
zoom.us aman.com
mozilla.org instagram.com
wikipedia.org disney.com
chase.com stackoverflow.com
aman.com twitter.com
google.com stackoverflow.com
twitter.com ufl.edu
wikipedia.org google.com
chase.com aman.com
roblox.com mozilla.org
reactjs.org pcbuildinguf.com
instagram.com getbootstrap.com
getbootstrap.com twitter.com
google.com twitter.com
stackoverflow.com disney.com
disney.com instagram.com
stackoverflow.com twitter.com
aman.com pcbuildinguf.com
mozilla.org pcbuildinguf.com
stackoverflow.com roblox.com
reactjs.org google.com
disney.com aman.com
stackoverflow.com chase.com
facebook.com wikipedia.org
chase.com twitter.com
disney.com chase.com
openai.com pcbuildinguf.com
python.org openai.com
wikipedia.org mozilla.org
twitter.com reactjs.org
openai.com getbootstrap.com
python.org disney.com
facebook.com disney.com
python.org instagram.com
twitter.com facebook.com
roblox.com aman.com
stackoverflow.com zoom.us
google.com pcbuildinguf.com
chase.com pcbuildinguf.com
reactjs.org facebook.com
mozilla.org disney.com
instagram.com google.com
pcbuildinguf.com openai.com
stackoverflow.com instagram.com
twitter.com stackoverflow.com
instagram.com stackoverflow.com
mozilla.org stackoverflow.com
chase.com openai.com
google.com chase.com
reactjs.org chase.com
ufl.edu getbootstrap.com
stackoverflow.com wikipedia.org
chase.com wikipedia.org
chase.com reactjs.org
google.com openai.com
pcbuildinguf.com stackoverflow.com
reactjs.org twitter.com
aman.com reactjs.org
python.org wikipedia.org
ufl.edu disney.com
getbootstrap.com aman.com
stackoverflow.com openai.com
pcbuildinguf.com python.org
ufl.edu facebook.com
wikipedia.org aman.com
python.org aman.com
roblox.com getbootstrap.com
aman.com wikipedia.org
getbootstrap.com python.org
zoom.us instagram.com
mozilla.org getbootstrap.com)";

    string expectedOutput = R"(aman.com 0.09
chase.com 0.05
disney.com 0.07
facebook.com 0.04
getbootstrap.com 0.07
google.com 0.05
instagram.com 0.06
mozilla.org 0.02
openai.com 0.07
pcbuildinguf.com 0.09
python.org 0.05
reactjs.org 0.05
roblox.com 0.01
stackoverflow.com 0.09
twitter.com 0.08
ufl.edu 0.02
wikipedia.org 0.07
zoom.us 0.01
)";

    AdjacencyList graph;
    initializeGraph(graph, input);
    string actualOutput = getDisplayOutput(graph);

    REQUIRE(actualOutput == expectedOutput);
}

// Test Case 2
TEST_CASE("PageRank Test 2", "[PageRank]") {
    string input = R"(29 1
facebook.com mozilla.org
stackoverflow.com python.org
python.org github.com
mozilla.org roblox.com
apple.com roblox.com
stackoverflow.com facebook.com
google.com openai.com
openai.com instagram.com
mozilla.org google.com
aman.com roblox.com
python.org openai.com
facebook.com roblox.com
apple.com samsung.com
github.com stackoverflow.com
github.com python.org
weather.com github.com
roblox.com aman.com
samsung.com python.org
github.com instagram.com
aman.com facebook.com
samsung.com aman.com
roblox.com github.com
samsung.com mozilla.org
stackoverflow.com samsung.com
weather.com aman.com
roblox.com facebook.com
roblox.com python.org
python.org apple.com
openai.com mozilla.org)";

    string expectedOutput = R"(aman.com 0.08
apple.com 0.08
facebook.com 0.08
github.com 0.08
google.com 0.08
instagram.com 0.08
mozilla.org 0.08
openai.com 0.08
python.org 0.08
roblox.com 0.08
samsung.com 0.08
stackoverflow.com 0.08
weather.com 0.08
)";

    AdjacencyList graph;
    initializeGraph(graph, input);
    string actualOutput = getDisplayOutput(graph);

    REQUIRE(actualOutput == expectedOutput);
}

// Test Case 3
TEST_CASE("PageRank Test 3", "[PageRank]") {
    string input = R"(31 11
twitter.com weather.com
wikipedia.org roblox.com
roblox.com google.com
microsoft.com openai.com
mozilla.org facebook.com
python.org facebook.com
google.com twitter.com
microsoft.com disney.com
microsoft.com instagram.com
getbootstrap.com instagram.com
disney.com weather.com
mozilla.org pcbuildinguf.com
wikipedia.org reactjs.org
disney.com facebook.com
chase.com twitter.com
google.com mozilla.org
roblox.com weather.com
google.com roblox.com
openai.com getbootstrap.com
weather.com disney.com
ufl.edu apple.com
getbootstrap.com ufl.edu
chase.com apple.com
microsoft.com getbootstrap.com
samsung.com github.com
instagram.com reactjs.org
youtube.com roblox.com
youtube.com facebook.com
mozilla.org microsoft.com
zoom.us microsoft.com
instagram.com ufl.edu)";

    string expectedOutput = R"(apple.com 0.00
chase.com 0.00
disney.com 0.01
facebook.com 0.01
getbootstrap.com 0.00
github.com 0.00
google.com 0.00
instagram.com 0.00
microsoft.com 0.00
mozilla.org 0.00
openai.com 0.00
pcbuildinguf.com 0.00
python.org 0.00
reactjs.org 0.00
roblox.com 0.00
samsung.com 0.00
twitter.com 0.00
ufl.edu 0.00
weather.com 0.01
wikipedia.org 0.00
youtube.com 0.00
zoom.us 0.00
)";

    AdjacencyList graph;
    initializeGraph(graph, input);
    string actualOutput = getDisplayOutput(graph);

    REQUIRE(actualOutput == expectedOutput);
}
