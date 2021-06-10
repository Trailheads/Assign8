#ifndef MULTI_GRAPH_H
#define MULTI_GRAPH_H

//#include "vertex.h"
#include <vector>
#include <string>
#include <map>

class multi_graph {
    public:
        multi_graph();
        ~multi_graph();

        void add_vertex(std::string name);
        void add_edge(const std::string source, const std::string destination, const float weight);
        void minimum_spanning_tree();
        float shortest_path(std::string source, std::string destination);
        void print_matrix();
        void print_map();
        void clear();

        std::vector<std::string> get_bar_names() const;
        int get_num_vertices() const;
    
    private:
        std::vector<std::vector<float> > adjacency_matrix;
        std::vector<std::string> bar_names;
        std::map<std::string, float> shortest_paths;
        int num_vertices;

        void print_min_span_tree(const float total_min);
        int get_bar_position(const std::string bar_name);
        std::string get_bar_name(const int index) const; 
        float get_path_length(const std::string bar_name) const;
};

#endif