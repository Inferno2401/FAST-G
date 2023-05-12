#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>

namespace FastG{

    namespace Graph{

        struct vertex {

            int index;

            vertex() : index(0) {};
            
            vertex(int i) : index(i) {};

            bool operator == (vertex v);
            bool operator == (int x);
            bool operator < (vertex v);
            bool operator < (int x);
            bool operator > (vertex v);
            bool operator > (int x);
            
            void print();
        };

        typedef std::pair<vertex, int> w_vertex;

        class base {

            public:
            
            base();
            base(int n);
            virtual ~base() {}

            void add_vertex(int v);
            virtual void add_edge(int u, int v);
            virtual void add_edge(int u, int v, int weight);

            int V();
            virtual int E();

            void print();

            std::vector<std::vector<w_vertex>> adjList;
        };

        class undir : public base {
            
            using base::base;
            //This inherits all base constructors
            //If it doesn't work, your compiler prolly doesn't support C++11 standard
            public:

            void add_edge(int u, int v);
            void add_edge(int u, int v, int weight);
            int E();
            int deg(int i);
            int deg(vertex v);

        };

        class dir : public base {
            
            using base::base;

            public:

            void add_edge(int u, int v);
            void add_edge(int u, int v, int weight);
            int E();
            int in_deg(int i);
            int in_deg(vertex v);
            int out_deg(int i);
            int out_deg(vertex v);
        };
    }
}

#endif