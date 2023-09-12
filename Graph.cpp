#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <limits>
#include <set>
#include <cmath>

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

    int heuristic(int s, int t) // heuristic function for A* search algorithm
    {
        // Assuming Euclidean distance as heuristic
        int dx = abs(nodes[s]->label - nodes[t]->label);
        int dy = abs(nodes[s]->label - nodes[t]->label);
        return (int)(sqrt(dx * dx + dy * dy));
    }

    std::pair<std::map<int, int>, std::map<int, int>> AStar(int s, int t) // A* search algorithm
    {
        std::map<int, int> g;
        std::map<int, int> f;
        std::map<int, int> p;
        std::map<int, bool> marked;

        for (auto &node : nodes)
        {
            g[node.first] = std::numeric_limits<int>::max();
            f[node.first] = std::numeric_limits<int>::max();
        }
        g[s] = 0;
        f[s] = heuristic(s, t);

        while (!marked[t])
        {
            int label_min = -1;
            int f_min = std::numeric_limits<int>::max();
            for (auto &node : nodes)
            {
                if (!marked[node.first] && f[node.first] < f_min)
                {
                    f_min = f[node.first];
                    label_min = node.first;
                }
            }
            if (label_min == -1)
            {
                break;
            }
            marked[label_min] = true;
            for (Node *node : nodes[label_min]->adjNodes)
            {
                if (!marked[node->label] && g[node->label] > g[label_min] + edges[std::set<int>{label_min, node->label}])
                {
                    g[node->label] = g[label_min] + edges[std::set<int>{label_min, node->label}];
                    f[node->label] = g[node->label] + heuristic(node->label, t);
                    p[node->label] = label_min;
                }
            }
        }
        return {g, p};
    }
    
    std::map<std::vector<int>, int> FloydWarshall() // Floyd-Warshall algorithm
    {
        std::map<std::vector<int>, int> D = APSP();
        for (auto &k : nodes)
        {
            for (auto &i : nodes)
            {
                for (auto &j : nodes)
                {
                    if (D[{i.first, k.first}] != std::numeric_limits<int>::max() && D[{k.first, j.first}] != std::numeric_limits<int>::max())
                    {
                        D[{i.first, j.first}] = std::min(D[{i.first, j.first}], D[{i.first, k.first}] + D[{k.first, j.first}]);
                    }
                }
            }
        }
        return D;
    }

    int EdmondsKarp(int s, int t) // Edmonds-Karp algorithm
    {
        std::map<std::set<int>, int> flow;
        for (auto &edge : edges)
        {
            flow[edge.first] = 0;
        }
        int max_flow = 0;
        while (true)
        {
            std::map<int, int> p;
            std::map<int, int> M;
            p[s] = s;
            M[s] = std::numeric_limits<int>::max();
            std::queue<int> Q;
            Q.push(s);
            while (!Q.empty())
            {
                int u = Q.front();
                Q.pop();
                for (Node *v : nodes[u]->adjNodes)
                {
                    if (edges[std::set<int>{u, v->label}] > flow[std::set<int>{u, v->label}] && p.find(v->label) == p.end())
                    {
                        p[v->label] = u;
                        M[v->label] = std::min(M[u], edges[std::set<int>{u, v->label}] - flow[std::set<int>{u, v->label}]);
                        if (v->label != t)
                        {
                            Q.push(v->label);
                        }
                        else
                        {
                            while (p[v->label] != v->label)
                            {
                                u = p[v->label];
                                flow[std::set<int>{u, v->label}] += M[t];
                                flow[std::set<int>{v->label, u}] -= M[t];
                                v = nodes[u];
                            }
                            max_flow += M[t];
                            break;
                        }
                    }
                }
            }
            if (M.find(t) == M.end())
            {
                break;
            }
        }
        return max_flow;
    }

    int MinCostFlow(int s, int t) // Minimum-cost flow algorithm
    {
        std::map<std::set<int>, int> flow;
        std::map<std::set<int>, int> cost;
        for (auto &edge : edges)
        {
            flow[edge.first] = 0;
            cost[edge.first] = 0;
        }
        int min_cost_flow = 0;
        while (true)
        {
            std::map<int, int> p;
            std::map<int, int> M;
            p[s] = s;
            M[s] = std::numeric_limits<int>::max();
            std::queue<int> Q;
            Q.push(s);
            while (!Q.empty())
            {
                int u = Q.front();
                Q.pop();
                for (Node *v : nodes[u]->adjNodes)
                {
                    if (edges[std::set<int>{u, v->label}] > flow[std::set<int>{u, v->label}] && p.find(v->label) == p.end())
                    {
                        p[v->label] = u;
                        M[v->label] = std::min(M[u], edges[std::set<int>{u, v->label}] - flow[std::set<int>{u, v->label}]);
                        if (v->label != t)
                        {
                            Q.push(v->label);
                        }
                        else
                        {
                            while (p[v->label] != v->label)
                            {
                                u = p[v->label];
                                flow[std::set<int>{u, v->label}] += M[t];
                                flow[std::set<int>{v->label, u}] -= M[t];
                                cost[std::set<int>{u, v->label}] += M[t];
                                v = nodes[u];
                            }
                            min_cost_flow += cost[std::set<int>{u, v->label}];
                            break;
                        }
                    }
                }
            }
            if (M.find(t) == M.end())
            {
                break;
            }
        }
        return min_cost_flow;
    }

    std::pair<std::map<int, int>, std::map<int, int>> PerfectMatching() // Perfect Matching algorithm
    {
        std::map<int, int> match;
        std::map<int, int> p;
        for (auto &node : nodes)
        {
            match[node.first] = -1;
        }
        for (auto &node : nodes)
        {
            if (match[node.first] == -1)
            {
                for (Node *adjNode : node.second->adjNodes)
                {
                    if (match[adjNode->label] == -1)
                    {
                        match[node.first] = adjNode->label;
                        match[adjNode->label] = node.first;
                        break;
                    }
                }
            }
        }
        return {match, p};
    }

    std::vector<int> ApproxVertexCover() // Approximation algorithm for Vertex Cover problem
    {
        std::vector<int> vertex_cover;
        std::map<std::set<int>, int> temp_edges = edges;

        while (!temp_edges.empty())
        {
            std::set<int> edge = temp_edges.begin()->first;
            vertex_cover.push_back(*edge.begin());
            vertex_cover.push_back(*(++edge.begin()));

            for (auto it = temp_edges.begin(); it != temp_edges.end();)
            {
                if (it->first.find(*edge.begin()) != it->first.end() || it->first.find(*(++edge.begin())) != it->first.end())
                {
                    it = temp_edges.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
        return vertex_cover;
    }  
};