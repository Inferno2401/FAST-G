#include <iostream>
#include <vector>
#include <graph.hpp>
using namespace std;

int main(){
    // test code
    Graph G;
    // G.inputGraph();
    G.addNode(6);
    G.addNode(2);
    G.addNode(3);
    G.addNode(15);
    G.addNode(48);    
    G.addNode(83);
    G.addNode(71);
    G.addNode(5);
    G.addNode(64);
    G.addNode(16);
    G.addNode(8);
    G.addNode(23);
    // G.addEdge(6,2);
    // G.addEdge(6,15);
    // G.addEdge(2,3);
    // G.addEdge(3,15);
    // G.addEdge(3,48);
    // G.addEdge(15,48);
    // G.addEdge(48,83);
    // G.addEdge(48,71);
    // G.addEdge(71,16);
    // G.addEdge(16,8);
    // G.addEdge(16,23);
    // G.addEdge(71,5);
    // G.addEdge(5,64);
    // G.addEdge(64,3);
    G.addWeightedEdge(6,2,4);
    G.addWeightedEdge(6,15,5);
    G.addWeightedEdge(2,3,9);
    G.addWeightedEdge(3,15,1);
    G.addWeightedEdge(3,48,3);
    G.addWeightedEdge(15,48,2);
    G.addWeightedEdge(48,83,6);
    G.addWeightedEdge(48,71,1);
    G.addWeightedEdge(71,16,6);
    G.addWeightedEdge(16,8,9);
    G.addWeightedEdge(16,23,10);
    G.addWeightedEdge(71,5,2);
    G.addWeightedEdge(5,64,7);
    G.addWeightedEdge(64,3,6);
    // G.addNode(1);
    // G.addNode(2);
    // G.addNode(3);
    // G.addNode(4);
    // G.addNode(5);
    // G.addNode(6);
    // G.addNode(7);
    // G.addNode(8);
    // G.addEdge(1,2);
    // G.addEdge(1,3);
    // G.addEdge(2,3);
    // G.addEdge(3,5);
    // G.addEdge(5,4);
    // G.addEdge(5,6);
    // G.addEdge(2,4);
    // G.addEdge(2,5);
    // G.addEdge(3,7);
    // G.addEdge(3,8);
    // G.addEdge(7,8);
    G.printGraph();
    Graph B = G.BFS(71);
    B.printGraph();
}