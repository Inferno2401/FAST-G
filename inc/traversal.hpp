#include "graph.hpp"

namespace FastG {

    //DEPTH FIRST SEARCH
    
    //These are supposed to create trees 
    Graph::undir DFSTree(Graph::undir& G, Graph::vertex& n);
    Graph::dir DFSTree(Graph::dir& G, Graph::vertex& n);

    //These just return the order of traversing vertices
    std::vector<Graph::vertex> DFSorder(Graph::undir& G, Graph::vertex& n);
    std::vector<Graph::vertex> DFSorder(Graph::dir& G, Graph::vertex& n);

    //BREADTH FIRST SEARCH

    //Graph::undir BFSTree(Graph::undir& G, Graph::vertex& n);
    //Graph::dir BFSTree(Graph::dir& G, Graph::vertex& n);

    std::vector<Graph::vertex> BFSorder(Graph::undir& G, Graph::vertex& n);
    std::vector<Graph::vertex> BFSorder(Graph::dir& G, Graph::vertex& n);

}