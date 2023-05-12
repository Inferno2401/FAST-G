#include "traversal.hpp"

namespace FastG {

    //anonymous namespace
    namespace {

        std::vector<Graph::vertex> DFS(Graph::undir& G, Graph::vertex& v, std::vector<bool>& visited) {

            std::vector<Graph::vertex> DFSorder;
            int d = G.deg(v);

            visited[v.index - 1] = true;
            DFSorder.push_back(v);

            for(int i = 0; i < d; i++) {
                if(!visited[G.adjList[v.index = 1][i].first.index]) {
                    DFS(G, G.adjList[v.index = 1][i].first, visited);
                }
            }
            return DFSorder;
        }

        std::vector<Graph::vertex> DFS(Graph::dir& G, Graph::vertex& v, std::vector<bool>& visited) {

            std::vector<Graph::vertex> DFSorder;
            int d = G.out_deg(v);

            visited[v.index - 1] = true;
            DFSorder.push_back(v);

            for(int i = 0; i < d; i++) {
                if(!visited[G.adjList[v.index = 1][i].first.index]) {
                    DFS(G, G.adjList[v.index = 1][i].first, visited);
                }
            }
            return DFSorder;
        }
    }
    
    std::vector<Graph::vertex> DFSorder(Graph::undir& G, Graph::vertex& v) {
        
        std::vector<bool> visited(G.V(), false);   
        return DFS(G, v, visited);
    }

    std::vector<Graph::vertex> DFSorder(Graph::dir& G, Graph::vertex& v) {
        
        std::vector<bool> visited(G.V(), false);
        return DFS(G, v, visited);
    }

}