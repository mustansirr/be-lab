/*
Parallel Breadth First Search and Depth First Search using OpenMP
*/

#include <chrono> // Include the chrono library for timing
#include <iostream>
#include <omp.h>
#include <queue>
#include <random> // Include random for graph generation
#include <vector>

using namespace std;
using namespace chrono; // Add namespace for chrono

class DFS {
public:
  void recursiveDfs(int node, vector<vector<int>> &adj, vector<int> &visited,
                    vector<int> &res) {
    visited[node] = 1;
    res.push_back(node);

#pragma omp parallel for
    for (size_t i = 0; i < adj[node].size(); i++) {
      int neighbor = adj[node][i];
      if (!visited[neighbor]) {
#pragma omp task
        recursiveDfs(neighbor, adj, visited, res);
      }
    }
  }

  vector<int> dfs(int n, vector<vector<int>> &adj) {
    vector<int> visited(n, 0);
    vector<int> res;

// Start the parallel region
#pragma omp parallel
    {
#pragma omp single
      {
        // Ensure starting node exists, default to 0
        if (n > 0)
          recursiveDfs(0, adj, visited, res);
      }
    }
    return res;
  }
};

class BFS {
public:
  vector<int> bfs(int n, vector<vector<int>> &adj) {
    vector<int> visited(n, 0);
    vector<int> res;

    if (n == 0)
      return res;

    visited[0] = 1;

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

void input(int n, int m, vector<vector<int>> &adj) {
  adj.assign(n, vector<int>());
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, n - 1);

  for (int i = 0; i < m; ++i) {
    int u = dis(gen);
    int v = dis(gen);
    if (u != v) { // Avoid self-loops
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }
}

int main() {
  BFS c1;
  DFS c2;

  int n, m;
  cout << "Enter number of nodes (defaulting to 10000 if <= 0): ";
  if (!(cin >> n) || n <= 0) {
    n = 10000;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Using default n = " << n << endl;
  }

  // Heuristic for number of edges, e.g., 2*n for sparse graph or n*log(n)
  m = n * 5;

  vector<vector<int>> adj;

  cout << "Generating graph with " << n << " nodes and " << m << " edges..."
       << endl;
  input(n, m, adj);
  cout << "Graph generated." << endl;

  // Measure BFS runtime
  auto start_bfs = high_resolution_clock::now();
  vector<int> res1 = c1.bfs(n, adj);
  auto end_bfs = high_resolution_clock::now();
  double bfs_time = duration<double>(end_bfs - start_bfs).count();

  // Measure DFS runtime
  auto start_dfs = high_resolution_clock::now();
  vector<int> res2 = c2.dfs(n, adj);
  auto end_dfs = high_resolution_clock::now();
  double dfs_time = duration<double>(end_dfs - start_dfs).count();

  if (n <= 100) {
    cout << "Parallel BFS" << endl;
    for (int node : res1)
      cout << node << " ";
    cout << '\n';

    cout << "Parallel DFS" << endl;
    for (int node : res2)
      cout << node << " ";
    cout << '\n';
  } else {
    cout << "Traversal output suppressed for large graph (n > 100)." << endl;
    cout << "BFS visited " << res1.size() << " nodes." << endl;
    cout << "DFS visited " << res2.size() << " nodes." << endl;
  }

  // Print the timings
  cout << "Parallel BFS Runtime: " << bfs_time << " seconds" << endl;
  cout << "Parallel DFS Runtime: " << dfs_time << " seconds" << endl;

  return 0;
}