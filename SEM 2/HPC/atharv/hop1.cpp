#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected Graph
    }

    // ------------------ PARALLEL BFS ------------------
    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nParallel BFS Traversal: ";

        while (!q.empty()) {
            int size = q.size();
            vector<int> currentLevel;

            while (size--) {
                int node = q.front();
                q.pop();
                currentLevel.push_back(node);
            }

            #pragma omp parallel for
            for (int i = 0; i < currentLevel.size(); i++) {
                int node = currentLevel[i];

                #pragma omp critical
                cout << node << " ";

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                q.push(neighbor);
                            }
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    // ------------------ PARALLEL DFS ------------------
    void parallelDFSUtil(int node, vector<bool> &visited) {

        #pragma omp critical
        {
            if (visited[node])
                return;
            visited[node] = true;
            cout << node << " ";
        }

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                #pragma omp task
                parallelDFSUtil(neighbor, visited);
            }
        }
    }

    void parallelDFS(int start) {
        vector<bool> visited(V, false);

        cout << "\nParallel DFS Traversal: ";

        #pragma omp parallel
        {
            #pragma omp single
            {
                parallelDFSUtil(start, visited);
            }
        }
        cout << endl;
    }
};

int main() {

    Graph g(6);

    // Sample Undirected Graph
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(1,4);
    g.addEdge(2,5);

    cout << "Using OpenMP with " << omp_get_max_threads() << " threads\n";

    g.parallelBFS(0);
    g.parallelDFS(0);

    return 0;
}
