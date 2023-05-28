#include <iostream>
#include <vector>

class graphs
{
public:
    void addEdge(int u, int v);
    void addVertex();
    void removeEdge(int u, int v);
    void removeVertex(int u);
    bool checkAdj(int u, int v);
    void printGraph();
    graphs();
    graphs(const graphs &G);
    graphs(int u);

private:
    std::vector<std::vector<int> *> a;
};
//basic graph class with functionalities of adding and reomving edges, and checking whether two vertices are adjacent or not. 
// basic exception handling is added such as checking whether a vertex exists before deleting it. Same goes for an edge.


graphs::graphs(int u) // default constructor
{
    for (int i = 1; i <= u; i++)
    {
        std::vector<int> *v = new std::vector<int>;
        a.push_back(v);
    }
}
graphs::graphs(const graphs &G) // copy constructor
{
    a = G.a;
    for (int i = 0; i < G.a.size(); i++)
        a[i] = G.a[i];
}
void graphs::printGraph() // basic graph printing
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < (*a[i]).size(); j++)
        {
            std::cout << (*a[i])[j];
        }
        std::cout << std::endl;
    }
}
bool graphs::checkAdj(int u, int v) // function to check adjacent edges 
{
    if (u>=a.size()||v>=a.size())
    {
        std::cout<<"Vertices may not exist";
        return false;
    }
    if (u==v)
    {
        std::cout<<"Same vertex has been entered";
        return false;
    }

    bool b = false;
    for (int i = 0; i < (*a[u]).size(); i++)
    {
        if ((*a[u])[i] == v)
            b = true;
    }
    return b;
}

void graphs::addEdge(int u, int v)
{
    if (checkAdj(u, v) == true)
        return;
    (*a[u]).push_back(v);
    (*a[v]).push_back(u);
}

void graphs::addVertex()
{
    std::vector<int> *w = new std::vector<int>;
    a.push_back(w);
}
void graphs::removeEdge(int u, int v)
{
    if(checkAdj(u,v)==false)
    {
        std::cout<<"Edge doesn't exist";
        return;
    }
    for (int j = 0; j < (*a[u]).size(); j++)
    {
        if((*a[u])[j]==v)
        (*a[u]).erase((*a[u]).begin()+j);
        break;
    }
    for (int j = 0; j < (*a[v]).size(); j++)
    {
        if((*a[v])[j]==u)
        (*a[v]).erase((*a[v]).begin()+j);
        break;
    }
}
void graphs::removeVertex(int u)
{
    if (u >= a.size())
    {
        std::cout << "Vertex doesn't exist";
        return;
    }
    for (int i = 0; i < a.size(); i++)
    {
        if (i == u)
        {
            (*a[i]).clear();
        }
        else
        {
            for (int j = 0; j < (*a[i]).size(); j++)
            {
                if ((*a[i])[j] == u)
                {
                    (*a[i]).erase((*a[i]).begin() + j);
                    break;
                }
            }
        }
        a.erase(a.begin()+u);
    }
}
