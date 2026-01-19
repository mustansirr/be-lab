/*
Design and implement Parallel Breadth First Search and Depth First Search
based on existing algorithms using OpenMP. Use a Tree or an undirected
graph for BFS and DFS .
*/

#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    #pragma omp parallel
    {
        printf("Thread: %d\n", omp_get_thread_num());
    }
    return 0;
}