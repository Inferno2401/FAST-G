#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
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
    Graph BFS (Node* root) // breadth-first search
    {
        /*
        Returns a Graph object that is in the form of a tree, i.e, each node has
        only a parent and children nodes.
        */
        Graph tree;
        Node* new_root = new Node();
        new_root->label = root->label;
        new_root->adjNodes = {};
        map<Node*, int> discovered;
        discovered[root] = 1;

        queue<Node*> order;
        queue<Node*> original_nodes;
        order.push(new_root);
        original_nodes.push(root);

        tree.nodes[new_root->label] = new_root;

        while (!order.empty())
        {
            Node* node = order.front();
            Node* original_node = original_nodes.front();
            order.pop();
            original_nodes.pop();
            for (Node* adjNode : original_node->adjNodes)
            {
                if (discovered[adjNode] == 0)
                {
                    discovered[adjNode] = 1;
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
    Graph DFS(Node* root) // depth-first search
    {
        /*
        Returns a Graph object that is in the form of a tree, i.e, each node has
        only a parent and children nodes.
        */
        Graph tree;
        Node* new_root = new Node();
        new_root->label = root->label;
        new_root->adjNodes = {};
        map<Node*, int> discovered;
        discovered[root] = 1;

        stack<Node*> order;
        stack<Node*> original_nodes;
        order.push(new_root);
        original_nodes.push(root);

        tree.nodes[new_root->label] = new_root;

        while (!order.empty())
        {
            Node* node = order.top();
            Node* original_node = original_nodes.top();
            order.pop();
            original_nodes.pop();
            for (Node* adjNode : original_node->adjNodes)
            {
                if (discovered[adjNode] == 0)
                {
                    discovered[adjNode] = 1;
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
    /*vector<Node> Dijkstra() // Dijkstra's algorithm 
    {

    }
    vector<Node> APSP() // all pairs shortest path
    {

    }*/
};