#include <iostream>
#include <vector>
#include <stack>
using namespace std;

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
        int degree;     // Degree of the node, may not be necessary as a variable, but I have implemented it
    };
    vector<Node> nodes; // Vector containing the nodes of the graph

    // member functions
    Graph();    // constructor
    void inputGraph();   // Function to take the entire graph as an input
    void printGraph();   // Function to print the graph as an adjacency list
    int returnIndex(int);   // Function to return the index of a node with the label as parameter
    void addNode(int);    // Function to add a node to a graph, with label as parameter
    void addEdge(int, int);     // Function to add an edge with two labels as parameters
    Graph BFS(int);     // BFS, label of source node is taken as input
    Graph DFS(int);     // DFS, label of source node is taken as input
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

Graph Graph :: DFS(int source_label){   // Implementing DFS, followed exact same algo as given in textbook, however need to check it
    Graph T;
    stack<Node> S;
    Node parent[num_nodes];
    bool Discovered[num_nodes];
    int count[num_nodes];
    for(int m = 0; m < num_nodes; m++){
        count[m] = 0;
    }
    for(int m = 0; m < num_nodes; m++){
        Discovered[m] = false;
    }
    S.push(nodes[returnIndex(source_label)]);
    while( S.empty() != 1 ){
        bool flag = false;
        bool flag1 = true;
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
                S.push(nodes[returnIndex(node.AdjList[i])]);
                // cout << "Pushed " << node.AdjList[i] << " into the stack" << endl;
                count[returnIndex(node.AdjList[i])]++;
                // cout << "Count of index " << returnIndex(node.AdjList[i]) << " and value " << node.AdjList[i] << " is " << count[returnIndex(node.AdjList[i])] << endl;
                if(count[returnIndex(node.AdjList[i])] == 1 && node.AdjList[i]!=source_label){
                    parent[returnIndex(node.AdjList[i])] = node;
                    // cout << "Parent of " << node.AdjList[i] << " is " << node.label << endl;
                }
            }
        }
    }
    return T;
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
    G.addEdge(6,2);
    G.addEdge(6,15);
    G.addEdge(2,3);
    G.addEdge(3,15);
    G.addEdge(3,48);
    G.addEdge(15,48);
    G.addEdge(48,83);
    G.addEdge(48,71);
    G.addEdge(71,16);
    G.addEdge(16,8);
    G.addEdge(16,23);
    G.addEdge(71,5);
    G.addEdge(5,64);
    G.addEdge(64,3);
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
    // G.printGraph();
    Graph B = G.BFS(71);
    B.printGraph();
    Graph D = G.DFS(71);
    D.printGraph();
    return 0;
}