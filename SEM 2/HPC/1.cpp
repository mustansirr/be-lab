/*
Design and implement Parallel Breadth First Search and Depth First Search
based on existing algorithms using OpenMP. Use a Tree or an undirected
graph for BFS and DFS .
*/
#include <omp.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class DFS {
    public:
    void recursiveDfs(int node, vector<int> adj[], int visited[], vector<int> &res) {
        visited[node] = 1;
        res.push_back(node);
        for(auto it : adj[node]) {
            if(!visited[it]) {
                recursiveDfs(it, adj, visited, res);
            }
        }
    }
    vector<int> dfs(int n, vector<int> adj[]) {
        int visited[n];
        for(int i = 0; i < n; i++) visited[i] = 0;
        int start = 0;
        vector<int> res;
        recursiveDfs(start, adj, visited, res);
        return res;
    }
};

class BFS {
    public:
    vector<int> bfs(int n, vector<int> adj[]) {
        vector<int> visited(n, 0);
        visited[0] = 1;
        queue<int> q;
        q.push(0);
        vector<int> res;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            res.push_back(node);
            for(auto it : adj[node]) {
                if(!visited[it]) {
                    visited[it] = 1;
                    q.push(it);
                }
            }
        }
        return res;
    }
};

int main() {
    BFS c1;
    DFS c2;
    int n = 5;
    vector<int> adj[6];

    adj[0] = {1, 2};
    adj[1] = {0, 3};                
    adj[2] = {0, 4};                
    adj[3] = {1};                
    adj[4] = {2};                   

    vector<int> res1 = c1.bfs(n, adj);
    vector<int> res2 = c2.dfs(n, adj);
    cout << "BFS" << endl;
    for(int node : res1)
        cout << node << " ";
        cout << '\n';
    cout << "DFS" << endl;
    for(int node : res2)
        cout << node << " ";
    return 0;
}