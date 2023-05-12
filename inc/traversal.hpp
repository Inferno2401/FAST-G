#include "graph.hpp"

namespace FastG {

    //DEPTH FIRST SEARCH
    
    //These are supposed to create trees 
    //Graph::undir DFS(Graph::undir& G, int& n);
    //Graph::dir DFS(Graph::dir& G, int& n);

    std::vector<Graph::vertex> DFSorder(Graph::undir& G, int& n);
    std::vector<Graph::vertex> DFSorder(Graph::dir& G, int& n);

    //BREADTH FIRST SEARCH

    //Graph::undir BFSTree(Graph::undir& G, int& n);
    //Graph::dir BFSTree(Graph::dir& G, int& n);

    std::vector<Graph::vertex> BFSorder(Graph::undir& G, int& n);
    std::vector<Graph::vertex> BFSorder(Graph::dir& G, int& n);

}