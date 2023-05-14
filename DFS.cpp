#include<bits/stdc++.h>
using namespace std;

/*
5 5
S . # . .    // #'s are taken as walls
. . . . . 
# # # . . 
. . # . . 
. . # . . 
*/
int n,m;
vector<string> arr;
vector<vector<int>> vis;

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

bool valid (int x,int y){
    if(x<0||x>=n||y<0||y>=m||arr[x][y]=='#') return 0;
    return  1;
}
void dfs(int x, int y){
   vis[x][y]=1;
   for(int k=0;k<4;k++){
    int nx=x+dx[k], ny = y+dy[k];
     if(valid(nx,ny) && !vis[nx][ny]){
        dfs(nx,ny);
     }
   }
}

int main(){
    
    cin>>n>>m;
    arr.resize(n);
    vis.resize(n);
    int x,y;
    for(int i=0;i<n;i++){
          vis[i].assign(m,0);
        for(int j=0;j<m;j++){
            char ch;
            cin>>ch;
            arr[i]+=ch;
            if(ch=='S'){
                x=i,y=j;
            }
        }
    }
    dfs(x,y);
     int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(arr[i][j]=='.' && vis[i][j]==1){
                ans++;
            }
        }
    }
      cout<<ans<<endl;
   return 0;

}