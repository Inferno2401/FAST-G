#include <iostream>
#include <vector>
#include <graph.hpp>
using namespace std;

int main(){
    // test code
    Graph G;
    // G.inputGraph();
    // G.addNode(6);
    // G.addNode(2);
    // G.addNode(3);
    // G.addNode(15);
    // G.addNode(48);    
    // G.addNode(83);
    // G.addNode(71);
    // G.addNode(5);
    // G.addNode(64);
    // G.addNode(16);
    // G.addNode(8);
    // G.addNode(23);
    // G.addWeightedEdge(6,2,4);
    // G.addWeightedEdge(6,15,5);
    // G.addWeightedEdge(2,3,9);
    // G.addWeightedEdge(3,15,1);
    // G.addWeightedEdge(3,48,3);
    // G.addWeightedEdge(15,48,2);
    // G.addWeightedEdge(48,83,6);
    // G.addWeightedEdge(48,71,1);
    // G.addWeightedEdge(71,16,6);
    // G.addWeightedEdge(16,8,9);
    // G.addWeightedEdge(16,23,10);
    // G.addWeightedEdge(71,5,2);
    // G.addWeightedEdge(5,64,7);
    // G.addWeightedEdge(64,3,6);
    // G.addNode(1);
    // G.addNode(2);
    // G.addNode(3);
    // G.addNode(4);
    // G.addWeightedEdge(1,2,7);
    // G.addWeightedEdge(2,3,5);
    // G.addWeightedEdge(1,3,3);
    // G.addWeightedEdge(1,4,7);
    // G.addNode(0);
    // G.addNode(1);
    // G.addNode(2);
    // G.addNode(3);
    // G.addNode(4);
    // G.addNode(5);
    // G.addNode(6);
    // G.addNode(7);
    // G.addNode(8);
    // G.addWeightedEdge(0,1,4);
    // G.addWeightedEdge(1,2,8);
    // G.addWeightedEdge(2,3,7);
    // G.addWeightedEdge(3,4,9);
    // G.addWeightedEdge(4,5,10);
    // G.addWeightedEdge(5,6,2);
    // G.addWeightedEdge(6,7,1);
    // G.addWeightedEdge(7,0,8);
    // G.addWeightedEdge(1,7,11);
    // G.addWeightedEdge(2,8,2);
    // G.addWeightedEdge(7,8,7);
    // G.addWeightedEdge(2,5,4);
    // G.addWeightedEdge(3,5,14);
    // G.addWeightedEdge(6,8,6);
    // G.addNode(1);
    // G.addNode(2);
    // G.addNode(3);
    // G.addNode(4);
    // G.addNode(5);
    // G.addNode(6);
    // G.addDirectedWeightedEdge(1,2,15);
    // G.addDirectedWeightedEdge(1,4,12);
    // G.addDirectedWeightedEdge(2,4,10);
    // G.addDirectedWeightedEdge(2,3,12);
    // G.addDirectedWeightedEdge(3,6,25);
    // G.addDirectedWeightedEdge(2,5,1);
    // G.addDirectedWeightedEdge(4,5,14);
    // G.addDirectedWeightedEdge(5,3,10);
    // G.addDirectedWeightedEdge(5,6,4);
    G.addNode(1);
    G.addNode(2);
    G.addNode(3);
    G.addNode(4);
    G.addNode(5);
    G.addNode(6);
    G.addNode(7);
    G.addDirectedWeightedEdge(1,2,7);
    G.addDirectedWeightedEdge(1,3,10);
    G.addDirectedWeightedEdge(2,5,5);
    G.addDirectedWeightedEdge(2,3,1);
    G.addDirectedWeightedEdge(2,4,3);
    G.addDirectedWeightedEdge(3,4,2);
    G.addDirectedWeightedEdge(4,5,3);
    G.addDirectedWeightedEdge(4,6,2);
    G.addDirectedWeightedEdge(3,6,7);
    G.addDirectedWeightedEdge(5,6,2);
    G.addDirectedWeightedEdge(5,7,10);
    G.addDirectedWeightedEdge(6,7,4);
    G.printGraph();
    // cout << "---------------------------------------" << endl;
    // cout << "BFS: " << endl;
    // Graph B = G.BFS(71);
    // B.printGraph();
    // cout << "---------------------------------------" << endl;
    // cout << "DFS: " << endl;
    // Graph D = G.DFS(71);
    // D.printGraph();
    // cout << "---------------------------------------" << endl;
    // cout << "Dijkstra: " << endl;
    // vector<int> dist = G.Dijkstra(71);
    // for(int i = 0; i < dist.size(); i++){
    //     cout << "Distance of " << G.nodes[i]->label << " from 71 is " << dist[i] << endl; 
    // }
    // cout << "---------------------------------------" << endl;
    // cout << "APSP: " << endl;
    // vector<vector<int>> Distance_APSP = G.APSP();
    // for(int i = 0; i < G.num_nodes; i++){
    //     cout << "Label " << G.nodes[i]->label << " - "; 
    //     for(int j = 0; j < G.num_nodes; j++){
    //         cout << Distance_APSP[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "---------------------------------------" << endl;
    // // cout << "Selection Sort: " << endl;
    // // vector<int> array;
    // // int k;
    // // for(int i = 0; i < 10; i++){
    // //     cin >> k;
    // //     array.push_back(k);
    // // }
    // // vector<int> sorted = selectionSort(array);
    // // for(int i = 0; i < sorted.size(); i++){
    // //     cout << sorted[i] << " ";
    // // }
    // // cout << endl;
    // // cout << "---------------------------------------" << endl;
    // cout << "Kruskal: " << endl;
    // Graph K = G.Kruskal();
    // K.printGraph();
    cout << "Network Flow: ";
    cout << G.FordFulkerson(1,7);
}
