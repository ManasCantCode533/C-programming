#include <stdio.h>
#include <limits.h>

#define MAX 10
#define INF 9999  // Represents infinity

int n; // number of vertices
int cost[MAX][MAX]; // adjacency matrix (weights)

// Function to find vertex with minimum distance value
int minDistance(int dist[], int visited[]) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++)
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

// Dijkstra’s Algorithm
void dijkstra(int src) {
    int dist[MAX];    // shortest distance from src to i
    int visited[MAX]; // visited vertices
    int parent[MAX];  // to store shortest path tree

    // Initialize distances and visited array
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        // Update distances of adjacent vertices
        for (int v = 0; v < n; v++) {
            if (!visited[v] && cost[u][v] && cost[u][v] != INF &&
                dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
            }
        }
    }

    // Print results
    printf("\nVertex\tDistance from Source\tPath");
    for (int i = 0; i < n; i++) {
        printf("\n%d\t\t%d\t\t\t", i, dist[i]);
        int j = i;
        while (j != -1) {
            printf("%d ", j);
            j = parent[j];
        }
    }
    printf("\n");
}

// Main function
int main() {
    int edges, src, u, v, w;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Initialize cost matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = INF;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &w);
        cost[u][v] = w;
        cost[v][u] = w; // For undirected graph; remove for directed
    }

    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(src);

    return 0;
}