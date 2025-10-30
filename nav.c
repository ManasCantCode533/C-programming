#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

// ------------------------------------------
// CAMPUS NAVIGATION SYSTEM
// Concepts Used: Graph + BFS + Directions
// ------------------------------------------

int adj[MAX][MAX];
int dist[MAX][MAX];
char direction[MAX][MAX][20]; // Direction between nodes

int visited[MAX];
int queue[MAX];
int front = -1, rear = -1;

// Building / Branch Names
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

// BFS traversal to find shortest path
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

// Print the path and total distance with directions
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
        if (i != 0) {
            printf(" --(%s, %dm)--> ", direction[path[i]][path[i-1]], dist[path[i]][path[i-1]]);
        }
    }
    printf("\nTotal Distance: %d meters\n", totalDist[end]);
}

// Display direct connections with directions
void showConnections(int n) {
    printf("\nCampus Map (Connections, Distances & Directions):\n");
    for (int i = 1; i <= n; i++) {
        printf("\n%s connects to:\n", branches[i]);
        int connected = 0;
        for (int j = 1; j <= n; j++) {
            if (adj[i][j]) {
                printf(" - %s (%dm, %s)\n", branches[j], dist[i][j], direction[i][j]);
                connected = 1;
            }
        }
        if (!connected)
            printf(" None\n");
    }
}

// Mini map display
void displayMiniMap() {
    printf("||----------------------------------------GITAM--------------------------------------||\n");
    printf("\n");
    printf("+-------------------------------------------------------------------------------------+\n");
    printf("|                    [9]Boys hostel                                                   |\n");
    printf("|                         |                                                           |\n");
    printf("|                         |                                                           |\n");
    printf("|  [1]Main gate----- [2]Coke St.------------[3]KRC------------- [10]Back gate         |\n");
    printf("|             |                                |                         |            |\n");
    printf("|              |                               |                         |            |\n");
    printf("|             [5]CV Raman Bhavan            [4]CB                        |            |\n");
    printf("|                       |                       |                        |            |\n");
    printf("|                        |-------------[6]ICT Bhavan-----[7]CRL ---[8]Girls Hostel    |\n");
    printf("+-------------------------------------------------------------------------------------+\n");
}

int main() {
    int n = 10;
    int choice, start, end;

    // Initialize adjacency, distance, and direction
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) {
            adj[i][j] = 0;
            dist[i][j] = 0;
            strcpy(direction[i][j], " ");
        }

    // Define connections with distances and directions
    adj[1][2] = adj[2][1] = 1; dist[1][2] = dist[2][1] = 220;
    strcpy(direction[2][1], "East");
    strcpy(direction[1][2], "West");

    adj[1][5] = adj[5][1] = 1; dist[1][5] = dist[5][1] = 450;
    strcpy(direction[1][5], "South-West");
    strcpy(direction[5][1], "North-East");

    adj[2][3] = adj[3][2] = 1; dist[2][3] = dist[3][2] = 120;
    strcpy(direction[2][3], "West");
    strcpy(direction[3][2], "East");

    adj[3][4] = adj[4][3] = 1; dist[3][4] = dist[4][3] = 120;
    strcpy(direction[3][4], "South");
    strcpy(direction[4][3], "North");

    adj[4][6] = adj[6][4] = 1; dist[4][6] = dist[6][4] = 110;
    strcpy(direction[4][6], "South");
    strcpy(direction[6][4], "North");

    adj[5][6] = adj[6][5] = 1; dist[5][6] = dist[6][5] = 120;
    strcpy(direction[5][6], "West");
    strcpy(direction[6][5], "East");

    adj[6][7] = adj[7][6] = 1; dist[6][7] = dist[7][6] = 400;
    strcpy(direction[6][7], "South-West");
    strcpy(direction[7][6], "North-East");

    adj[7][8] = adj[8][7] = 1; dist[7][8] = dist[8][7] = 90;
    strcpy(direction[7][8], "North");
    strcpy(direction[8][7], "South");

    adj[2][9] = adj[9][2] = 1; dist[2][9] = dist[9][2] = 260;
    strcpy(direction[2][9], "North-West");
    strcpy(direction[9][2], "South-East");

    adj[8][10] = adj[10][8] = 1; dist[8][10] = dist[10][8] = 210;
    strcpy(direction[8][10], "North");
    strcpy(direction[10][8], "South");

    adj[3][10] = adj[10][3] = 1; dist[3][10] = dist[10][3] = 240;
    strcpy(direction[3][10], "West");
    strcpy(direction[10][3], "East");

    adj[5][4] = adj[4][5] = 1; dist[4][5] = dist[5][4] = 110;
    strcpy(direction[4][5], "South-East");
    strcpy(direction[5][4], "North-West");

    printf("\n=========================================\n");
    printf("      CAMPUS NAVIGATION SYSTEM (C)      \n");
    printf("=========================================\n");
    printf(" Concepts Used: Graph + BFS + Directions\n");
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
                        printf(" - %s (%dm, %s)\n", branches[i], dist[start][i], direction[start][i]);
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
