#include "multi_graph.h"
#include <iostream>


multi_graph::multi_graph() {
    num_vertices = 0;
}


multi_graph::~multi_graph() {

}


/*Adds one vertex into the graph by increasing the size
  of the adjacency matrix. Big O(n^2) since the resize()
  for vectors is linear, and this functions requires that
  function to be called another "n" times. */
void multi_graph::add_vertex(std::string name) {
    num_vertices++;

    adjacency_matrix.resize(num_vertices);
    for(int i = 0; i < num_vertices; ++i) {
        adjacency_matrix[i].resize(num_vertices);
    }

    bar_names.push_back(name);
}


/*Add an edge weight, distances in miles, between two bars.
  Big O(n) since there is one iteration starting at one specific row
  and the time depends on the size of the array. */
void multi_graph::add_edge(const std::string source, const std::string destination, const float distance) {
    int source_index, destination_index = 0;

    //Find the indices for the source and destination bars.
    for(int i = 0; i < num_vertices; ++i) {
        if(bar_names[i] == source) {
            source_index = i;
        }
        else if(bar_names[i] == destination) {
            destination_index = i;
        }
    }

    //Using both indicies, insert the distance between those two bars in the matrix.
    adjacency_matrix[source_index][destination_index] = distance;
    //std::cout << adjacency_matrix[source_index][destination_index] << std::endl;
}


/*Find the graph's minimum spanning tree via Dijistrak's algorithm.
  Big O(n^2) since the time depends on two linear for loops starting
  at line 64. */
void multi_graph::minimum_spanning_tree() {
    if(num_vertices == 0) {
        return;
    }

    //If map isn't empty, clear it.
    if(shortest_paths.empty() != true) {
        shortest_paths.clear();
    }

    float edge_min = INT_MAX;
    float total_min = 0;

    //Start at the first vertex placed in the graph.
    //Iterate through each unvisited vertex's edges.
    for(int row = 0; row < num_vertices; ++row) {
        for(int col = 0; col < num_vertices; ++col) {
            //Update minimum path if an edge's weight is less than the previously saved value.
            if(adjacency_matrix[row][col] > 0 && adjacency_matrix[row][col] < edge_min) {
                edge_min = adjacency_matrix[row][col];
            }
        }
    //Before the next iteration, update the total path length.
    total_min += edge_min;
    //Also, insert both the source name and updated shortest edge weight into map.
    shortest_paths.insert(std::pair<std::string, float>(bar_names[row], edge_min));
    }
    
    print_min_span_tree(total_min);
}


/*Iterate through the map containing the shortest path lengths,
  and print each bar's name with its distance. Then, print the
  summation of those distances. */ 
void multi_graph::print_min_span_tree(const float total_min) {
    std::cout << "\n";
    std::map<std::string, float>::iterator it;

    for(it = shortest_paths.begin(); it != shortest_paths.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << "\nThe minimum spanning tree length is: " << total_min << std::endl;
}


/*Finds the shortest distance between two bars. 
  Big O(n) since the time it takes to execute the for the loop on line 113,
  is dependent on the the size of one row in the adjacency matrix. */
float multi_graph::shortest_path(std::string source, std::string destination) {
    //The graph is empty, no vertices are present.
    if(num_vertices == 0) return -1;

    //Base case
    if(source == destination) return 0;

    /*Retrieve the index of the current "source" bar's name.
      This index correlates to the row positions of the adjacency matrix.*/
    int current_bar_index = get_bar_position(source);
    int nearest_bar_index = 0;

    //Until the mininimum edge weight is identified, it will be set to the highest float value
    float FLOAT_MAX = 3.402823466E+38;
    float min_edge_distance = FLOAT_MAX;

    /*Iterate through the columns at the row index we retrieved earlier.
      Update the minimum distance found between the two bars and save
      its index so it may be used to locate its name. */
    for(int col = 0; col < num_vertices; ++col) {

        if(adjacency_matrix[current_bar_index][col] < min_edge_distance &&
           adjacency_matrix[current_bar_index][col] > 0) {

            min_edge_distance = adjacency_matrix[current_bar_index][col];
            nearest_bar_index = col; 
        }
    }

    /*Retrieve the name of the bar that had the shortest distance between
      it and the starting bar. */
    std::string new_source;
    new_source = get_bar_name(nearest_bar_index);

    //Retrieve that bars shortest distance determined by the minimum spanning tree function
    float min_path_length = 0;
    min_path_length = get_path_length(new_source);
    std::cout << "min_path_length = " << min_path_length << std::endl;

    //Summate all the shortest distances until the base case is reached.
    return min_path_length + shortest_path(new_source, destination);
}


void multi_graph::print_matrix() {
    std::cout << "\n";

    for(int row = 0; row < num_vertices; ++row) {
        for(int col = 0; col < num_vertices; ++col) {
            std::cout << "[ " << adjacency_matrix[row][col] << " ]";
        }
        std::cout << "\n";
    }
}


void multi_graph::print_map() {

}


void multi_graph::clear() {
    adjacency_matrix.clear();
    bar_names.clear();
}


std::vector<std::string> multi_graph::get_bar_names() const {
    return  bar_names;
}


int multi_graph::get_num_vertices() const {
    return num_vertices;
}


int multi_graph::get_bar_position(const std::string bar_name) {
    int current_bar = 0;

    for(int i = 0; i < num_vertices; ++i) {
        if(bar_names[i] == bar_name) {
            current_bar = i;
        }
    }

    return current_bar;
}


std::string multi_graph::get_bar_name(const int index) const {
    return bar_names[index];
}


float multi_graph::get_path_length(const std::string bar_name) const {
    float min_path_length = 0;

    for(auto it = shortest_paths.begin(); it != shortest_paths.end(); it++) {
        //std::cout << "key: " << it->first << std::endl;
        if(it->first == bar_name) {
            min_path_length = it->second;
        }
    }

    return min_path_length;
}