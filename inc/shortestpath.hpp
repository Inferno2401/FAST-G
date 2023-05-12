#include "graph.hpp"

namespace FastG {

    //DJIKSTRA

    //this should give a shortest-path tree
    //Graph::undir DjikstraTree(Graph::undir& G, int& n);
    //Graph::dir DjikstraTree(Graph::dir& G, int& n);

    std::vector<Graph::w_vertex> Djikstra(Graph::undir& G, Graph::vertex& v);
    std::vector<Graph::w_vertex> Djikstra(Graph::dir& G, Graph::vertex& v);

    //TODO: Bellman-Ford, Floyd-Warshall

}