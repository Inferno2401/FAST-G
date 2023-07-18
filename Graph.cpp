#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <limits>
#include <set>

using namespace std;

class Graph
{
public:
    // struct for node
    struct Node
    {
        int label;
        std::vector<Node *> adjNodes;

        bool operator==(const Node other) const
        {
            return (label == other.label && adjNodes == other.adjNodes);
        }
        Node &operator=(const Node &other)
        {
            label = other.label;
            adjNodes = other.adjNodes;
            return *this;
        }
    };

    int n;                              // number of nodes
    int n_total;                        // number of nodes added in total
    std::map<int, Node *> nodes;        // adjacency list for graph
    std::map<std::set<int>, int> edges; // list of edges of graph

    // constructors
    Graph()
    {
        n = 0;
        n_total = 0;
    }
    Graph(std::vector<int> labels, std::vector<std::vector<int>> adj_lists, std::vector<std::vector<int>> weights = std::vector<std::vector<int>>())
    {
        n = 0;
        n_total = 0;
        initializeGraph(adj_lists, labels, weights);
        printGraph();
    }

    // destructor
    ~Graph()
    {
        for (auto &node : nodes)
        {
            delete node.second;
        }
    }

    // public methods
    void initializeGraph(std::vector<std::vector<int>> adj_lists, std::vector<int> new_labels = std::vector<int>(), std::vector<std::vector<int>> weights = std::vector<std::vector<int>>()) // initialize graph
    {
        bool is_empty = new_labels.empty();
        n = adj_lists.size();
        for (int i = 0; i < n; i++)
        {
            Node *node = new Node();
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
                if (!weights.empty())
                {
                    edges[std::set<int>{nodes[i]->label, nodes[adj_lists[i][j]]->label}] = weights[i][j];
                }
                else
                {
                    edges[std::set<int>{nodes[i]->label, nodes[adj_lists[i][j]]->label}] = 1;
                }
            }
        }
    }
    void printGraph() // print graph
    {
        for (auto &node : nodes)
        {
            std::cout << node.first << ": ";
            for (Node *adj_node : node.second->adjNodes)
            {
                std::cout << adj_node->label << " ";
            }
            std::cout << std::endl;
        }
    }
    void addNode(std::vector<int> labels = std::vector<int>(), int new_label = -1, std::vector<int> weights = std::vector<int>()) // add node using adjacent nodes
    {
        Node *new_node = new Node();
        if (new_label == -1)
            new_node->label = n_total;
        else
            new_node->label = new_label;
        for (int i = 0; i < labels.size(); i++)
        {
            nodes[labels[i]]->adjNodes.push_back(new_node);
            new_node->adjNodes.push_back(nodes[labels[i]]);
            if (!weights.empty())
            {
                edges[std::set<int>{new_node->label, labels[i]}] = weights[i];
            }
            else
            {
                edges[std::set<int>{new_node->label, labels[i]}] = 1;
            }
        }
        nodes[new_node->label] = new_node;
        n++;
        n_total++;
    }
    void addNode(Node *node) // add node using Node*
    {
        nodes[node->label] = node;
        n++;
        n_total++;
    }
    void deleteNode(int label) // delete node
    {
        for (Node *node : nodes[label]->adjNodes)
        {
            node->adjNodes.erase(remove(node->adjNodes.begin(), node->adjNodes.end(), nodes[label]), node->adjNodes.end());
        }
        for (auto edge = edges.begin(); edge != edges.end();)
        {
            if (edge->first.find(label) != edge->first.end())
            {
                edges.erase(edge);
            }
        }
        delete nodes[label];
        nodes.erase(label);
        n--;
    }
    void addEdge(int label1, int label2, int weight = 1) // join two nodes
    {
        nodes[label1]->adjNodes.push_back(nodes[label2]);
        nodes[label2]->adjNodes.push_back(nodes[label1]);
        edges[std::set<int>{label1, label2}] = weight;
    }
    void deleteEdge(int label1, int label2)
    {
        nodes[label1]->adjNodes.erase(remove(nodes[label1]->adjNodes.begin(), nodes[label1]->adjNodes.end(), nodes[label2]), nodes[label1]->adjNodes.end());
        nodes[label2]->adjNodes.erase(remove(nodes[label2]->adjNodes.begin(), nodes[label2]->adjNodes.end(), nodes[label1]), nodes[label2]->adjNodes.end());
        edges.erase(edges.find(std::set<int>{label1, label2}));
    }
    void joinGraph(Graph tree, int label1, int label2, int weight = 1)
    {
        for (auto& node : tree.nodes)
        {
            nodes[node.first] = node.second;
        }
        addEdge(label1, label2, weight);
        n += tree.n;
        n_total += tree.n_total;
    }
    Graph BFS(int root) // breadth-first search
    {
        /*
        Returns a Graph object that is in the form of a tree, i.e, each node has
        only a parent and children nodes.
        */
        Graph tree;
        Node *new_root = new Node();
        new_root->label = root;
        new_root->adjNodes = {};
        std::map<int, int> discovered;
        discovered[root] = 1;

        std::queue<Node *> order;
        std::queue<Node *> original_nodes;
        order.push(new_root);
        original_nodes.push(nodes[root]);

        tree.nodes[new_root->label] = new_root;

        while (!order.empty())
        {
            Node *node = order.front();
            Node *original_node = original_nodes.front();
            order.pop();
            original_nodes.pop();
            for (Node *adjNode : original_node->adjNodes)
            {
                if (discovered[adjNode->label] == 0)
                {
                    discovered[adjNode->label] = 1;
                    Node *temp_node = new Node();
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
        Node *new_root = new Node();
        new_root->label = root;
        new_root->adjNodes = {};
        std::map<int, int> discovered;
        discovered[root] = 1;

        std::stack<Node *> order;
        std::stack<Node *> original_nodes;
        order.push(new_root);
        original_nodes.push(nodes[root]);

        tree.nodes[new_root->label] = new_root;

        while (!order.empty())
        {
            Node *node = order.top();
            Node *original_node = original_nodes.top();
            order.pop();
            original_nodes.pop();
            for (Node *adjNode : original_node->adjNodes)
            {
                if (discovered[adjNode->label] == 0)
                {
                    discovered[adjNode->label] = 1;
                    Node *temp_node = new Node();
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
    std::pair<std::map<int, int>, std::map<int, int>> Dijkstra(int s) // Dijkstra's algorithm
    {
        /*
        Returns a pair with a map of distances of nodes from root node and a map
        of previous nodes for the shortest path from the root node
        */
        std::map<int, int> d;
        std::map<int, int> p;
        std::map<int, bool> marked;

        for (auto &node : nodes)
        {
            d[node.first] = std::numeric_limits<int>::max();
        }
        d[s] = 0;
        int d_min = std::numeric_limits<int>::max();
        int label_min = s;
        for (int i = 0; i < n; i++)
        {
            d_min = std::numeric_limits<int>::max();
            for (auto &node : nodes)
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
            for (Node *node : nodes[label_min]->adjNodes)
            {
                if (!marked[node->label] && d[node->label] >= d[label_min] + edges[std::set<int>{label_min, node->label}])
                {
                    d[node->label] = d[label_min] + edges[std::set<int>{label_min, node->label}];
                    p[node->label] = label_min;
                }
            }
            marked[label_min] = true;
        }
        return {d, p};
    }
    std::map<std::vector<int>, int> APSP() // all pairs shortest path
    {
        /*
        Returns a map of distances between any two nodes of the graph
        */
        std::map<std::vector<int>, int> D;
        for (auto &node1 : nodes)
        {
            for (auto &node2 : nodes)
            {
                if (node1 == node2)
                {
                    D[{node1.first, node2.first}] = 0;
                    continue;
                }
                D[{node1.first, node2.first}] = std::numeric_limits<int>::max();
            }
        }
        bool flag = false;
        for (auto &node : nodes)
        {
            if (flag)
            {
                break;
            }
            std::map<int, int> d = Dijkstra(node.first).first;
            int changes = 0;
            for (auto &dist : d)
            {
                if (D[{node.first, dist.first}] > dist.second)
                {
                    D[{node.first, dist.first}] = dist.second;
                    D[{dist.first, node.first}] = dist.second;
                    changes++;
                }
            }
            flag = true ? changes == 0 : false;
        }
        return D;
    }
    Graph Kruskal()
    {
        int substrees = n;
        std::map<int, Graph> trees;
        std::map<int, int> tree_id;
        for (auto& node : nodes)
        {
            Graph tree;
            tree.addNode(std::vector<int>(), node.first);
            trees[node.first] = tree;
            tree_id[node.first] = node.first;
        }
        std::vector<std::pair<std::set<int>, int>> sorted_edges;
        for (auto &edge : edges)
        {
            sorted_edges.emplace_back(edge.first, edge.second);
        }
        std::sort(sorted_edges.begin(), sorted_edges.end(), [](const auto &a, const auto &b)
                  { return a.second < b.second; });
        for (std::pair<std::set<int>, int> edge : sorted_edges)
        {
            int label1 = *(edge.first.begin());
            int label2 = *(++edge.first.begin());
            if (tree_id[label1] != tree_id[label2])
            {
                Graph tree1 = trees[tree_id[label1]];
                Graph tree2 = trees[tree_id[label2]];
                tree1.joinGraph(tree2, label1, label2, edge.second);
                trees.erase(trees.find(tree_id[label2]));
                tree_id[label2] = tree_id[label1];
            }
        }
        Graph spanning_tree = trees.begin()->second;
        return spanning_tree;
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