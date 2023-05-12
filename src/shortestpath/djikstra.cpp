#include "shortestpath.hpp"
#include <queue>

namespace FastG {
    
    //Initial implementation - vector<int>. key = vertex index - 1, value = shortest path
    //I then decided this is stupid
    std::vector<Graph::w_vertex> Djikstra(Graph::undir& G, Graph::vertex& v) {

        int inf = 0x3f3f3f3f, V = G.V();
        std::vector<int> distance(V, inf);
        std::vector<Graph::w_vertex> Djikstra;
        distance[v.index - 1] = 0;

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>>
                            processor;

        processor.push(std::make_pair(0, v.index));

        while(!processor.empty()) {

            int u_index = processor.top().second, d = G.deg(u_index);
            processor.pop();

            for(int i = 0; i < d; i++) {
                
                Graph::vertex s = G.adjList[u_index - 1][i].first;
                int w = G.adjList[u_index - 1][i].second;
                
                if(distance[u_index - 1] + w < distance[s.index - 1]) {
                    distance[s.index - 1] = distance[u_index - 1] + w;
                    processor.push(std::make_pair(distance[s.index - 1], s.index));
                }
            }
        }

        for(int i = 0; i < V; i++) {
            Djikstra.push_back(std::make_pair(Graph::vertex(i + 1), distance[i]));
        }

        return Djikstra;
    }
    //TODO: catch all exceptions

    std::vector<Graph::w_vertex> Djikstra(Graph::dir& G, Graph::vertex& v) {

        int inf = 0x3f3f3f3f, V = G.V();
        std::vector<int> distance(V, inf);
        std::vector<Graph::w_vertex> Djikstra;
        distance[v.index - 1] = 0;

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>>
                            processor;

        processor.push(std::make_pair(0, v.index));

        while(!processor.empty()) {

            int u_index = processor.top().second, d = G.out_deg(u_index);
            processor.pop();

            for(int i = 0; i < d; i++) {
                
                Graph::vertex s = G.adjList[u_index - 1][i].first;
                int w = G.adjList[u_index - 1][i].second;
                
                if(distance[u_index - 1] + w < distance[s.index - 1]) {
                    distance[s.index - 1] = distance[u_index - 1] + w;
                    processor.push(std::make_pair(distance[s.index - 1], s.index));
                }
            }
        }

        for(int i = 0; i < V; i++) {
            Djikstra.push_back(std::make_pair(Graph::vertex(i + 1), distance[i]));
        }

        return Djikstra;
    }
}