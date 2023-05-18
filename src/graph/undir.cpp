#include "graph.hpp"

namespace FastG{

    namespace Graph{
        
        void undir::add_edge(int u, int v) {
            return add_edge(u, v, 1);
        }
        
        void undir::add_edge(int u, int v, int w) {
            try {
                if(u < 1 || v < 1) throw 2;
                if(u > adjList.size() || v > adjList.size()) throw 1;
                if(u == v) throw 0;
                vertex* v_u = new vertex(u);
                vertex* v_v = new vertex(v);
                int d_u = deg(u), d_v = deg(v);
                int p_v = d_u, p_u = d_v;
                for(int i = 0; i < d_u; i++) {
                    if(*v_v == adjList[u - 1][i].first) throw 3;
                    if(*v_v < adjList[u - 1][i].first) {
                        p_v = i;
                        break;
                    }
                }
                for(int j = 0; j < d_v; j++) {
                    if(*v_u < adjList[v - 1][j].first) {
                        p_u = j;
                        break;
                    }
                }
                std::vector<w_vertex>::iterator insert_here_v = std::next(adjList[u - 1].begin(), p_v);
                std::vector<w_vertex>::iterator insert_here_u = std::next(adjList[v - 1].begin(), p_u);
                adjList[u - 1].insert(insert_here_v, std::make_pair(*v_v, w));
                adjList[v - 1].insert(insert_here_u, std::make_pair(*v_u, w));
                delete v_v;
                delete v_u;
                return;
            }
            catch(int exception) {
                if(exception == 3) {
                    std::cout << "ERROR: Can't have repeated edges in simple graph" << std::endl;
                }
                if(exception == 2) {
                    std::cout << "ERROR: Index too small" << std::endl;
                    return;
                }
                if(exception == 1) {
                    std::cout << "ERROR: insufficient vertices" << std::endl;
                    return;
                }
                else {
                    std::cout << "ERROR: No loops allowed; only simple graphs" << std::endl;
                    return;
                }
            }
        }

        void undir::add_edge(vertex& u, vertex& v) {
            return add_edge(u, v, 1);
        }

        void undir::add_edge(vertex& u, vertex& v, int w) {
            return add_edge(u.index, v.index, w);
        }

        int undir::deg(int i) {
            try {
                if(i > V()) throw 1;
                if(i < 1) throw 0;
                return adjList[i - 1].size();
            }
            catch(int too_much_i) {
                if(too_much_i) {
                    std::cout << "ERROR: vertex doesn't exist" << std::endl;
                    return -1;
                }
                std::cout << "ERROR: Index too small" << std::endl;
                return -1;
            }
        }

        int undir::deg(vertex v) {
            return deg(v.index);
        }

        int undir::E() {
            int E = 0, V = this->V();
            try {
                for(int i = 0; i < V; i++) {
                    E += adjList[i].size();
                }
                if(E % 2 == 1) throw E;
                return E/2;
            }
            catch(int odd_edges) {
                std::cout << "ERROR: Incorrect graph structure" << std::endl;
                return odd_edges;
            }
        }

    }
}