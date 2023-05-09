#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

/*bool isPresent(stack<Graph::Node> S, Graph::Node n)
{
    stack<Graph::Node> temp = S;
    while (!temp.empty()) 
    {
        if (temp.top().label == n.label) 
        {
            return true;
        }
        temp.pop();
    }
    return false;
}

bool isPresent(queue<Graph::Node> S, Graph::Node n)
{
    queue<Graph::Node> temp = S;
    while (!temp.empty()) 
    {
        if (temp.front().label == n.label) 
        {
            return true;
        }
        temp.pop();
    }
    return false;
}*/

class Graph 
{
    public:
    // struct for node
    struct Node
    {
        int label;
        vector<int> adj;
    };

    int n; // number of nodes
    int n_total; // number of nodes added in total
    vector<Node> nodes; // adjacency list for graph

    // default constructor
    Graph()
    {
        n = 0;
        n_total = 0;
    }

    // public methods
    void inputGraph(int label, vector<int> adj_list) // input graph
    {
        for (int i = 0; i < n; i++)
        {
            Node node;
            node.label = n_total++;
            node.adj = adj_list;
            nodes.push_back(node);
        }
    }
    void deleteNode(int label) // delete node
    {
        for(int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i].label = label)
            {
                nodes.erase(remove(nodes.begin(), nodes.end(), nodes[i]), nodes.end());
                for (int j = 0; j < nodes.size(); j++)
                {
                    nodes[j].adj.erase(remove(nodes[j].adj.begin(), nodes[j].adj.end(), label), nodes[j].adj.end());
                }
                break;
            }
        }
    }
    void printGraph() // print graph
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << nodes[i].label << ": ";
            for (int adj : nodes[i].adj)
            {
                cout << adj << " ";
            }
            cout << endl;
        }
    }
    void addNode(vector<int> labels) // add node
    {
        Node node;
        node.adj = labels;
        node.label = n_total++;
        for (int i = 0; i < nodes.size(); i++)
        {
            for (int label : labels)
            {
                if (nodes[i].label == label)
                {
                    nodes[i].adj.push_back(label);
                }
            }
        }
        nodes.push_back(node);
    }
    void addEdge(int label1, int label2) // join two nodes
    {
        bool flag1 = true, flag2 = true;
        for (int i = 0; i < nodes.size(); i++)
        {
            if (flag1 && nodes[i].label == label1)
            {
                nodes[i].adj.push_back(label2);
                flag1 = !flag1;
            }
            if (flag2 && nodes[i].label == label2)
            {
                nodes[i].adj.push_back(label1);
                flag2 = !flag2;
            }
            if (flag1 || flag2)
            {
                break;
            }
        }
    }
    vector<Node> BFS(Node u) // breadth-first search
    {
        
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