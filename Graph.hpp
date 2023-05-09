#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
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
    vector<int> labels; // list of labels of current nodes

    // default constructor
    Graph ()
    {
        n = 0;
        n_total = 0;
    }

    Graph (vector<vector<int>> adj_lists)
    {
        n = 0;
        n_total = 0;
        initializeGraph(adj_lists);
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
    void initializeGraph(vector<vector<int>> adj_lists, vector<int> new_labels = vector<int>()) // initialize graph
    {
        bool is_empty = labels.empty();
        n = adj_lists.size();
        for (int i = 0; i < n; i++)
        {
            Node* node = new Node();
            if (is_empty)
                node->label = n_total++;
            else
                node->label = new_labels[i];
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
    void deleteNode(int label) // delete node
    {   
        for (Node* node : nodes[label]->adjNodes)
        {
            vector<Node*> adj_nodes = node->adjNodes;
            nodes.erase(remove_if(
                nodes.begin(), 
                nodes.end(), 
                [label](const Node* node) {
                    return node->label == label; 
                }
            ), nodes.end());
        }
        delete nodes[label];
        nodes.erase(label);
    }
    void printGraph() // print graph
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
    void addNode(vector<int> labels = vector<int>(), int new_label = -1) // add node
    {
        Node* new_node = new Node();
        if (new_label == -1)
            new_node->label = n_total++;
        else
            new_node->label = new_label;
        for (auto& node : nodes)
        {
            for (int label : labels)
            {
                if (node.first == label)
                {
                    new_node->adjNodes.push_back(nodes[label]);
                }
            }
        }
        nodes[new_node->label] = new_node;
    }
    void addEdge(int label1, int label2) // join two nodes
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
            if (flag1 || flag2)
            {
                break;
            }
        }
    }
    vector<Node> BFS(Node root) // breadth-first search
    {
        Node* root_node = new Node();
        root_node->label = root.label;
        root_node->adjNodes = root.adjNodes;
        vector<vector<Node>> layers;
        Graph tree;
        tree.addNode(vector<int>(), root.label);
        layers.push_back(vector<Node>());
        layers[0].push_back(root);
        map<Node*, bool> discovered;
        discovered[root_node] = true;
        int i = 0;
        while(!layers[i].empty())
        {

        }

        vector<vector<Node>> layers;
        Graph tree;
        tree.addNode(vector<int>(), root.label);
        layers.push_back(vector<Node>());
        layers[0].push_back(root);
        map<Node, bool> discovered;
        discovered[root] = true;
        int i = 0;
        while (!layers[i].empty())
        {
            for (int j = 0; j < layers[i].size(); j++)
            {
                for (int k = 0; k < layers[i][j].adj.size(); k++)
                {
                    int label = layers[i][j].adj[k];

                    for (int l = 0; l < nodes.size(); l++)
                    {
                        if (label == nodes[l].label)
                        {
                            if (discovered[nodes[i]] == false)
                            {
                                discovered[nodes[i]] == true;
                                vector<int> temp;
                                temp.push_back(label);
                                tree.addNode(vector<int>(label))
                            }
                        }
                    }
                }
            }
        }
    }
    vector<Node> DFS() // depth-first search
    {

    }
    vector<Node> Dijkstra() // Dijkstra's algorithm 
    {

    }
    vector<Node> APSP() // all pairs shortest path
    {

    }

};



int main()
{
    Graph graph;

}