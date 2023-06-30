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

int maxIndex(std::vector<int> arr){
    int max = -1;
    int index;
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] > max){
            max = arr[i];
            index = i;
        }
    }
    return index;
}

std::vector<int> selectionSort(std::vector<int> arr){
    std::vector<int> copy = arr;
    int index;
    int temp;
    for(int i = 0; i < arr.size(); i++){
        index = maxIndex(copy);
        temp = arr[index];
        arr[index] = arr[arr.size()-i-1];
        arr[arr.size()-i-1] = temp;
        temp = copy[index];
        copy[index] = copy[copy.size()-1];
        copy[copy.size()-1] = temp;
        copy.pop_back();
    }
    std::vector<int> result = arr;
    return result;
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
    bool operator==(Graph);
    void inputGraph();
    void printGraph();
    void addNode(int);
    void addUnweightedEdge(int, int);
    void addWeightedEdge(int, int, int);
    void removeEdge(int, int);
    bool edgeExists(int, int);
    int returnIndex(int);
    int returnWeight(int, int);
    int numEdges();
    std::pair<std::vector<int>,std::vector<std::pair<int,int>>> sortEdges(std::pair<std::vector<int>,std::vector<std::pair<int,int>>>);
    bool cycleExists();

    Graph BFS(int);
    Graph DFS(int);
    std::vector<int> Dijkstra(int);
    std::vector<std::vector<int>> APSP();
    Graph Kruskal();
};

Graph :: Graph(){
    num_nodes = 0;
}

bool Graph :: operator==(Graph A){
    if( num_nodes != A.num_nodes){
        return false;
    }
    std::vector<bool> flag;
    std::vector<bool> True;
    for(int i = 0; i < num_nodes; i++){
        True.push_back(true);
    }
    std::vector<int> arr1;
    for(int i = 0; i < num_nodes; i++){
        arr1.push_back(nodes[i]->label);
    }
    arr1 = selectionSort(arr1);
    std::vector<int> arr2;
    for(int i = 0; i < num_nodes; i++){
        arr2.push_back(A.nodes[i]->label);
    }
    arr2 = selectionSort(arr2);
    if(arr1 != arr2){
        return false;
    }
    else{
        for(int i = 0; i < num_nodes; i++){
            std::vector<int> array1;
            for(int j = 0; j < nodes[returnIndex(arr1[i])]->adj_list.first.size(); j++){
                array1.push_back(nodes[returnIndex(arr1[i])]->adj_list.first[j]->label);
            }
            std::vector<int> array2;
            for(int j = 0; j < A.nodes[A.returnIndex(arr1[i])]->adj_list.first.size(); j++){
                array2.push_back(A.nodes[A.returnIndex(arr1[i])]->adj_list.first[j]->label);
            }
            array1 = selectionSort(array1);
            array2 = selectionSort(array2);
            if(array1 == array2){
                flag.push_back(true);
            }
            else{
                flag.push_back(false);
            }
        }
        if(flag == True){
            return true;
        }
        else{
            return false;
        }
    }
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
    std::cout << "The number of nodes in the graph is " << num_nodes << std::endl;
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

void Graph :: removeEdge(int start, int end){
    if(!edgeExists(start, end)){
        std::cout << "The edge does not exist";
    }
    else{
        int i;
        for(i = 0; i < nodes[returnIndex(start)]->adj_list.first.size(); i++){
            if(end == nodes[returnIndex(start)]->adj_list.first[i]->label){
                break;
            }
        }
        int j;
        for(j = 0; j < nodes[returnIndex(end)]->adj_list.first.size(); j++){
            if(start == nodes[returnIndex(end)]->adj_list.first[j]->label){
                break;
            }
        }
        nodes[returnIndex(end)]->adj_list.first.erase(nodes[returnIndex(end)]->adj_list.first.begin()+j);
        nodes[returnIndex(end)]->adj_list.second.erase(nodes[returnIndex(end)]->adj_list.second.begin()+j);
        nodes[returnIndex(start)]->adj_list.first.erase(nodes[returnIndex(start)]->adj_list.first.begin()+i);
        nodes[returnIndex(start)]->adj_list.second.erase(nodes[returnIndex(start)]->adj_list.second.begin()+i);
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
    else if(index < num_nodes){
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

int Graph ::numEdges(){
    int num_edges = 0;
    for(int i = 0; i < num_nodes; i++){
        num_edges = num_edges + nodes[i]->adj_list.first.size();
    }
    num_edges = num_edges/2;
    return num_edges;
}

std::pair<std::vector<int>,std::vector<std::pair<int,int>>> Graph :: sortEdges(std::pair<std::vector<int>,std::vector<std::pair<int,int>>> edges){
    std::pair<std::vector<int>,std::vector<std::pair<int,int>>> copy = edges;
    int index;
    int temp;
    std::pair<int,int> temp_edge;
    for(int i = 0; i < edges.first.size(); i++){
        index = maxIndex(copy.first);
        temp = edges.first[index];
        temp_edge = edges.second[index];
        edges.first[index] = edges.first[edges.first.size()-i-1];
        edges.second[index] = edges.second[edges.second.size()-i-1];
        edges.first[edges.first.size()-i-1] = temp;
        edges.second[edges.second.size()-i-1] = temp_edge;
        temp = copy.first[index];
        temp_edge = copy.second[index];
        copy.first[index] = copy.first[copy.first.size()-1];
        copy.second[index] = copy.second[copy.second.size()-1];
        copy.first[copy.first.size()-1] = temp;
        copy.second[copy.second.size()-1] = temp_edge;
        copy.first.pop_back();
        copy.second.pop_back();
    }
    return edges;
}

bool Graph :: cycleExists(){
    bool flag = false;
    int source;
    bool flag2 = false;
    for(int i = 0; i < num_nodes; i++){
        source = nodes[i]->label;
        std::stack<Node*> S;
        Node* parent[num_nodes];
        bool Discovered[num_nodes];
        for(int m = 0; m < num_nodes; m++){
            Discovered[m] = false;
        }
        S.push(nodes[returnIndex(source)]);
        while(S.empty() != 1){
            Node* node = S.top();
            S.pop();
            if(Discovered[returnIndex(node->label)] == false){
                Discovered[returnIndex(node->label)] = true;
                for(int i = 0; i < node->adj_list.first.size(); i++){
                    std::stack<Node*> Copy = S;
                    for(int j = 0; j < Copy.size(); j++){
                        if(node->adj_list.first[i] == Copy.top()){
                            flag2 = true;
                            break;
                        }
                        else{
                            Copy.pop();
                        }
                    }
                    if(Discovered[returnIndex(node->adj_list.first[i]->label)] == false){
                        if(flag2){
                            flag = true;
                        }
                        S.push(nodes[returnIndex(node->adj_list.first[i]->label)]);
                        parent[returnIndex(node->adj_list.first[i]->label)] = node;
                    }
                }
            }
        }
    }
    return flag;
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

Graph Graph :: DFS(int source){
    Graph T;
    std::stack<Node*> S;
    Node* parent[num_nodes];
    bool Discovered[num_nodes];
    for(int m = 0; m < num_nodes; m++){
        Discovered[m] = false;
    }
    S.push(nodes[returnIndex(source)]);
    while(S.empty() != 1){
        Node* node = S.top();
        S.pop();
        if(!(T.returnIndex(node->label)+1)){
            T.addNode(node->label);
        }
        if(Discovered[returnIndex(node->label)] == false){
            Discovered[returnIndex(node->label)] = true;
            if(node->label != source){
                T.addWeightedEdge(node->label, parent[returnIndex(node->label)]->label, returnWeight(node->label, parent[returnIndex(node->label)]->label));
            }
            for(int i = 0; i < node->adj_list.first.size(); i++){
                if(Discovered[returnIndex(node->adj_list.first[i]->label)] == false){
                    S.push(nodes[returnIndex(node->adj_list.first[i]->label)]);
                    parent[returnIndex(node->adj_list.first[i]->label)] = node;
                }
            }
        }
    }
    return T;
}

std::vector<int> Graph :: Dijkstra(int source){
    std::vector<int> Distance;
    std::vector<int> DistanceCopy;
    std::vector<bool> visited;
    std::vector<bool> True;
    int index;
    for(int i = 0; i < num_nodes; i++){
        Distance.push_back(0);
    }
    for(int i = 0; i < num_nodes; i++){
        Distance[i] = returnWeight(source,nodes[i]->label);
    }
    DistanceCopy = Distance;
    for(int i = 0; i < num_nodes; i++){
        visited.push_back(false);
    }
    for(int i = 0; i < num_nodes; i++){
        True.push_back(true);
    }
    visited[returnIndex(source)] = true;
    DistanceCopy[returnIndex(source)] = INFTY2;
    while(visited != True){
        index = minIndex(DistanceCopy);
        DistanceCopy[index] = INFTY2;
        visited[index] = true;
        for(int i = 0; i < num_nodes; i++){
            if(Distance[i] > Distance[index] + returnWeight(nodes[index]->label, nodes[i]->label)){
                Distance[i] = Distance[index] + returnWeight(nodes[index]->label, nodes[i]->label);
                DistanceCopy[i] = Distance[index] + returnWeight(nodes[index]->label, nodes[i]->label);
            }
        }
    }
    return Distance;
}

std::vector<std::vector<int>> Graph :: APSP(){
    std::vector<std::vector<int>> Distance;
    for(int i = 0; i < num_nodes; i++){
        Distance.push_back(Dijkstra(nodes[i]->label));
    }
    return Distance;
}

Graph Graph :: Kruskal(){
    Graph T;
    int num_edges = 0;
    int count = 0;
    std::pair<int,int> edge;
    std::pair<std::vector<int>,std::vector<std::pair<int,int>>> edges;
    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < nodes[i]->adj_list.first.size(); j++){
            bool flag = false;
            for(int k = 0; k < edges.second.size(); k++){
                if(((nodes[i]->label == edges.second[k].first) && (nodes[i]->adj_list.first[j]->label == edges.second[k].second)) || ((nodes[i]->label == edges.second[k].second) && (nodes[i]->adj_list.first[j]->label == edges.second[k].first))){
                    flag = true;
                }
            }
            if(flag == false){
                edges.first.push_back(nodes[i]->adj_list.second[j]);
                edge.first = nodes[i]->label;
                edge.second = nodes[i]->adj_list.first[j]->label;
                edges.second.push_back(edge);
            }

        }
    }
    std::pair<std::vector<int>,std::vector<std::pair<int,int>>> edges_sorted = sortEdges(edges);
    for(int i = 0; i < edges_sorted.first.size(); i++){
        std::cout << i << " - Weight - " << edges_sorted.first[i] <<  " Edge - " << edges_sorted.second[i].first << ", " << edges_sorted.second[i].second << std::endl;
    }
    while(num_edges < num_nodes-1){
        if(!(T.returnIndex(edges_sorted.second[count].first) + 1)){
            T.addNode(edges_sorted.second[count].first);
        }
        if(!(T.returnIndex(edges_sorted.second[count].second) + 1)){
            T.addNode(edges_sorted.second[count].second);
        }
        T.addWeightedEdge(edges_sorted.second[count].first, edges_sorted.second[count].second, returnWeight(edges_sorted.second[count].first, edges_sorted.second[count].second));
        if(T.cycleExists()){
            T.removeEdge(edges_sorted.second[count].first, edges_sorted.second[count].second);
        }
        else{
            num_edges++;
        }
        count++;
    }
    return T;
}