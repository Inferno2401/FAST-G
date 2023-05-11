#include <iostream>
#include <vector>
using namespace std;

class Graph{

public:
    
    int num_nodes;      // Number of nodes in the graph
    struct Node{
        int index;              // Index of the node
        int label;
        vector<Node> AdjList; // Each node is associated with a vector containing nodes that are adjacent to it
        int degree;
    };
    vector<Node> nodes; // Vector containing the nodes of the graph

    Graph();
    void inputGraph();   // Function to take the entire graph as an input
    void printGraph();   // Function to print the graph
    int returnIndex(int);
    void addNode(int);    // Function to add a node to a graph
    void addNode(Node);
    void addNode(Node, int);
    void addEdge(Node, Node);
    void addEdge(int, int);
    void assignDegree();
    Graph BFS(int);
};

Graph :: Graph(){
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
        cin >> node.label;
        cout << "Enter the degree of this node: ";
        cin >> node.degree;
        nodes.push_back(node); 
    } 
    for(int i = 0; i < n; i++){
        int val;
        int j;
        cout << "Enter the adjcency list of the node with label " << nodes[i].label << endl;
        for(int k = 0; k < nodes[i].degree; k++){
            cout << "Enter the label of the adjacent node: ";
            cin >> val;
            for(j = 0; j < n; j++){
                if(val == nodes[j].label){
                    break;
                }
            }
            nodes[i].AdjList.push_back(nodes[j]);
        }
    }
}

void Graph :: printGraph(){      // Defining print function
    cout << "The number of nodes in this graph are: " << num_nodes << endl;
    cout << "The adjacency list is as follows: " << endl;
    for (int i = 0; i < num_nodes; i++){
        cout << "Label of this node is: " << nodes[i].label << ". "; // Printing index of node
        cout << "The nodes adjacent to this node are: ";
        for (int j = 0; j < nodes[i].degree; j++){
            cout << nodes[i].AdjList[j].label << " "; // Printing indices of adjacent nodes
        }
        cout << endl;
    }
}

void Graph :: addEdge(Node start, Node end){    // Defining add edge function, start is the start node of the edge and end is the end
    start.degree++;    // Increase the degree of the start node
    end.degree++;      // Increase the degree of the end node
    start.AdjList.push_back(end);   // Adding the end node to the adjacency list of start 
    end.AdjList.push_back(start);   // Adding the start node to the adjacency list of end
}

void Graph :: addEdge(int label_start, int label_end){
    int start_index, end_index;
    start_index = returnIndex(label_start);
    end_index = returnIndex(label_end);
    nodes[start_index].AdjList.push_back(nodes[end_index]);
    nodes[end_index].AdjList.push_back(nodes[start_index]);
}

void Graph :: assignDegree(){
    for(int i = 0; i < num_nodes; i++){
        nodes[i].degree = nodes[i].AdjList.size();
    }
    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < nodes[i].AdjList.size(); j++){
            nodes[i].AdjList[j].degree = nodes[returnIndex(nodes[i].AdjList[j].label)].degree;
        }
    }
}

void Graph :: addNode(int val){       // Defining the add node function
    num_nodes++;
    Node node;
    node.label = val;
    node.index = num_nodes - 1;
    node.degree = 0;
    nodes.push_back(node);
}

void Graph :: addNode(Node node){
    num_nodes++;
    node.index = num_nodes - 1;
    nodes.push_back(node);
}

void Graph :: addNode(Node node, int val){
    num_nodes++;
    node.AdjList.clear();
    node.label = val;
    node.index = num_nodes - 1;
    node.degree = 0;
    nodes.push_back(node);
}

int Graph :: returnIndex(int lab){
    int index;
    for(index = 0; index < num_nodes; index++){
        if( nodes[index].label == lab){
            break;
        }
    }
    return index;
}

Graph Graph :: BFS(int source_label){
    Graph T;
    int index = 0;
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
            // cout << "i - " << i << " j - " << j << endl;
            // cout << "Label of node is " << L[i][j].label << " Degree of this node is " << L[i][j].degree << endl;
            for(int k = 0; k < L[i][j].degree; k++){
                // cout << "i - " << i << " j - " << j << " k - " << k << endl;
                // cout << "Before: Index - " << L[i][j].AdjList[k].index;
                // cout << " Discovered? " << Discovered[L[i][j].AdjList[k].index] << endl;
                if(Discovered[L[i][j].AdjList[k].index] == false){
                    Discovered[L[i][j].AdjList[k].index] = true;
                    // cout << "After: Index - " << L[i][j].AdjList[k].index << " Discovered? " << Discovered[L[i][j].AdjList[k].index] << endl;
                    T.addNode(L[i][j].AdjList[k].label);
                    // cout << "Node added. Degree: " << L[i][j].AdjList[k].degree << endl;
                    T.addEdge(nodes[returnIndex(L[i][j].label)].label, nodes[returnIndex(L[i][j].AdjList[k].label)].label);
                    // cout << "Edge added. Degree: " << L[i][j].AdjList[k].degree << endl;
                    // cout << "The label being pushed into L[" << i+1 << "] is " << L[i][j].AdjList[k].label << " Index:" << L[i][j].AdjList[k].index << "The degree is " << L[i][j].AdjList[k].degree << endl;
                    L[i+1].push_back(nodes[L[i][j].AdjList[k].index]);
                }
            }
        }
        i++;
    }
    return T;
}