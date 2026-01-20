/*
Parallel Breadth First Search and Depth First Search using OpenMP
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

        // Parallelize the recursive calls
        #pragma omp parallel for
        for (size_t i = 0; i < adj[node].size(); i++) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                #pragma omp task // Create a parallel task for each neighbor
                recursiveDfs(neighbor, adj, visited, res);
            }
        }
    }

    vector<int> dfs(int n, vector<int> adj[]) {
        int visited[n];
        for (int i = 0; i < n; i++) visited[i] = 0;
        vector<int> res;

        // Start the parallel region
        #pragma omp parallel
        {
            #pragma omp single // Ensure only one thread starts the DFS
            {
                recursiveDfs(0, adj, visited, res);
            }
        }
        return res;
    }
};

class BFS {
public:
    vector<int> bfs(int n, vector<int> adj[]) {
        vector<int> visited(n, 0);
        visited[0] = 1;
        vector<int> res;

        // Use a queue for the current level and a temporary queue for the next level
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            vector<int> currentLevel;

            // Process all nodes in the current queue
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                res.push_back(node);
                currentLevel.push_back(node);
            }

            // Parallelize the processing of neighbors
            #pragma omp parallel for
            for (size_t i = 0; i < currentLevel.size(); i++) {
                int node = currentLevel[i];
                for (auto neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        #pragma omp critical // Ensure only one thread updates the queue
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = 1;
                                q.push(neighbor);
                            }
                        }
                    }
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

    cout << "Parallel BFS" << endl;
    for (int node : res1)
        cout << node << " ";
    cout << '\n';

    cout << "Parallel DFS" << endl;
    for (int node : res2)
        cout << node << " ";
    return 0;
}