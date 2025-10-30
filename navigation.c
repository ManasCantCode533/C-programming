#include <stdio.h>
#include <stdlib.h>
#define MAX 20

// ------------------------------------------
// CAMPUS NAVIGATION SYSTEM
// Concepts Used: Graph + Searching (BFS)
// ------------------------------------------

int adj[MAX][MAX];
int dist[MAX][MAX];
int visited[MAX];
int queue[MAX];
int front = -1, rear = -1;

// Branch/Building Names
char *branches[] = {
    " ",
    "Main Gate",
    "COKE ST",
    "KRC",
    "CB",
    "CVR",
    "ICT",
    "CRL",
    "Girls Hostel",
    "Boys Hostel",
    "Back Gate"
};

// Queue operations
void enqueue(int x) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = x;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

// BFS traversal to find shortest path + distance
void bfs(int start, int n, int parent[], int totalDist[]) {
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
        totalDist[i] = 0;
        parent[i] = -1;
    }

    front = rear = -1;
    enqueue(start);
    visited[start] = 1;

    while (front <= rear) {
        int node = dequeue();
        for (int i = 1; i <= n; i++) {
            if (adj[node][i] && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
                parent[i] = node;
                totalDist[i] = totalDist[node] + dist[node][i];
            }
        }
    }
}

// Print the path and total distance
void printPath(int parent[], int totalDist[], int start, int end) {
    int path[MAX], count = 0;
    int temp = end;

    while (temp != -1) {
        path[count++] = temp;
        temp = parent[temp];
    }

    if (count == 1 && path[0] != start) {
        printf("No path found!\n");
        return;
    }

    printf("\nShortest Path:\n");
    for (int i = count - 1; i >= 0; i--) {
        printf("%s", branches[path[i]]);
        if (i != 0) printf(" -> ");
    }
    printf("\nTotal Distance: %d meters\n", totalDist[end]);
}

// Display direct connections
void showConnections(int n) {
    printf("\nCampus Map (Connections & Distances):\n");
    for (int i = 1; i <= n; i++) {
        printf("%s connects to: \n", branches[i]);
        int connected = 0;
        for (int j = 1; j <= n; j++) {
            if (adj[i][j]) {
                printf("%s (%dm)  ", branches[j], dist[i][j]);
                connected = 1;
            }
        }
        if (!connected)
            printf("None");
        printf("\n");
    }
}

// Mini map display
void displayMiniMap() {
    printf("\n+------------------------------------------+\n");
    printf("|  [1] Main Gate              [5] CVR      |\n");
    printf("|        |                      |          |\n");
    printf("|        |                      |          |\n");
    printf("|  [2] COKE ST --- [3] KRC --- [4] CB      |\n");
    printf("|        |                       |         |\n");
    printf("|  [9] Boys Hostel             [6] ICT     |\n");
    printf("|                               |          |\n");
    printf("|         [8] Girls Hostel --- [7] CRL     |\n");
    printf("|         |                                |\n");
    printf("|        [10] Back Gate                    |\n");
    printf("+------------------------------------------+\n");
}

int main() {
    int n = 10;
    int choice, start, end;

    // Initialize adjacency and distance matrices
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) {
            adj[i][j] = 0;
            dist[i][j] = 0;
        }

    // Define connections with distances
    adj[1][2] = adj[2][1] = 1; dist[1][2] = dist[2][1] = 150;
    adj[1][5] = adj[5][1] = 1; dist[1][5] = dist[5][1] = 200;
    adj[2][3] = adj[3][2] = 1; dist[2][3] = dist[3][2] = 120;
    adj[3][4] = adj[4][3] = 1; dist[3][4] = dist[4][3] = 100;
    adj[4][6] = adj[6][4] = 1; dist[4][6] = dist[6][4] = 130;
    adj[5][6] = adj[6][5] = 1; dist[5][6] = dist[6][5] = 160;
    adj[6][7] = adj[7][6] = 1; dist[6][7] = dist[7][6] = 90;
    adj[7][8] = adj[8][7] = 1; dist[7][8] = dist[8][7] = 110;
    adj[2][9] = adj[9][2] = 1; dist[2][9] = dist[9][2] = 140;
    adj[8][10] = adj[10][8] = 1; dist[8][10] = dist[10][8] = 180;

    printf("\n=========================================\n");
    printf("      CAMPUS NAVIGATION SYSTEM (C)      \n");
    printf("=========================================\n");
    printf(" Concepts Used: Graph + Searching (BFS)\n");
    printf("=========================================\n");

    do {
        printf("\n---------- MENU ----------\n");
        printf("1. Display Campus Map\n");
        printf("2. Find Shortest Path\n");
        printf("3. Show Reachable Places from a Branch\n");
        printf("4. Exit\n");
        printf("---------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMiniMap();
                showConnections(n);
                break;

            case 2: {
                printf("\nAvailable Locations:\n");
                for (int i = 1; i <= n; i++)
                    printf("%d. %s\n", i, branches[i]);
                printf("\nEnter Starting Location (1-10): ");
                scanf("%d", &start);
                printf("Enter Destination (1-10): ");
                scanf("%d", &end);
                int parent[MAX], totalDist[MAX];
                bfs(start, n, parent, totalDist);
                printPath(parent, totalDist, start, end);
                break;
            }

            case 3:
                printf("\nEnter Branch Number (1-10): ");
                scanf("%d", &start);
                printf("From %s, you can directly go to:\n", branches[start]);
                for (int i = 1; i <= n; i++) {
                    if (adj[start][i])
                        printf(" - %s (%dm)\n", branches[i], dist[start][i]);
                }
                break;

            case 4:
                printf("\nThank you for using Campus Navigator!\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
