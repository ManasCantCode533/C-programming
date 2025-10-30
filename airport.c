#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH 31
#define MAX_CITIES 10

/* -------- Flights (Linked List) -------- */
typedef struct Flight {
    int no, dur;
    char src[20], dest[20];
    float fare;
    struct Flight *next;
} Flight;
Flight *head = NULL;

Flight* newFlight(int n, char* s, char* d, int du, float fare) {
    Flight* f = (Flight*)malloc(sizeof(Flight));
    f->no = n;
    strcpy(f->src, s);
    strcpy(f->dest, d);
    f->dur = du;
    f->fare = fare;
    f->next = NULL;
    return f;
}
void addFlight(Flight* f) { f->next = head; head = f; }

void showFlights() {
    if (!head) { puts("No flights available."); return; }
    puts("\nAvailable Flights:");
    for (Flight* p = head; p; p = p->next)
        printf(" %d: %s -> %s (%d min)\nFare: Rs %.2f\n", 
               p->no, p->src, p->dest, p->dur, p->fare);
}

Flight* findFlight(int no) {
    for (Flight* p = head; p; p = p->next)
        if (p->no == no) return p;
    return NULL;
}

/* -------- Passenger Hash Table -------- */
typedef struct Passenger {
    int id;
    char name[20];
    float luggage, charge, fare;
    int flightNo;
    char src[20], dest[20];
    struct Passenger* next;
} Passenger;

Passenger* H[HASH] = {NULL};
int h(int id) { return abs(id % HASH); }

void addPassenger(Passenger* p) {
    int k = h(p->id);
    p->next = H[k];
    H[k] = p;
}

Passenger* getPassenger(int id) {
    for (Passenger* p = H[h(id)]; p; p = p->next)
        if (p->id == id) return p;
    return NULL;
}

/* -------- Boarding Pass -------- */
void printBoardingPass(Passenger* p) {
    float total = p->fare + p->charge;
    printf("\n========== BOARDING PASS ==========\n");
    printf(" Passenger Name : %s\n", p->name);
    printf(" Passenger ID   : %d\n", p->id);
    printf(" Flight Number  : %d\n", p->flightNo);
    printf(" Route          : %s -> %s\n", p->src, p->dest);
    printf(" Flight Fare    : Rs%.2f\n", p->fare);
    printf(" Luggage Weight : %.2f kg\n", p->luggage);
    printf(" Extra Charges  : Rs%.2f\n", p->charge);
    printf(" Total Charges  : Rs%.2f\n", total);
    printf("===================================\n\n");
}

/* -------- Graph for Airport Routes -------- */
char cities[MAX_CITIES][20] = {
    "DELHI", "MUMBAI", "BENGALORE", "CHENNAI", "HYDERABAD",
    "VISAKHAPATNAM", "GOA", "KOLKATA", "PATNA", "GORAKHPUR"
};

int adj[MAX_CITIES][MAX_CITIES] = {0};

int getCityIndex(char *name) {
    for (int i = 0; i < MAX_CITIES; i++)
        if (strcmp(cities[i], name) == 0)
            return i;
    return -1;
}

void addRoute(char *src, char *dest) {
    int u = getCityIndex(src);
    int v = getCityIndex(dest);
    if (u != -1 && v != -1)
        adj[u][v] = adj[v][u] = 1; // Undirected
}

/* -------- Display the Airport Map -------- */
void showAirportMap() {
    printf("\n========== INDIA AIRPORT ROUTE MAP ==========\n\n");
    printf("               [DELHI]\n");
    printf("                 |  \\\n");
    printf("                 |   \\_________[KOLKATA]\n");
    printf("                 |               |\n");
    printf("             [GORAKHPUR]      [PATNA]\n");
    printf("                                |\n");
    printf("                                |\n");
    printf("          [MUMBAI] ------ [HYDERABAD] ------ [VISAKHAPATNAM]\n");
    printf("             |                |\n");
    printf("            [GOA]         [BENGALORE]\n");
    printf("                               |\n");
    printf("                           [CHENNAI]\n");
    printf("\n---------------------------------------------\n");
    printf("Graph Connections (Adjacency List):\n\n");

    for (int i = 0; i < MAX_CITIES; i++) {
        printf("%-12s -> ", cities[i]);
        for (int j = 0; j < MAX_CITIES; j++) {
            if (adj[i][j])
                printf("%s ", cities[j]);
        }
        printf("\n");
    }

    printf("---------------------------------------------\n");
}


/* -------- MAIN -------- */
int main() {
    printf("Airport Management System (Linked List + Hashing + Graph)\n");

    /* Predefined flights */
    addFlight(newFlight(101, "DELHI", "MUMBAI", 120, 5500));
    addFlight(newFlight(202, "MUMBAI", "BENGALORE", 100, 4500));
    addFlight(newFlight(303, "DELHI", "HYDERABAD", 150, 6000));
    addFlight(newFlight(404, "BENGALORE", "CHENNAI", 90, 5000));
    addFlight(newFlight(505, "GORAKHPUR", "DELHI", 180, 8000));
    addFlight(newFlight(606, "HYDERABAD", "VISAKHAPATNAM", 180, 4000));
    addFlight(newFlight(707, "PATNA", "GORAKHPUR", 120, 3500));
    addFlight(newFlight(808, "GOA", "MUMBAI", 180, 4000));
    addFlight(newFlight(909, "KOLKATA", "DELHI", 180, 12000));

    /* Build graph connections */
    for (Flight *f = head; f; f = f->next)
        addRoute(f->src, f->dest);

    int choice;
    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Show Airport Map\n");
        printf("2. Show All Flights\n");
        printf("3. Book Flight\n");
        printf("4. Find Passenger by ID\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            showAirportMap();
        }
        else if (choice == 2) {
            showFlights();
        }
        else if (choice == 3) {
            showFlights();
            int fno;
            printf("\nEnter flight number to book: ");
            scanf("%d", &fno);
            Flight* f = findFlight(fno);
            if (!f) {
                printf("Invalid flight number.\n");
                continue;
            }

            printf("\nSelected Flight: %s -> %s (Fare: Rs%.2f)\n", 
                   f->src, f->dest, f->fare);

            Passenger* p = (Passenger*)malloc(sizeof(Passenger));
            printf("Enter passenger name: ");
            scanf("%s", p->name);
            printf("Enter mobile number (as ID): ");
            scanf("%d", &p->id);
            printf("Enter luggage weight (kg): ");
            scanf("%f", &p->luggage);

            strcpy(p->src, f->src);
            strcpy(p->dest, f->dest);
            p->flightNo = f->no;
            p->fare = f->fare;
            p->charge = (p->luggage > 22) ? (p->luggage - 22) * 400 : 0;

            addPassenger(p);
            printf("\nBooking Successful!\n");
            printBoardingPass(p);
        }
        else if (choice == 4) {
            int id;
            printf("Enter passenger ID: ");
            scanf("%d", &id);
            Passenger* p = getPassenger(id);
            if (p) printBoardingPass(p);
            else printf("Passenger not found.\n");
        }
        else if (choice == 5) {
            puts("Exiting system...");
            break;
        }
        else
            puts("Invalid choice!");
    }
    return 0;
}
