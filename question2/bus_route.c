#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ─── Node Structure ─── */
typedef struct BusStop {
    int stopNumber;
    char stopName[100];
    struct BusStop *prev;
    struct BusStop *next;
} BusStop;

/* ─── Head and Tail pointers ─── */
BusStop *head = NULL;
BusStop *tail = NULL;

/* ─── Create a New Node ─── */
BusStop *createNode(int number, char *name) {
    BusStop *newStop = (BusStop *)malloc(sizeof(BusStop));
    if (!newStop) {
        printf("ERROR: Memory allocation failed.\n");
        exit(1);
    }
    newStop->stopNumber = number;
    strncpy(newStop->stopName, name, 99);
    newStop->stopName[99] = '\0';
    newStop->prev = NULL;
    newStop->next = NULL;
    return newStop;
}

/* ─── Add Stop at End of Route ─── */
void addStop(int number, char *name) {
    BusStop *newStop = createNode(number, name);

    if (head == NULL) {
        head = newStop;
        tail = newStop;
    } else {
        tail->next = newStop;
        newStop->prev = tail;
        tail = newStop;
    }
    printf("  Stop added: [%d] %s\n", number, name);
}

/* ─── Traverse Forward (Home to Campus) ─── */
void traverseForward() {
    if (head == NULL) {
        printf("No bus stops in the route.\n");
        return;
    }
    printf("\n--- Travelling Home to Campus ---\n");
    BusStop *current = head;
    while (current != NULL) {
        printf(">>> Stop %d: %s\n", current->stopNumber, current->stopName);
        if (current->next != NULL) {
            printf("    [waiting 3 seconds...]\n");
            sleep(3);
        }
        current = current->next;
    }
    printf("--- Reached Campus! ---\n\n");
}

/* ─── Traverse Backward (Campus to Home) ─── */
void traverseBackward() {
    if (tail == NULL) {
        printf("No bus stops in the route.\n");
        return;
    }
    printf("\n--- Travelling Campus to Home ---\n");
    BusStop *current = tail;
    while (current != NULL) {
        printf(">>> Stop %d: %s\n", current->stopNumber, current->stopName);
        if (current->prev != NULL) {
            printf("    [waiting 3 seconds...]\n");
            sleep(3);
        }
        current = current->prev;
    }
    printf("--- Reached Home! ---\n\n");
}

/* ─── Print All Stops ─── */
void printRoute() {
    if (head == NULL) {
        printf("Route is empty.\n");
        return;
    }
    printf("\n--- Current Route ---\n");
    BusStop *current = head;
    while (current != NULL) {
        printf("  [%d] %s\n", current->stopNumber, current->stopName);
        current = current->next;
    }
    printf("---------------------\n\n");
}

/* ─── Free All Memory ─── */
void freeList() {
    BusStop *current = head;
    while (current != NULL) {
        BusStop *temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
    tail = NULL;
}

/* ─── Read Initial Stops from User ─── */
void readInitialStops() {
    int n;
    printf("How many bus stops are on the route? ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        char name[100];
        printf("  Enter name for stop %d: ", i + 1);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        addStop(i + 1, name);
    }
    printf("\nRoute constructed successfully!\n");
}

/* ─── Menu ─── */
void showMenu() {
    printf("╔══════════════════════════════╗\n");
    printf("║      BUS ROUTE NAVIGATOR     ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║ 1. Travel Home -> Campus     ║\n");
    printf("║ 2. Travel Campus -> Home     ║\n");
    printf("║ 3. Add a new stop at end     ║\n");
    printf("║ 4. View all stops            ║\n");
    printf("║ 5. Exit                      ║\n");
    printf("╚══════════════════════════════╝\n");
    printf("Choose an option: ");
}

/* ─── Main ─── */
int main() {
    printf("=== Welcome to John's Bus Navigator ===\n\n");

    readInitialStops();
    printRoute();

    int choice;
    do {
        showMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                traverseForward();
                break;

            case 2:
                traverseBackward();
                break;

            case 3: {
                char name[100];
                int number = tail ? tail->stopNumber + 1 : 1;
                printf("Enter name for new stop (Stop %d): ", number);
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                addStop(number, name);
                printf("Stop added successfully!\n\n");
                break;
            }

            case 4:
                printRoute();
                break;

            case 5:
                printf("Freeing memory and exiting...\n");
                freeList();
                printf("Goodbye, John! Safe travels!\n");
                break;

            default:
                printf("Invalid option. Please try again.\n\n");
        }

    } while (choice != 5);

    return 0;
}
