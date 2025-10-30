#include <stdio.h>
#include <stdlib.h>

#define MAX 10  // maximum number of vertices

int adj[MAX][MAX];  // adjacency matrix
int visited[MAX];
int n;  // number of vertices

// Function to create graph
void createGraph() {
    int edges, src, dest;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    // Read edges
    printf("Enter edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        adj[src][dest] = 1;
        adj[dest][src] = 1; // For undirected graph
    }
}

// ---------------- DFS ----------------
void DFS(int v) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i])
            DFS(i);
    }
}

// ---------------- BFS ----------------
void BFS(int start) {
    int queue[MAX], front = 0, rear = -1;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[++rear] = start;

    while (front <= rear) {
        int v = queue[front++];
        printf("%d ", v);

        for (int i = 0; i < n; i++) {
            if (adj[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    createGraph();

    int startVertex;
    printf("Enter starting vertex: ");
    scanf("%d", &startVertex);

    // DFS traversal
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    printf("\nDepth First Search (DFS): ");
    DFS(startVertex);

    // BFS traversal
    printf("\nBreadth First Search (BFS): ");
    BFS(startVertex);

    printf("\n");
    return 0;
}