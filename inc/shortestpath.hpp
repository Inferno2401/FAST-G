#include "graph.hpp"

namespace FastG {

    //DJIKSTRA

    //This should give a shortest-path tree
    //Starting to think I should just implement a separate Tree data structure or something. . .
    //Will this even be useful in normal graph form? No clue
    //  Graph::undir DjikstraTree(Graph::undir& G, int& n);
    //  Graph::dir DjikstraTree(Graph::dir& G, int& n);

    //This utilizes the w_vertex type to return a bunch of pairs, containing a vertex with the length of its shortest path
    std::vector<Graph::w_vertex> Djikstra(Graph::undir& G, Graph::vertex& v);
    std::vector<Graph::w_vertex> Djikstra(Graph::dir& G, Graph::vertex& v);

    //TODO: Bellman-Ford, Floyd-Warshall
}