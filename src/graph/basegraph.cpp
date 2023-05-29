#include "graph.hpp"

namespace FastG{

    namespace Graph{

        bool vertex::operator == (vertex v) {
            return this->index == v.index;
        }

        bool vertex::operator == (int x) {
            return this->index == x;
        }
        
        bool vertex::operator < (vertex v) {
            return this->index < v.index;
        }

        bool vertex::operator < (int x) {
            return this->index < x;
        }

        bool vertex::operator > (vertex v) {
            return this->index > v.index;
        }

        bool vertex::operator > (int x) {
            return this->index > x;
        }
        
        void vertex::print() {
            std::cout << index << std::endl;
        }

        base::base() {
            add_vertex(1);
        }

        base::base(int n) {
            add_vertex(n);
        }

        void base::add_vertex(int n) {
            std::vector<w_vertex>* initial = new std::vector<w_vertex>;
            for(int i = 0; i < n; i++) {
                adjList.push_back(*initial);
            }
            delete initial;
        }

        int base::V() {
            return adjList.size();
        }

        void base::print() {
            for(int i = 0; i < adjList.size(); i++) {
                std::cout << "Vertex " << i + 1 << ':' << std::endl;
                if(adjList[i].size() == 0) {
                    std::cout << "  Nothing" << std::endl;
                }
                else for(int j = 0; j < adjList[i].size(); j++) {
                    std::cout << "  ";
                    adjList[i][j].first.print();
                }
            }
        }
    }
}