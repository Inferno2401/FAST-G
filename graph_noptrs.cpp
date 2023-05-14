#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#define INFTY 10000000
#define INFTY2 100000000
#define INFTY3 1000000000
using namespace std;

int minIndex(vector<int> arr){      // Function to determine index of minimum term of an array
    int min = INFTY3;
    int index;
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] < min){
            min = arr[i];
        }
    }
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] == min){
            index = i;
        }
    }
    return index;
}

// Graph Class
class Graph{

public:
    // member variables
    int num_nodes;      // Number of nodes in the graph
    // Node struct
    struct Node{
        int index;      // Index of the node in the nodes vector
        int label;      // Label of the node the user decides            
        vector<int> AdjList; // Each node is associated with a vector containing labels of nodes that are adjacent to it
        pair<vector<int>,vector<int>> AdjWeight;
        int degree;     // Degree of the node, may not be necessary as a variable, but I have implemented it
    };
    vector<Node> nodes; // Vector containing the nodes of the graph

    // member functions
    Graph();    // constructor
    void inputGraph();   // Function to take the entire graph as an input
    void printGraph();   // Function to print the graph as an adjacency list
    void addNode(int);    // Function to add a node to a graph, with label as parameter
    void addEdge(int, int);     // Function to add an edge with two labels as parameters
    void addWeightedEdge(int, int, int);    // Function to add a weighted edge with two labels and weight as parameters
    bool edgeExists(int, int);      // Function to check if an edge exists between two labels
    int returnWeight(int, int);     // Function to return the weight of the edge between two labels
    int returnIndex(int);   // Function to return the index of a node with the label as parameter
    Graph BFS(int);     // BFS, label of source node is taken as input
    Graph DFS(int);     // DFS, label of source node is taken as input
    vector<int> Dijkstra(int);      // Dijkstra's Algorithm, label of source node is taken as input
    vector<vector<int>> APSP();     // All pairs shortest paths
};

Graph :: Graph(){   // Defining constructor
    num_nodes = 0;
}

void Graph :: inputGraph(){          // Defining input function
    int n;
    cout << "Enter the number of nodes in the graph: ";
    cin >> n;
    cout << endl;
    num_nodes = n; // Assigning n to the member variable num_nodes
    for (int i = 0; i < n; i++){
        Node node;    // node is the node that will be present in our graph
        node.index = i;
        cout << "Enter the label of the " << i+1 << " node: ";
        cin >> node.label;   // User defines the labels for the nodes and will only use them, indexes is just for the code
        cout << "Enter the degree of this node: ";
        cin >> node.degree;     // User defines the degree of the node
        nodes.push_back(node); 
    } 
    for(int i = 0; i < n; i++){
        int val;
        int j;
        cout << "Enter the adjcency list of the node with label " << nodes[i].label << endl;
        for(int k = 0; k < nodes[i].degree; k++){
            cout << "Enter the label of the adjacent node: ";
            cin >> val;
            nodes[i].AdjList.push_back(val);    // Adding label val to the adjacency list of nodes[i]
        }
    }
}

void Graph :: printGraph(){      // Defining print function
    cout << "The number of nodes in this graph are: " << num_nodes << endl;
    cout << "The adjacency list is as follows: " << endl;
    for (int i = 0; i < num_nodes; i++){
        cout << "Label of this node is: " << nodes[i].label << ". "; // Printing label of node
        cout << "The nodes adjacent to this node are: ";
        for (int j = 0; j < nodes[i].degree; j++){
            cout << nodes[i].AdjList[j] << " "; // Printing labels of adjacent nodes
        }
        cout << endl;
    }
}

void Graph :: addEdge(int label_start, int label_end){      // Defining function to add an edge, assuming the two labels already exist.
    int start_index, end_index;
    start_index = returnIndex(label_start);
    end_index = returnIndex(label_end);
    nodes[start_index].degree++;        // Increasing the degree of the nodes
    nodes[end_index].degree++;
    nodes[start_index].AdjList.push_back(label_end);     // Adding the labels to each others' adjlist
    nodes[end_index].AdjList.push_back(label_start);
}

void Graph :: addWeightedEdge(int label_start, int label_end, int weight){  // Defining function to add an edge, with weight
    int start_index, end_index;
    start_index = returnIndex(label_start);
    end_index = returnIndex(label_end);
    nodes[start_index].degree++;        // Increasing the degree of the nodes
    nodes[end_index].degree++;
    nodes[start_index].AdjList.push_back(label_end);     // Adding the labels to each others' adjlist
    nodes[end_index].AdjList.push_back(label_start);
    nodes[start_index].AdjWeight.first.push_back(label_end);    // Adding weight
    nodes[start_index].AdjWeight.second.push_back(weight);
    nodes[end_index].AdjWeight.first.push_back(label_start);
    nodes[end_index].AdjWeight.second.push_back(weight);
}

void Graph :: addNode(int val){       // Defining the add node function
    num_nodes++;    // Increasing the number of nodes
    Node node;      // Initialising a node and adding it to the nodes vector
    node.label = val;
    node.index = num_nodes - 1;
    node.degree = 0;
    nodes.push_back(node);
}

int Graph :: returnIndex(int lab){      // Defining a function that returns the index of a node with a label lab
    int index = 0;
    for(index = 0; index < num_nodes; index++){
        if( nodes[index].label == lab){
            break;      // Break out of for loop if lab is found amongst the labels, hence index is one required
        }
    }
    if(num_nodes == 0){
        return -1;
    }
    if(nodes[index].label == lab){
        return index;
    }
    else{
        return -1;
    }
}

int Graph :: returnWeight(int label1, int label2){      // Defining the function that returns the weight
    if(label1 == label2){
        return 0;
    }
    if(edgeExists(label1, label2)){
        int i;
        for(i = 0; i < nodes[returnIndex(label1)].degree; i++){
            if(label2 == nodes[returnIndex(label1)].AdjList[i]){
                break;
            }
        }
        return nodes[returnIndex(label1)].AdjWeight.second[i];
    }
    else{
        return INFTY;
    }
}

bool Graph :: edgeExists(int label1, int label2){   // Defining the function that tells if the edge exists
    bool flag = false;
    for(int i = 0; i < nodes[returnIndex(label1)].degree; i++){
        if( nodes[returnIndex(label1)].AdjList[i] == label2 ){
            flag = true;
        }
    }
    if( flag == true ){
        return 1;
    }
    else{
        return 0;
    }
}

Graph Graph :: BFS(int source_label){   // Implementing BFS, followed the exact same algorithm given in the textbook
    Graph T;
    bool Discovered[num_nodes];
    vector<vector<Node>> L;
    int i = 0;
    for(int m = 0; m < num_nodes; m++){
        Discovered[m] = false;
    }
    Discovered[returnIndex(source_label)] = true;
    L.push_back({nodes[returnIndex(source_label)]});
    T.addNode(L[0][0].label);
    while( L[i].empty() != 1 ){   
        L.push_back({});  
        for(int j = 0; j < L[i].size(); j++){
            for(int k = 0; k < L[i][j].degree; k++){
                if(Discovered[returnIndex(L[i][j].AdjList[k])] == false){
                    Discovered[returnIndex(L[i][j].AdjList[k])] = true;
                    T.addNode(nodes[returnIndex(L[i][j].AdjList[k])].label);
                    T.addEdge(nodes[returnIndex(L[i][j].label)].label, nodes[returnIndex(L[i][j].AdjList[k])].label);
                    L[i+1].push_back(nodes[returnIndex(L[i][j].AdjList[k])]);
                }
            }
        }
        i++;
    }
    return T;
}

Graph Graph :: DFS(int source_label){   // Implementing DFS, followed exact same algo as given in textbook
    Graph T;
    stack<Node> S;
    Node parent[num_nodes];
    bool Discovered[num_nodes];
    // int count[num_nodes];
    // for(int m = 0; m < num_nodes; m++){
    //     count[m] = 0;
    // }
    for(int m = 0; m < num_nodes; m++){
        Discovered[m] = false;
    }
    S.push(nodes[returnIndex(source_label)]);
    while( S.empty() != 1 ){
        Node node = S.top();
        S.pop();
        if(!(T.returnIndex(node.label)+1)){
            T.addNode(node.label);
            // cout << "Added node " << node.label << endl;
        }
        if(Discovered[returnIndex(node.label)] == false){
            Discovered[returnIndex(node.label)] = true;
            if(node.label != source_label){
                T.addEdge(node.label, parent[returnIndex(node.label)].label);
                // cout << "Added edge " << node.label << " , " << parent[returnIndex(node.label)].label << endl;
            }
            for(int i = 0; i < node.degree; i++){
                if(Discovered[returnIndex(node.AdjList[i])] == false){
                    S.push(nodes[returnIndex(node.AdjList[i])]);
                    // cout << "Pushed " << node.AdjList[i] << " into the stack" << endl;
                    parent[returnIndex(node.AdjList[i])] = node;
                    // cout << "Parent of " << node.AdjList[i] << " is " << node.label << endl;
                }
            }
        }
    }
    return T;
}

vector<int> Graph :: Dijkstra(int source_label){    // Implementing Dijkstra, will add comments if required
    vector<int> Distance;
    vector<int> DistanceCopy;
    vector<bool> visited;
    vector<bool> True;
    int index;
    for(int i = 0; i < num_nodes; i++){
        Distance.push_back(0);
    }
    for(int i = 0; i < num_nodes; i++){
        Distance[i] = returnWeight(source_label, nodes[i].label);
    }
    DistanceCopy = Distance;
    for(int i = 0; i < num_nodes; i++){
        visited.push_back(false);
    }
    for(int i = 0; i < num_nodes; i++){
        True.push_back(true);
    }
    visited[returnIndex(source_label)] = true;
    DistanceCopy[returnIndex(source_label)] = INFTY2;
    while( visited != True ){
        index = minIndex(DistanceCopy);
        DistanceCopy[index] = INFTY2;
        visited[index] = true;
        for(int i = 0; i < num_nodes; i++){
            if(Distance[i] > Distance[index] + returnWeight(nodes[index].label,nodes[i].label)){
                Distance[i] = Distance[index] + returnWeight(nodes[index].label,nodes[i].label);
                DistanceCopy[i] = Distance[index] + returnWeight(nodes[index].label,nodes[i].label);
            }
        }
    }
    return Distance;
}

vector<vector<int>> Graph :: APSP(){    // Added APSP, want to know whether doing dijkstra num_nodes times is okay or do i need to follow the dynamic programming algorithm, which i found on the net
    vector<vector<int>> Distance;
    // for(int i = 0; i < num_nodes; i++){
    //     Distance.push_back({});
    // }
    // for(int i = 0; i < num_nodes; i++){
    //     for(int j = 0; j < num_nodes; j++){
    //         Distance[i].push_back(returnWeight(nodes[i].label,nodes[j].label));
    //     }
    // }
    // for(int i = 0; i < num_nodes; i++){
    //     for(int j = 0; j < num_nodes; j++){
    //         for(int k = 0; k < num_nodes; k++){
    //             if(Distance[j][k] > returnWeight(nodes[j].label, nodes[i].label) + returnWeight(nodes[i].label, nodes[k].label)){
    //                 Distance[j][k] = returnWeight(nodes[j].label, nodes[i].label) + returnWeight(nodes[i].label, nodes[k].label);
    //             }
    //         }
    //     }
    // }
    for(int i = 0; i < num_nodes; i++){
        Distance.push_back(Dijkstra(nodes[i].label));
    }
    return Distance;
}

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
    // G.printGraph();
    Graph B = G.BFS(71);
    B.printGraph();
    Graph D = G.DFS(71);
    D.printGraph();
    vector<int> Distance_Dijkstra = G.Dijkstra(6);
    for(int i = 0; i < G.num_nodes; i++){
        cout << "Distance of " << G.nodes[i].label << " from 6 is " << Distance_Dijkstra[i] << endl;  
    }
    vector<vector<int>> Distance_APSP = G.APSP();
    for(int i = 0; i < G.num_nodes; i++){
        for(int j = 0; j < G.num_nodes; j++){
            cout << Distance_APSP[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}