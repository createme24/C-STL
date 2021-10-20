#include<bits/stdc++.h>
using namespace std;

void dfs(int node, int parent, vector<int> &vis, vector<int> &tin, vector<int> &low, int &timer, vector<int> adj[]){
    
    //mark the node as visited     
    vis[node] = 1;
    //everytime a node is visited in dfs, the timer gets increased and
    //time of insertion and lowest of node gets updated
    tin[node] = low[node] = timer++;
    
    for(auto it : adj[node]){
        //if the adjacent element is parent, we'll not do a dfs call because we know
        // that it will go backward
        if(it == parent) continue;
        
        if(!vis[it]){
            /* call dfs for adjacent nodes, now when dfs will be called, time of insertion 
            will increase and low of node will increase */
            dfs(it, node, vis, tin, low, timer, adj);
            //low of the node will be updated whose dfs is completed
            //it will be updated only if the adjacent node have lesser low
            low[node] = min(low[node], low[it]);
            
            //if this condition follows that does mean that the node is visited by some other 
            //component and not this component, therefore it is a bridge
            if(low[it]>tin[node]){
                cout<<node<<" "<<it<<endl;
            }
         }
         //else if the node is already visited, then just update the low of the node
         /*this does mean if the node is previously visited, then there is possibility that
         the time of insertion would be lowest for that , so update it */
         else{
            low[node] = min(low[node], tin[it]);
        }
    }
}

int main(){
    
    //create a vector
    int n, m;
    cin>>n>>m;
    vector<int> adj[n];
    for(int i=0; i<m; i++){
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    //create time of insertion for the given node
    //create lowest time for the given node
    //visited array
    
    vector<int> tin(n, -1);
    vector<int> low(n, -1);
    vector<int> vis(n, 0);
    
    int timer=0;
    
    //call dfs for the whole graph, i.e all the components
    for(int i=0; i<n; i++){
        if(!vis[i]){
            dfs(i, -1, vis, tin, low, timer, adj);
        }
    }
    return 0;
}
