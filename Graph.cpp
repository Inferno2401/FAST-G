#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

class Graph 
{
    public:
    // struct for node
    struct Node
    {
        int label;
        vector<Node*> adjNodes;

        bool operator==(const Node other) const
        {
            return (label == other.label && adjNodes == other.adjNodes);
        }
        Node& operator=(const Node& other)
        {
            label = other.label;
            adjNodes = other.adjNodes;
            return *this;
        }
    };

    int n; // number of nodes
    int n_total; // number of nodes added in total
    map<int, Node*> nodes; // adjacency list for graph

    // constructors
    Graph ()
    {
        n = 0;
        n_total = 0;
    }
    Graph (vector<int> labels, vector<vector<int>> adj_lists)
    {
        n = 0;
        n_total = 0;
        initializeGraph(adj_lists, labels);
        printGraph();
    }

    // destructor
    ~Graph ()
    {
        for (auto& node : nodes)
        {
            delete node.second;
        }
    }

    // public methods
    void initializeGraph (vector<vector<int>> adj_lists, vector<int> new_labels = vector<int>()) // initialize graph
    {
        bool is_empty = new_labels.empty();
        n = adj_lists.size();
        for (int i = 0; i < n; i++)
        {
            Node* node = new Node();
            if (is_empty)
                node->label = n_total;
            else
                node->label = new_labels[i];
            n_total++;
            nodes[node->label] = node;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < adj_lists[i].size(); j++)
            {
                nodes[nodes[i]->label]->adjNodes.push_back(nodes[adj_lists[i][j]]);
            }
        }   
    }
    void deleteNode (int label) // delete node
    {   
        for (Node* node : nodes[label]->adjNodes)
        {
            for (Node* adjNode : node->adjNodes)
            {
                if (adjNode->label == label)
                {
                    node->adjNodes.erase(remove(node->adjNodes.begin(), node->adjNodes.end(), nodes[label]), node->adjNodes.end());
                }
            }
        }
        delete nodes[label];
        nodes.erase(label);
        n--;
    }
    void printGraph () // print graph
    {
        for (auto& node : nodes)
        {
            cout << node.first << ": ";
            for (Node* adj_node : node.second->adjNodes)
            {
                cout << adj_node->label << " ";
            }
            cout << endl;
        }
    }
    void addNode (vector<int> labels = vector<int>(), int new_label = -1) // add node using adjacent nodes
    {
        Node* new_node = new Node();
        if (new_label == -1)
            new_node->label = n_total;
        else
            new_node->label = new_label;
        for (auto& node : nodes)
        {
            for (int label : labels)
            {
                if (node.first == label)
                {
                    new_node->adjNodes.push_back(nodes[label]);
                    node.second->adjNodes.push_back(new_node);
                }
            }
        }
        nodes[new_node->label] = new_node;
        n++;
        n_total++;
    }
    void addNode (Node* node) // add node using Node*
    {
        nodes[node->label] = node;
        n_total++;
    }
    void addEdge (int label1, int label2) // join two nodes
    {
        bool flag1 = true, flag2 = true;
        for (auto& node : nodes)
        {
            if (flag1 && node.first == label1)
            {
                node.second->adjNodes.push_back(nodes[label2]);
                flag1 = !flag1;
            }
            if (flag2 && node.first == label2)
            {
                node.second->adjNodes.push_back(nodes[label1]);
                flag2 = !flag2;
            }
            if (!(flag1 || flag2))
            {
                break;
            }
        }
    }
    Graph BFS (int root) // breadth-first search
    {
        /*
        Returns a Graph object that is in the form of a tree, i.e, each node has
        only a parent and children nodes.
        */
        Graph tree;
        Node* new_root = new Node();
        new_root->label = root;
        new_root->adjNodes = {};
        map<int, int> discovered;
        discovered[root] = 1;

        queue<Node*> order;
        queue<Node*> original_nodes;
        order.push(new_root);
        original_nodes.push(nodes[root]);

        tree.nodes[new_root->label] = new_root;

        while (!order.empty())
        {
            Node* node = order.front();
            Node* original_node = original_nodes.front();
            order.pop();
            original_nodes.pop();
            for (Node* adjNode : original_node->adjNodes)
            {
                if (discovered[adjNode->label] == 0)
                {
                    discovered[adjNode->label] = 1;
                    Node* temp_node = new Node();
                    temp_node->label = adjNode->label;
                    temp_node->adjNodes.push_back(node);
                    node->adjNodes.push_back(temp_node);
                    order.push(temp_node);
                    original_nodes.push(adjNode);

                    tree.nodes[temp_node->label] = temp_node;
                }
            }
        }
        return tree;
    }
    Graph DFS(int root) // depth-first search
    {
        /*
        Returns a Graph object that is in the form of a tree, i.e, each node has
        only a parent and children nodes.
        */
        Graph tree;
        Node* new_root = new Node();
        new_root->label = root;
        new_root->adjNodes = {};
        map<int, int> discovered;
        discovered[root] = 1;

        stack<Node*> order;
        stack<Node*> original_nodes;
        order.push(new_root);
        original_nodes.push(nodes[root]);

        tree.nodes[new_root->label] = new_root;

        while (!order.empty())
        {
            Node* node = order.top();
            Node* original_node = original_nodes.top();
            order.pop();
            original_nodes.pop();
            for (Node* adjNode : original_node->adjNodes)
            {
                if (discovered[adjNode->label] == 0)
                {
                    discovered[adjNode->label] = 1;
                    Node* temp_node = new Node();
                    temp_node->label = adjNode->label;
                    temp_node->adjNodes.push_back(node);
                    node->adjNodes.push_back(temp_node);
                    order.push(temp_node);
                    original_nodes.push(adjNode);

                    tree.nodes[temp_node->label] = temp_node;
                }
            }
        }
        return tree;
    }
    pair<map<int, int>, map<int, int>> Dijkstra(int s) // Dijkstra's algorithm 
    {
        /*
        Returns a pair with a map of distances of nodes from root node and a map
        of previous nodes for the shortest path from the root node
        */
        map<int, int> d;
        map<int, int> p;
        map<int, bool> marked;

        for (auto& node : nodes)
        {
            d[node.first] = numeric_limits<int>::max();
        }
        d[s] = 0;
        int d_min = numeric_limits<int>::max();
        int label_min = s;
        for (int i = 0; i < n; i++)
        {
            d_min = numeric_limits<int>::max();
            for (auto& node : nodes)
            {
                if (marked[node.first])
                {
                    continue;
                }
                if (d[node.first] <= d_min)
                {
                    d_min = d[node.first];
                    label_min = node.first;
                }
            }
            for (Node* adjNode : nodes[label_min]->adjNodes)
            {
                if (!marked[adjNode->label] && d[adjNode->label] >= d[label_min] + 1)
                {
                    d[adjNode->label] = d[label_min] + 1;
                    p[adjNode->label] = label_min;
                }
            }
            marked[label_min] = true;      
        }
        return {d, p};
    }
    map<vector<int>, int> APSP() // all pairs shortest path
    {
        /*
        Returns a map of distances between any two nodes of the graph
        */
        map<vector<int>, int> D;
        for (auto& node1 : nodes)
        {
            for (auto& node2 : nodes)
            {
                if (node1 == node2)
                {
                    D[{node1.first, node2.first}] = 0;
                    continue;
                }
                D[{node1.first, node2.first}] = numeric_limits<int>::max();
            }
        }
        bool flag = false;
        for (auto& node : nodes)
        {
            if (flag)
            {
                break;
            }
            map<int, int> d = Dijkstra(node.first).first;
            int changes = 0;
            for (auto& dist : d)
            {
                if (D[{node.first, dist.first}] > dist.second) 
                {
                    D[{node.first, dist.first}] = min(dist.second, D[{node.first, dist.first}]);
                    D[{dist.first, node.first}] = min(dist.second, D[{dist.first, node.first}]);
                    changes++;
                }  
            }
            flag = true ? changes == 0 : false;
        }
        return D;
    }
};

int main()
{
    // test code
    Graph graph({0, 1, 2, 3}, {{3, 1}, {0, 2}, {1, 3}, {2, 0}});
    graph.addEdge(0, 2);
    graph.addNode({0, 2, 3}, 8);
    graph.addNode({8, 3}, 9);
    graph.printGraph();

    cout << endl;

    Graph tree = graph.DFS(1);
    tree.printGraph();

    cout << endl;

    map<int, int> d = graph.Dijkstra(1).first;
    map<int, int> p = graph.Dijkstra(1).second;

    map<vector<int>, int> D = graph.APSP();

    for (auto &node1 : graph.nodes)
    {
        for (auto &node2 : graph.nodes)
        {
            cout << node1.first << ", " << node2.first << ": " << D[{node1.first, node2.first}] << endl;
        }
    }

    for (auto& dist : d)
    {
        cout << dist.first << ": " << dist.second << endl;
    }
    cout << endl;
    for (auto& prev : p)
    {
        cout << prev.first << ": " << prev.second << endl;
    }
}