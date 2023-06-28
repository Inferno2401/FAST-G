#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#define INFTY 10000000
#define INFTY2 100000000
#define INFTY3 1000000000

int minIndex( std::vector<int> arr ) {
    int min = INFTY3;
    int index;
    for ( int i = 0; i < arr.size(); i++ ) {
        if ( arr[i] < min ) {
            min = arr[i];
        }
    }
    for ( int i = 0; i < arr.size(); i++ ) {
        if ( arr[i] == min ) {
            index = i;
        }
    }
    return index;
}

class Graph {

    public:

    int num_nodes;

    struct Node{
        int label;
        std::pair<std::vector<Node*>,std::vector<int>> adj_list;
    };

    std::vector<Node*> nodes;

    Graph();
    void inputGraph();
    void printGraph();
    void addNode(int);
    void addUnweightedEdge(int, int);
    void addWeightedEdge(int, int, int);
    bool edgeExists(int, int);
    int returnIndex(int);
    int returnWeight(int, int);

    Graph BFS(int);
};

Graph :: Graph(){
    num_nodes = 0;
}

void Graph :: inputGraph(){
    std::cout << "Enter the number of nodes in the graph: ";
    std::cin >> num_nodes;
    std::cout << std::endl;

    for(int i = 0; i < num_nodes; i++){
        Node* node = new Node;
        std::cout << "Enter the label of the " << i+1 << " node: ";
        std::cin >> node->label;
        nodes.push_back(node);
    }

    for(int i = 0; i < num_nodes; i++){
        int val;
        int degree;
        int weight;
        std::cout << "Enter the degree of the node with label " << nodes[i]->label << std::endl;
        std::cin >> degree;
        for(int j = 0; j < degree; j++){
            std::cout << "Enter the label of the adjacent node: ";
            std::cin >> val;
            std::cout << std::endl;
            nodes[i]->adj_list.first.push_back(nodes[returnIndex(val)]);
            std::cout << "Enter the weight of the adjacent node: ";
            std::cin >> weight;
            nodes[i]->adj_list.second.push_back(weight);
        }
    }
}

void Graph :: printGraph(){
    for(int i = 0; i < num_nodes; i++){
        std::cout << "Label - " << nodes[i]->label << " - ";
        for(int j = 0; j < nodes[i]->adj_list.first.size(); j++){
            std::cout << nodes[i]->adj_list.first[j]->label << "-" << nodes[i]->adj_list.second[j] << ", ";
        }
        std::cout << std::endl;
    }
}

void Graph :: addNode(int label){
    num_nodes++;
    Node* node = new Node;
    node->label = label;
    nodes.push_back(node);
}

void Graph :: addUnweightedEdge(int start, int end){
    if(!(returnIndex(start)+1) && !(returnIndex(end)+1)){
        std::cout << "Node does not exist, either add a valid node or use addNode" << std::endl;
    }
    else{
        nodes[returnIndex(start)]->adj_list.first.push_back(nodes[returnIndex(end)]);
        nodes[returnIndex(start)]->adj_list.second.push_back(1);
        nodes[returnIndex(end)]->adj_list.first.push_back(nodes[returnIndex(start)]);
        nodes[returnIndex(end)]->adj_list.second.push_back(1);
    }
}

void Graph :: addWeightedEdge(int start, int end, int weight){
    if(!(returnIndex(start)+1) && !(returnIndex(end)+1)){
        std::cout << "Node does not exist, either add a valid node or use addNode" << std::endl;
    }
    else{
        nodes[returnIndex(start)]->adj_list.first.push_back(nodes[returnIndex(end)]);
        nodes[returnIndex(start)]->adj_list.second.push_back(weight);
        nodes[returnIndex(end)]->adj_list.first.push_back(nodes[returnIndex(start)]);
        nodes[returnIndex(end)]->adj_list.second.push_back(weight);
    }
}

bool Graph :: edgeExists(int start, int end){
    bool flag = false;

    for(int i = 0; i < nodes[returnIndex(start)]->adj_list.first.size(); i++){
        if(nodes[returnIndex(start)]->adj_list.first[i]->label == end){
            flag = true;
        }
    }

    return flag;
}

int Graph :: returnIndex(int label){
    int index = 0;

    for(index = 0; index < num_nodes; index++){
        if(nodes[index]->label == label){
            break;
        }
    }

    if(num_nodes == 0){
        return -1;
    }

    else if(nodes[index]->label == label){
        return index;
    }

    else{
        return -1;
    }
}

int Graph :: returnWeight(int start, int end){
    if(start == end){
        return 0;
    }

    if(edgeExists(start,end)){
        std::cout << edgeExists(start, end) << std::endl;
        int i;
        for(i = 0; i < nodes[returnIndex(start)]->adj_list.first.size(); i++){
            if (nodes[returnIndex(start)]->adj_list.first[i]->label == end){
                break;
            }    
        }
        return nodes[returnIndex(start)]->adj_list.second[i];
    }

    else{
        return INFTY;
    }
}

Graph Graph :: BFS(int source){
    Graph T;
    bool Discovered[num_nodes];
    std::vector<std::vector<Node*>> L;
    int i = 0;
    for (int m = 0; m < num_nodes; m++){
        Discovered[m] = false;
    }
    Discovered[returnIndex(source)] = true;
    L.push_back({nodes[returnIndex(source)]});
    T.addNode(L[0][0]->label);
    while(L[i].empty() != 1){
        L.push_back({});
        for(int j = 0; j < L[i].size(); j++){
            for(int k = 0; k < L[i][j]->adj_list.first.size(); k++){
                if(Discovered[returnIndex(L[i][j]->adj_list.first[k]->label)] == false){
                    Discovered[returnIndex(L[i][j]->adj_list.first[k]->label)] = true;
                    T.addNode(L[i][j]->adj_list.first[k]->label);
                    T.addWeightedEdge(L[i][j]->label, L[i][j]->adj_list.first[k]->label, returnWeight(L[i][j]->label, L[i][j]->adj_list.first[k]->label));
                    L[i+1].push_back(nodes[returnIndex(L[i][j]->adj_list.first[k]->label)]);
                }
            }
        }
        i++;
    }    
    return T;
}