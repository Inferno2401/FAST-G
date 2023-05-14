#include<bits/stdc++.h>
using namespace std;
#define F first 
#define S second 

using ii = pair<int,int>;
/*
6 6
6 6
S.#... 
...... 
####.#
E.##.#
..#..#
#....#
*/
int n,m;
vector<string> arr;
ii par[1000][1000];
int dist[1010][1010]; // it's our preference

int dx[] = {0,1,0,-1}; // in each step it can go either up/down/right/left.
int dy[] = {1,0,-1,0};
bool inside(int x,int y){
    if(x<0||x>=n||y<0||y>=m||arr[x][y]=='#') return 0;
    return 1;   
}


void bfs(ii st){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dist[i][j]=1e6;
           
        }
       
    }
    dist[st.F][st.S]=0; // taking distance from st.(st as a reference)
    queue<ii> q;
    q.push(st);
    while(!q.empty()){
        ii cur = q.front();
        q.pop();
        int curd = dist[cur.F][cur.S]; //current distance
        for(int k=0;k<4;k++){
            if(!inside(cur.F+dx[k], cur.S+dy[k])) continue;
            ii neigh = {cur.F+dx[k],cur.S+dy[k]};
            if(dist[neigh.F][neigh.S]>curd+1){  // means unvisited. beocz initially all are intialized to 1e9;
            dist[neigh.F][neigh.S]=curd+1;
            par[neigh.F][neigh.S] =cur;  // parent. storing this becoz it will be useful in getting path. 
                q.push(neigh);
                
            }
        }
    }
}

 int main(){
    cin>>n>>m;
    arr.resize(n);
    ii st,en;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        for(int j=0;j<m;j++)
        if(arr[i][j]=='S'){
            st= {i,j};
        }
        else if(arr[i][j]=='E'){
            en = {i,j};
        }
    }
    bfs(st);
    cout<<dist[en.F][en.S]<<endl;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<dist[i][j]<<"\t";  
        }
        cout<<endl;
    }
    cout<<endl;
    ii temp =en;
    vector<ii> path;
    while(temp!=st){  // for printing the path which it follows.
        path.push_back(temp);
        temp = par[temp.F][temp.S];
    }
    path.push_back(st);
    reverse(path.begin(),path.end());
    cout<<"path which it followed"<<endl;
    for(auto v:path){
        cout<<v.F<<" "<<v.S<<endl;
    }
    return 0;
 }