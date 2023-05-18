#include "traversal.hpp"

namespace FastG {

    //anonymous namespace
    namespace {

        void DFS(Graph::undir& G, Graph::vertex& v, std::vector<bool>& visited, std::vector<Graph::vertex>& DFSorder) {

            int d = G.deg(v);
            visited[v.index - 1] = true;
            DFSorder.push_back(v);

            for(int i = 0; i < d; i++) {

                if(!visited[G.adjList[v.index - 1][i].first.index]) {

                    DFS(G, G.adjList[v.index - 1][i].first, visited, DFSorder);
                    
                }
            }
        }

        void DFS(Graph::dir& G, Graph::vertex& v, std::vector<bool>& visited, std::vector<Graph::vertex>& DFSorder) {

            int d = G.out_deg(v);
            visited[v.index - 1] = true;
            DFSorder.push_back(v);

            for(int i = 0; i < d; i++) {

                if(!visited[G.adjList[v.index - 1][i].first.index]) {

                    DFS(G, G.adjList[v.index - 1][i].first, visited, DFSorder);

                }
            }
        }

        void DFS(Graph::undir& G, Graph::vertex& v, std::vector<bool>& visited, Graph::undir& T) {
            
            int d = G.deg(v);
            visited[v.index - 1] = true;

            for(int i = 0; i < d; i++) {

                Graph::vertex w = G.adjList[v.index - 1][i].first;
                int weight = G.adjList[v.index - 1][i].second;

                if(!visited[w.index - 1]) {

                    T.add_edge(v, w, weight);
                    DFS(G, w, visited, T);

                }
            }
        }

        void DFS(Graph::dir& G, Graph::vertex& v, std::vector<bool>& visited, Graph::dir& T) {
            
            int d = G.out_deg(v);
            visited[v.index - 1] = true;

            for(int i = 0; i < d; i++) {

                Graph::vertex w = G.adjList[v.index - 1][i].first;
                int weight = G.adjList[v.index - 1][i].second;

                if(!visited[w.index - 1]) {

                    T.add_edge(v, w, weight);
                    DFS(G, w, visited, T);

                }
            }
        }
    }
    
    std::vector<Graph::vertex> DFSorder(Graph::undir& G, Graph::vertex& v) {
        
        std::vector<bool> visited(G.V(), false);
        std::vector<Graph::vertex> DFSorder;  

        DFS(G, v, visited, DFSorder);

        return DFSorder;
    }

    std::vector<Graph::vertex> DFSorder(Graph::dir& G, Graph::vertex& v) {
        
        std::vector<bool> visited(G.V(), false);
        std::vector<Graph::vertex> DFSorder;  

        DFS(G, v, visited, DFSorder);

        return DFSorder;
    }

    Graph::undir DFSTree(Graph::undir& G, Graph::vertex& v) {
        
        int V = G.V();
        std::vector<bool> visited(V, false);
        Graph::undir DFSTree(V);

        DFS(G, v, visited, DFSTree);

        return DFSTree;
    }

    Graph::dir DFSTree(Graph::dir& G, Graph::vertex& v) {
        
        int V = G.V();
        std::vector<bool> visited(V, false);
        Graph::dir DFSTree(V);

        DFS(G, v, visited, DFSTree);

        return DFSTree;
    }

}