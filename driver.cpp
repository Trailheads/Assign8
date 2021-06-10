#include "multi_graph.h"
#include <iostream>

int main() {
    //Create an empty graph
    multi_graph graph;

    //Local bar names in Eugene, OR
    const int NUM_BARS = 10;
    const std::string EUGENE_BARS [NUM_BARS] = {"Jackalope Lounge", "Jameson's Bar", "BarTini Bistro", "Starlight Lounge",
                            "Max's Tavern", "The Jazz Station", "Lucky's Club", "Drake Bar", "Party Bar",
                            "The Horsehead Bar"};


    //Add vertices to graph
    for(int i = 0; i < NUM_BARS; ++i) {
        graph.add_vertex(EUGENE_BARS[i]);
    }

    /*The distance in miles from the 1st bar to the following two bars that come after in the array named "eugene_bars".
    Process repeats until the last bar is connected to the first two bars in the array. */
    const int NUM_EDGES = 20;
    const float BAR_DISTANCES [NUM_EDGES] = {.4, .6, .4, .04, .4, .5, .9, .08, .8, .8, .05, .05, .05, .09, .04, .05, .07, .4, .4, .01};


    //Add edges to vertices
    int increment = 0;
    for(int i = 0; i < NUM_BARS; ++i) {
        for(int j = (i+1); j < (i+3); ++j) {
            if(i > (NUM_BARS - 1)) {
                j = i - NUM_BARS;
            }
            graph.add_edge(EUGENE_BARS[i], EUGENE_BARS[j], BAR_DISTANCES[increment]);
            ++increment;
        }
    }


    //Check if both vertices and edges are put into the adjacency matrix correctly
    graph.print_matrix();

    //Find the minimum spanning tree
    graph.minimum_spanning_tree();

    //Find shortest path between two vertices
    float shortest_path;
    shortest_path = graph.shortest_path(EUGENE_BARS[0], EUGENE_BARS[8]);
    std::cout << "\nFrom '" << EUGENE_BARS[0] << "' to '" << EUGENE_BARS[8] << "', the shortest distance is: "
              << shortest_path << std::endl;
}