#include<bits/stdc++.h>
#include<algorithm>
#include<vector>
using namespace std;
int n,m;
class Graph{
    public:
      vector<vector<int>> adj_list;
      
      
       //adding undirect edges between 2 nodes
     void add_edge(int x, int y){
       adj_list[x].push_back(y);
       adj_list[y].push_back(x);
     } 
     
     // removing an edge between nodes.
     void remove_edge(int x, int y){
        
     
     }
     // getting all neighbours.
      void get_neighbours(int x){
          for(auto v:adj_list[x]){
            cout<<v<<" ";
          }
          cout<<endl;
      }
      

};

int main(){
    
      cin>>n>>m; // n:# of nodes.  m: # of edges
      
    return 0;
}