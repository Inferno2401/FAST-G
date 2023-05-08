#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

bool isPresent(stack<Graph::Node> S, Graph::Node n)
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
}

class Graph 
{
    public:
    // default constructor
    Graph();

    // struct for node
    struct Node
    {
        int label;
        vector<Node> adj;
    };

    //class variables
    vector<Node> explored;
    stack<Node> explored_stack; // for DFS
    queue<Node> explored_queue; // for BFS

    // public methods
    vector<Node> BFS(Node u) // breadth-first search
    {
        explored_queue.push(u);
        
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