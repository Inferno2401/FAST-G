#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <stack>
#include <algorithm>
#include <limits>
#include <unordered_set>
#include <unordered_map>

class Node
{
    int val;                                       // The value that the particular node stores
    std::vector<std::pair<Node *, int>> neighbors; // The vector of the neighbors of that node with their corresponding weights

public:
    Node(int val) : val(val) {} // The default constructor
    friend class Graph;
    friend class DirectedGraph;
};

class Graph
{
protected:
    std::vector<Node *> nodes;                              // The adjacency list of nodes of the graph
    std::vector<std::pair<int, std::pair<int, int>>> edges; // Vector containing all the edges and their weigths
    Node *findNode(int val)                                 // Function to find the pointer of the node given its value
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
    Graph(const Graph &graph);
    void add_node(int data);                          // Adds a node in the adjacency list with the value given as parameter
    void add_edge(int data1, int data2, int weight);  // Adds a weighted edge between the two nodes with the values as given in the argument
    bool are_adjacent(int data1, int data2);          // Function to check whether two nodes with the given values are adjacent or not
    int getWeight(int data1, int data2);              // Function to return the weight of edge between nodes given the node
    void printGraph();                                // Prints the entire graph (with weights in parenthesis)
    Graph BFS(int start);                             // Returns another graph object which is the BFS tree of the node with the given int as value
    Graph DFS(int start);                             // Returns another graph object which is the DFS tree of the node with the given int as value
    std::unordered_map<int, int> Dijkstra(int start); // Gives a map in which the index is the node value and the value of the index is the shortest distance of it from the start
    Graph Prim();                                     // Returns a minimum spanning tree for the graph
};

Graph::Graph() // The default constructor
{
    num_nodes = 0;
    num_edges = 0;
}

Graph::Graph(const Graph &graph)
{
    // Create a map to keep track of the mapping between original nodes and copied nodes
    std::unordered_map<Node *, Node *> nodeMapping;

    // Copy the nodes and build the mapping
    for (auto node : graph.nodes)
    {
        Node *newNode = new Node(node->val);
        nodes.push_back(newNode);    // Add the node to the new graph
        nodeMapping[node] = newNode; // Map the original node to the copied node
    }

    // Copy the edges using the node mapping
    for (auto node : graph.nodes)
    {
        Node *originalNode = node;
        Node *copiedNode = nodeMapping[originalNode];

        // Fetch all edges for the current node in the original graph
        for (const auto &neighbor : originalNode->neighbors)
        {
            Node *neighborNode = neighbor.first;
            int weight = neighbor.second;
            Node *copiedNeighborNode = nodeMapping[neighborNode];

            // Add the edge to the new graph
            copiedNode->neighbors.push_back(std::make_pair(copiedNeighborNode, weight));
        }
    }
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
        edges.push_back({weight, {data1, data2}});
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
            if (neighbor.first == node2)
                return true;
        }
    }

    return false; // Nodes are not adjacent or at least one node does not exist in the graph
}

int Graph::getWeight(int data1, int data2)
{
    Node *node1 = findNode(data1);
    Node *node2 = findNode(data2);
    for (auto &neighbor : node1->neighbors)
    {
        if (neighbor.first->val == data2)
        {
            return neighbor.second;
        }
    }
    return 0;
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

std::unordered_map<int, int> Graph::Dijkstra(int start)
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

Graph Graph::Prim()
{
    std::unordered_set<Node *> visited; // Track nodes that have already been added
    visited.insert(nodes[0]);           // Start with any node

    auto cmp = [](const std::pair<int, std::pair<int, int>> &a, const std::pair<int, std::pair<int, int>> &b)
    {
        return a.first > b.first;
    }; // Defines comparison operator for edges based on their weights

    // This creates a priority queue to store edges (as pairs with weight and connected nodes)
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, decltype(cmp)> pq(cmp);

    // Add edges from the first node to the priority queue
    for (const auto &neighbor : nodes[0]->neighbors)
    {
        pq.push({neighbor.second, {nodes[0]->val, neighbor.first->val}});
    }

    Graph minSpanningTree; // Initialize the final graph object we will return

    // Main loop
    while (!pq.empty())
    {
        std::pair<int, std::pair<int, int>> currEdge = pq.top(); // Extract the edge with minimum weight
        pq.pop();

        // Extract the nodes of the edge
        int from = currEdge.second.first;
        int to = currEdge.second.second;

        // If the 'to' node isn't visited, add that in the min spanning tree
        if (visited.find(findNode(to)) == visited.end())
        {
            visited.insert(findNode(to));
            // Check if the nodes are present already or not and add them correspondingly
            if (minSpanningTree.findNode(from) == NULL)
                minSpanningTree.add_node(from);
            if (minSpanningTree.findNode(to) == NULL)
                minSpanningTree.add_node(to);
            minSpanningTree.add_edge(from, to, currEdge.first);

            // Adding more edges to the priority queue
            for (const auto &edge : edges)
            {
                if (edge.second.first == to && visited.find(findNode(edge.second.second)) == visited.end())
                {
                    pq.push({edge.first, {to, edge.second.second}});
                }
                else if (edge.second.second == to && visited.find(findNode(edge.second.first)) == visited.end())
                {
                    pq.push({edge.first, {to, edge.second.first}});
                }
            }
        }
    }
    return minSpanningTree;
}

// Making a subclass for directed graphs

class DirectedGraph : public Graph
{
public:
    void add_edge(int data1, int data2, int weight)
    {
        Node *node1 = findNode(data1);
        Node *node2 = findNode(data2);

        if (node1 && node2)
        {
            node1->neighbors.push_back(std::make_pair(node2, weight));
        }
    }
    DirectedGraph();
    DirectedGraph(const DirectedGraph &graph);
    void delete_node(int data);
    std::pair<int, DirectedGraph> Ford_Fulkerson(int source, int sink);
    void change_edge_weight(int data1, int data2, int newWeight);
    bool augment(int source, int sink, std::unordered_map<int, int> &parent);
    int dfsAugment(DirectedGraph &residualGraph, int current, int sink, int minCapacity, std::unordered_map<int, bool> &visited);
    void perfectMatching(int n);
};

// The default constructor
DirectedGraph::DirectedGraph()
{
    num_nodes = 0;
    num_edges = 0;
}

DirectedGraph::DirectedGraph(const DirectedGraph &graph)
{
    // Create a map to keep track of the mapping between original nodes and copied nodes
    std::unordered_map<Node *, Node *> nodeMapping;

    // Copy the nodes and build the mapping
    for (auto node : graph.nodes)
    {
        Node *newNode = new Node(node->val);
        add_node(newNode->val);      // Add the node to the new graph
        nodeMapping[node] = newNode; // Map the original node to the copied node
    }

    // Copy the edges using the node mapping
    for (auto node : graph.nodes)
    {
        Node *originalNode = node;
        Node *copiedNode = nodeMapping[originalNode];

        // Fetch all edges for the current node in the original graph
        for (const auto &neighbor : originalNode->neighbors)
        {
            Node *neighborNode = neighbor.first;
            int weight = neighbor.second;
            Node *copiedNeighborNode = nodeMapping[neighborNode];

            // Add the edge to the new graph
            add_edge(copiedNode->val, copiedNeighborNode->val, weight);
        }
    }
}

void DirectedGraph::delete_node(int data)
{
    // Find the node to be deleted
    Node *nodeToDelete = findNode(data);

    if (nodeToDelete)
    {
        // Remove the node from the 'nodes' vector
        auto it = std::find(nodes.begin(), nodes.end(), nodeToDelete);
        if (it != nodes.end())
        {
            nodes.erase(it);
        }

        // Remove edges connected to the node
        for (Node *node : nodes)
        {
            auto &neighbors = node->neighbors;
            neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(),
                                           [nodeToDelete](const std::pair<Node *, int> &neighbor)
                                           {
                                               return neighbor.first == nodeToDelete;
                                           }),
                            neighbors.end());
        }

        // Delete the node
        delete nodeToDelete;
    }
}

void DirectedGraph::change_edge_weight(int data1, int data2, int weight)
{
    // Find the nodes
    Node *node1 = findNode(data1);
    Node *node2 = findNode(data2);
    bool edgeExists = false;
    for (auto &neighbor : node1->neighbors)
    {
        if (neighbor.first->val == data2)
        {
            // Edge exists, update the weight
            neighbor.second = weight;
            edgeExists = true;
            break;
        }
    }

    if (!edgeExists)
    {
        // Edge doesn't exist, add a new one
        node1->neighbors.push_back(std::make_pair(node2, weight));
    }
}

// Function to perform a depth-first search on the residual graph to find an augmenting path
// from 'current' to 'sink' with a minimum capacity of 'minCapacity'
int DirectedGraph::dfsAugment(DirectedGraph &residualGraph, int current, int sink, int minCapacity, std::unordered_map<int, bool> &visited)
{
    visited[current] = true;

    // If we have reached the sink node, return the minimum capacity found along the path
    if (current == sink)
    {
        return minCapacity;
    }

    // Iterate through neighbors of the current node in the residual graph
    for (auto &neighbor : residualGraph.findNode(current)->neighbors)
    {
        int next = neighbor.first->val;
        int capacity = neighbor.second;

        // If the neighbor is unvisited and the edge has remaining capacity
        if (!visited[next] && capacity > 0)
        {
            // Recursively find the bottleneck value for the augmenting path
            int bottleneck = dfsAugment(residualGraph, next, sink, std::min(minCapacity, capacity), visited);

            // If an augmenting path is found update residual graph and return bottleneck
            if (bottleneck > 0)
            {
                residualGraph.change_edge_weight(current, next, capacity - bottleneck);
                residualGraph.change_edge_weight(next, current, residualGraph.getWeight(next, current) + bottleneck);
                return bottleneck;
            }
        }
    }

    // If no augmenting path found return 0
    return 0;
}

// Function to find the maximum flow in a graph using the Ford-Fulkerson algorithm
std::pair<int, DirectedGraph> DirectedGraph::Ford_Fulkerson(int source, int sink)
{
    // Create a copy of the original graph as the residual graph
    DirectedGraph residualGraph(*this);

    // Initialize the total maximum flow to 0
    int maxFlow = 0;
    int bottleneck;

    // Main loop
    while (true)
    {
        // Initialize a map to keep track of visited nodes in DFS
        std::unordered_map<int, bool> visited;
        for (auto &i : nodes)
        {
            visited[i->val] = false;
        }

        bottleneck = dfsAugment(residualGraph, source, sink, INT_MAX, visited); // Find an augmenting path and the corresponding bottleneck value
        if (bottleneck == 0)
            break;             // If no more augmenting paths can be found, exit the loop
        maxFlow += bottleneck; // Update the maxFlow variable
    }

    return std::make_pair(maxFlow, residualGraph);
}

void DirectedGraph::perfectMatching(int n)
{
    DirectedGraph flowGraph(*this);
    // Adding the source and sink nodes
    flowGraph.add_node(0);
    flowGraph.add_node(2 * n + 1);
    for (int i = 1; i <= n; i++)
    {
        flowGraph.add_edge(0, i, 1);
        flowGraph.add_edge(n + i, 2 * n + 1, 1);
    }
    // Getting the residual graph using ford-fulkerson algo
    DirectedGraph residualGraph = flowGraph.Ford_Fulkerson(0, 2 * n + 1).second;
    residualGraph.delete_node(0);
    residualGraph.delete_node(2 * n + 1);
    std::cout << "--------------------\n";
    std::cout << "|Set 1    |    Set 2|\n";
    std::cout << "--------------------\n";
    for (int i = 1; i <= n; i++)
    {
        for (auto neighbor : residualGraph.findNode(i)->neighbors)
        {
            if (neighbor.second == 0)
            {
                std::cout << "|  " << i << "      |      " << neighbor.first->val - n << "  |\n";
            }
        }
    }
    std::cout << "--------------------\n";
}
