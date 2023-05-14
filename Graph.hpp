#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <stack>
#include <unordered_set>
#include <unordered_map>

class Node
{
    int val;                                       // The value that the particular node stores
    std::vector<std::pair<Node *, int>> neighbors; // The vector of the neighbors of that node with their corresponding weights

public:
    Node(int val) : val(val) {} // The default constructor
    friend class Graph;
};

class Graph
{
    std::vector<Node *> nodes; // The adjacency list of nodes of the graph
    Node *findNode(int val)    // Function to find the pointer of the node given its value
    {
        for (Node *node : nodes)
        {
            if (node->val == val)
            {
                return node;
            }
        }
        return nullptr;
    }
    int num_nodes; // Stores the number of nodes in the graph
    int num_edges; // Stores the number of edges in the graph
public:
    Graph();
    void add_node(int data);                           // Adds a node in the adjacency list with the value given as parameter
    void add_edge(int data1, int data2, int weight);   // Adds a weighted edge between the two nodes with the values as given in the argument
    bool are_adjacent(int data1, int data2);           // Function to check whether two nodes with the given values are adjacent or not
    void printGraph();                                 // Prints the entire graph (with weights in parenthesis)
    Graph BFS(int start);                              // Returns another graph object which is the BFS tree of the node with the given int as value
    Graph DFS(int start);                              // Returns another graph object which is the DFS tree of the node with the given int as value
    std::unordered_map<int, int> Dijisktra(int start); // Gives a map in which the index is the node value and the value of the index is the shortest distance of it from the start
};

Graph::Graph() // The default constructor
{
    num_nodes = 0;
    num_edges = 0;
}

void Graph::add_node(int data)
{
    Node *new_node = new Node(data);
    nodes.push_back(new_node);
    num_nodes++;
}

void Graph::add_edge(int data1, int data2, int weight)
{
    Node *node1 = findNode(data1); // Finds the node of the first int
    Node *node2 = findNode(data2); // Finds the node of the second int
    if (node1 && node2)            // If both the nodes exist then push them into each other's neighbors list
    {
        node1->neighbors.push_back(std::make_pair(node2, weight));
        node2->neighbors.push_back(std::make_pair(node1, weight));
        num_edges++;
    }
    else // If they don't exist then throw a runtime error
    {
        throw std::runtime_error("Either one or both of the values provided are not in the graph.");
    }
}

bool Graph::are_adjacent(int data1, int data2)
{
    Node *node1 = findNode(data1); // Finds the node of the first int
    Node *node2 = findNode(data2); // Finds the node of the second int

    if (node1 && node2) // If both nodes exist in the graph
    {
        for (auto neighbor : node1->neighbors) // Check if node2 is a neighbor of node1
        {
            if (neighbor.first == node2) return true;
        }
    }

    return false; // Nodes are not adjacent or at least one node does not exist in the graph
}

void Graph::printGraph()
{
    for (auto node : nodes) // Iterating throught the vector nodes and printing the nodes with their neigbhors and the corresponding weights
    {
        std::cout << node->val << " : ";
        for (auto neighbor : node->neighbors)
        {
            std::cout << neighbor.first->val << "(" << neighbor.second << "), ";
        }
        std::cout << std::endl;
    }
}

Graph Graph::BFS(int start)
{
    Node *start_node = findNode(start);    // Finding the first node
    std::queue<Node *> L;                  // Setting up the queue
    std::unordered_set<Node *> discovered; // Defining a set which will cover the visited nodes during the traversal
    Graph result;                          // The final graph which is to be returned
    L.push(start_node);
    discovered.insert(start_node);
    result.add_node(start);

    while (L.size() != 0)
    {
        Node *curr = L.front();
        L.pop();
        for (auto neighbor : curr->neighbors)
        {
            if (discovered.find(neighbor.first) == discovered.end())
            {
                L.push(neighbor.first);
                discovered.insert(neighbor.first); // Adding the node in the discovered set
                result.add_node(neighbor.first->val);
                result.add_edge(neighbor.first->val, curr->val, neighbor.second); // Adding the edge between the two nodes in the BFS tree
            }
        }
    }
    return result;
}

Graph Graph::DFS(int start)
{
    Node *start_node = findNode(start);    // Finding the starting node
    std::stack<Node *> L;                  // Setting up the stack
    std::unordered_set<Node *> discovered; // Defining a set which will cover the visited nodes during the traversal
    Graph result;                          // The final graph which is to be returned
    L.push(start_node);
    discovered.insert(start_node);
    result.add_node(start);

    while (L.size() != 0)
    {
        Node *curr = L.top();
        L.pop();
        for (auto neighbor : curr->neighbors)
        {
            if (discovered.find(neighbor.first) == discovered.end())
            {
                L.push(neighbor.first);
                discovered.insert(neighbor.first); // Adding the node in the discovered set
                result.add_node(neighbor.first->val);
                result.add_edge(neighbor.first->val, curr->val, neighbor.second); // Adding the edge between the two nodes in the DFS tree
            }
        }
    }
    return result;
}

std::unordered_map<int, int> Graph::Dijisktra(int start)
{
    Node *start_node = findNode(start);    // Finds the starting node
    std::unordered_map<int, int> result;   // The map which we will return
    result[start] = 0;                     // Setting the distance of the initial node to be zero
    std::unordered_set<Node *> discovered; // A set of the discovered nodes
    discovered.insert(start_node);         // Inserting the first node in the discovered set
    std::queue<Node *> L;                  // A queue to travel through the nodes in the graph
    L.push(start_node);                    // Pushing the start node in the queue
    while (L.size() != 0)                  // Travelling through the graph (in the connected component of the start node)
    {
        Node *curr = L.front();               // Setting the current element to be the front of the traversal queue
        L.pop();                              // Removing that element from the queue
        for (auto neighbor : curr->neighbors) // Travelling through the neighbors of that element
        {
            if (result.find(neighbor.first->val) == result.end()) // If the neighbor node's value is not in the map then add the weight + curr node's distance to the map
            {
                result[neighbor.first->val] = neighbor.second + result[curr->val];
            }
            else if (result.find(neighbor.first->val) != result.end() && result[neighbor.first->val] > neighbor.second + result[curr->val]) // Else if the neighbor node's value is in the graph but the curr node's distance + weight is giving shorter distance, update it
            {
                result[neighbor.first->val] = neighbor.second + result[curr->val];
            }
            if (discovered.find(neighbor.first) == discovered.end()) // If the neighbor node is not in the discovered set, insert it and push the node into the travelling queue
            {
                discovered.insert(neighbor.first);
                L.push(neighbor.first);
            }
        }
    }
    return result;
}
