#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>
#include "Graph.hpp"

using namespace std;

int main()
{
    cout << "  ______       _____ _______      _____ \n";
    cout << " |  ____/\\    / ____|__   __|    / ____|\n";
    cout << " | |__ /  \\  | (___    | |______| |  __ \n";
    cout << " |  __/ /\\ \\  \\___ \\   | |______| | |_ |\n";
    cout << " | | / ____ \\ ____) |  | |      | |__| |\n";
    cout << " |_|/_/    \\_\\_____/   |_|       \\_____|\n\n";
    cout << " Created by - SANSKAR SHAURYA (22B0985)\n\n";
    cout << "Welcome to the Bipartite Graph Perfect Matching Solver!!\nThis program takes in input of two sets lets say A and B and then matches them according to their preferences and outputs the final match.\nEnter the number of elements in both sets:" ;
    DirectedGraph a;
    int n;
    cin >> n;
    for (int i = 1; i <= 2 * n; i++)
        a.add_node(i);
    cout << "Add the edges in this bipartite graph, first enter the node number of the set A that you want to connect, then the node number of the set B: " << '\n'
         << "Enter 0 when you are finished"<<'\n';
    while (true)
    {
        int first, second;
        cout << "Node number in set A: ";
        cin >> first;
        if (first == 0) break;
        cout << "Node number in set B: ";
        cin >> second;
        if (second == 0) break;
        a.add_edge(first,n+second,1);
    }
    a.perfectMatching(n);
}
