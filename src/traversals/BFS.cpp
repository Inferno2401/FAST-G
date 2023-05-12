#include "traversal.hpp"
#include <queue>
namespace FastG{

    namespace {

        void BFS(Graph::undir& G, Graph::vertex& v, std::vector<bool> visited) {



        }
    }

    std::vector<Graph::vertex> BFSorder(Graph::undir& G, Graph::vertex& v) {

        std::vector<bool> visited(G.V(), false);
        std::queue<Graph::vertex> processor;
        std::vector<Graph::vertex> BFS;

        visited[v.index - 1] = true;
        processor.push(v);

        while(!processor.empty()) {

            Graph::vertex u = processor.front();
            int d = G.deg(u);
            BFS.push_back(u);
            processor.pop();

            for(int i = 0; i < d; i++) {
                Graph::vertex s = G.adjList[u.index - 1][i].first;
                if(!visited[s.index - 1]) {
                    visited[s.index - 1] = true;
                    processor.push(s);
                }
            }
        }

        return BFS;

    }

    std::vector<Graph::vertex> BFSorder(Graph::dir& G, Graph::vertex& v) {

        std::vector<bool> visited(G.V(), false);
        std::queue<Graph::vertex> processor;
        std::vector<Graph::vertex> BFS;

        visited[v.index - 1] = true;
        processor.push(v);

        while(!processor.empty()) {

            Graph::vertex u = processor.front();
            int d = G.out_deg(u);
            BFS.push_back(u);
            processor.pop();

            for(int i = 0; i < d; i++) {
                Graph::vertex s = G.adjList[u.index - 1][i].first;
                if(!visited[s.index - 1]) {
                    visited[s.index - 1] = true;
                    processor.push(s);
                }
            }
        }

        return BFS;
        
    }

}