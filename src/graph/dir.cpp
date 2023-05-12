#include "graph.hpp"

namespace FastG{

    namespace Graph {

        void dir::add_edge(int u, int v) {
            return dir::add_edge(u, v, 1);
        }

        void dir::add_edge(int u, int v, int w) {
            try {
                if(u < 1 || v < 1) throw 2;
                if(u > adjList.size() || v > adjList.size()) throw 1;
                if(u == v) throw 0;
                vertex* v_v = new vertex(v);
                int d_u = out_deg(u), p_v = d_u;
                for(int i = 0; i < d_u; i++) {
                    if(*v_v == adjList[u - 1][i].first) throw 3;
                    if(*v_v < adjList[u - 1][i].first) {
                        p_v = i;
                        break;
                    }
                }
                std::vector<w_vertex>::iterator insert_here_v = std::next(adjList[u - 1].begin(), p_v);
                adjList[u - 1].insert(insert_here_v, std::make_pair(*v_v, w));
                delete v_v;                
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
                    std::cout << "ERROR: vertices don't exist" << std::endl;
                    return;
                }
                else {
                    std::cout << "ERROR: No loops allowed; only simple graphs" << std::endl;
                    return;
                }
            }
        }

        int dir::E() {
            int E = 0, V = this->V();
            for(int i = 0; i < V; i++) {
                E += adjList[i].size();
            }
            return E;
        }

        int dir::in_deg(int i) {
            try {
                if(i > V()) throw 1;
                if(i < 1) throw 0;
                int d = 0, V = this->V(), end = 0;
                for(int j = 0; j < V; j++) {
                    end = out_deg(j);
                    for(int k = 0; k < end; k++) {
                        if(adjList[j][k].first > i) break;
                        if(adjList[j][k].first == i) {
                            d++;
                            break;
                        }
                    }
                }
                return d;
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

        int dir::in_deg(vertex v) {
            return in_deg(v.index);
        }
        
        int dir::out_deg(int i) {
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

        int dir::out_deg(vertex v) {
            return out_deg(v.index);
        }
    }
    
} 
