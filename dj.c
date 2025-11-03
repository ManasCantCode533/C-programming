#include <stdio.h> 
#include <stdbool.h> 
#define INF 9999 
#define V 5 
int minDistance(int dist[], bool sptSet[]) { 
    int min = INF, min_index; 
    for (int v = 0; v < V; v++) 
    if (!sptSet[v] && dist[v] <= min) 
    min = dist[v], min_index = v; 
    return min_index; 
} 
void printSolution(int dist[]) { 
    printf("Vertex \t Distance from Source\n"); 
    for (int i = 0; i < V; i++) 
    printf("%d \t %d\n", i, dist[i]); 
} 
void dijkstra(int graph[V][V], int src) { 
    int dist[V]; 
    bool sptSet[V]; 
    for (int i = 0; i < V; i++) 
    dist[i] = INF, sptSet[i] = false; 
    dist[src] = 0; 
    for (int count = 0; count < V - 1; count++) { 
    int u = minDistance(dist, sptSet); 
    sptSet[u] = true; 
    for (int v = 0; v < V; v++) 
    if (!sptSet[v] && graph[u][v] && dist[u] != INF 
    && dist[u] + graph[u][v] < dist[v]) 
    dist[v] = dist[u] + graph[u][v]; 
    } 
    printSolution(dist); 
} 
int main() { 
    int graph[V][V] = { 
    {0, 10, 0, 0, 5},
    {0, 0, 1, 0, 2},
    {0, 0, 0, 4, 0},
    {7, 0, 6, 0, 0}, 
    {0, 3, 9, 2, 0} 
    }; 
    dijkstra(graph, 0);
    return 0;
}
// #include <stdio.h>
// #include <stdbool.h>

// #define INF 9999  // Represents infinity (no connection)
// #define V 5       // Number of vertices in the graph

// // Function to find the vertex with the minimum distance value
// // that has not yet been processed
// int minDistance(int dist[], bool sptSet[]) {
//     int min = INF, min_index = -1;

//     for (int v = 0; v < V; v++) {
//         if (!sptSet[v] && dist[v] <= min) {
//             min = dist[v];
//             min_index = v;
//         }
//     }

//     return min_index;
// }

// // Function to print the final shortest distance from the source
// void printSolution(int dist[]) {
//     printf("Vertex\tDistance from Source\n");
//     for (int i = 0; i < V; i++)
//         printf("%d\t%d\n", i, dist[i]);
// }

// // Function that implements Dijkstra's algorithm
// void dijkstra(int graph[V][V], int src) {
//     int dist[V];        // dist[i] holds the shortest distance from src to i
//     bool sptSet[V];     // sptSet[i] is true if vertex i is processed

//     // Initialize all distances as infinite and sptSet[] as false
//     for (int i = 0; i < V; i++) {
//         dist[i] = INF;
//         sptSet[i] = false;
//     }

//     // Distance of source vertex from itself is always 0
//     dist[src] = 0;

//     // Find shortest path for all vertices
//     for (int count = 0; count < V - 1; count++) {
//         // Pick the vertex with the minimum distance
//         int u = minDistance(dist, sptSet);
//         sptSet[u] = true;

//         // Update distance value of the adjacent vertices
//         for (int v = 0; v < V; v++) {
//             if (!sptSet[v] && graph[u][v] && dist[u] != INF
//                 && dist[u] + graph[u][v] < dist[v]) {
//                 dist[v] = dist[u] + graph[u][v];
//             }
//         }
//     }

//     // Print the final result
//     printSolution(dist);
// }

// // Main function
// int main() {
//     int graph[V][V] = {
//         {0, 10, 0, 0, 5},
//         {0, 0, 1, 0, 2},
//         {0, 0, 0, 4, 0},
//         {7, 0, 6, 0, 0},
//         {0, 3, 9, 2, 0}
//     };

//     dijkstra(graph, 0); // Run Dijkstra from vertex 0

//     return 0;
// }
