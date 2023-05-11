#include <iostream>
#include <vector>
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
        vector<Node> AdjList; // Each node is associated with a vector containing nodes that are adjacent to it
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
    void assignDegree();    // Function to assign degrees to the graph when the addEdge function is used
    Graph BFS(int);     // BFS, label of source node is taken as input
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
            nodes[i].AdjList.push_back(nodes[returnIndex(val)]);    // Adding nodes with label val to the adjacency list of nodes[i]. Self note - I think this step is not accurate since nodes[returnIndex(val)] is not completely defined. So either I have to convert the adjList to simply an integer vector to simply store the labels, or convert it into a Node* vector
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
            cout << nodes[i].AdjList[j].label << " "; // Printing labels of adjacent nodes
        }
        cout << endl;
    }
}

void Graph :: addEdge(int label_start, int label_end){      // Defining function to add an edge, assuming the two labels already exist.
    int start_index, end_index;
    start_index = returnIndex(label_start);
    end_index = returnIndex(label_end);
    nodes[start_index].AdjList.push_back(nodes[end_index]);     // Adding the nodes to each others' adjlist
    nodes[end_index].AdjList.push_back(nodes[start_index]);
}

void Graph :: assignDegree(){       // Defining function to assign degrees to the nodes and its adjacent nodes, will not be required if I better the code in the future.
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
    num_nodes++;    // Increasing the number of nodes
    Node node;      // Initialising a node and adding it to the nodes vector
    node.label = val;
    node.index = num_nodes - 1;
    node.degree = 0;
    nodes.push_back(node);
}

int Graph :: returnIndex(int lab){      // Defining a function that returns the index of a node with a label lab
    int index;
    for(index = 0; index < num_nodes; index++){
        if( nodes[index].label == lab){
            break;      // Break out of for loop if lab is found amongst the labels, hence index is one required
        }
    }
    return index;
}

Graph Graph :: BFS(int source_label){   // Implementing BFS, followed the exact same algorithm given in the textbook, need to change it a bit once I change the AdjList, will be done soon.
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
            for(int k = 0; k < L[i][j].degree; k++){
                if(Discovered[L[i][j].AdjList[k].index] == false){
                    Discovered[L[i][j].AdjList[k].index] = true;
                    T.addNode(L[i][j].AdjList[k].label);
                    T.addEdge(nodes[returnIndex(L[i][j].label)].label, nodes[returnIndex(L[i][j].AdjList[k].label)].label);
                    L[i+1].push_back(nodes[L[i][j].AdjList[k].index]);
                }
            }
        }
        i++;
    }
    return T;
}

int main(){
    Graph G;
    G.inputGraph();
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
    // G.assignDegree();
    G.printGraph();
    Graph T = G.BFS(71);
    T.assignDegree();
    T.printGraph();
    return 0;
}