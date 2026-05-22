#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─── BST Node Structure ─── */
typedef struct Node {
    char firstName[50];
    char lastName[50];
    float grade;
    struct Node *left;
    struct Node *right;
} Node;

/* ─────────────────────────────────────────
 * createNode: Allocates a new BST node
 * ───────────────────────────────────────── */
Node *createNode(char *firstName, char *lastName, float grade) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("ERROR: Memory allocation failed.\n");
        exit(1);
    }
    strncpy(newNode->firstName, firstName, 49);
    strncpy(newNode->lastName,  lastName,  49);
    newNode->firstName[49] = '\0';
    newNode->lastName[49]  = '\0';
    newNode->grade  = grade;
    newNode->left   = NULL;
    newNode->right  = NULL;
    return newNode;
}

/* ─────────────────────────────────────────
 * insert: Inserts a node into the BST
 * Key: lastName (alphabetical ordering)
 * Duplicate last names go to right subtree
 * ───────────────────────────────────────── */
Node *insert(Node *root, char *firstName, char *lastName, float grade) {
    if (root == NULL) {
        return createNode(firstName, lastName, grade);
    }

    int cmp = strcmp(lastName, root->lastName);

    if (cmp < 0) {
        /* lastName is smaller → go left */
        root->left = insert(root->left, firstName, lastName, grade);
    } else {
        /* lastName is greater or equal → go right */
        /* Duplicates handled by inserting to right subtree */
        root->right = insert(root->right, firstName, lastName, grade);
    }

    return root;
}

/* ─────────────────────────────────────────
 * search: Searches BST by lastName
 * Prints all matching records (duplicates)
 * ───────────────────────────────────────── */
int search(Node *root, char *lastName) {
    if (root == NULL) return 0;

    int found = 0;
    int cmp = strcmp(lastName, root->lastName);

    if (cmp < 0) {
        /* Search left subtree only */
        found = search(root->left, lastName);
    } else {
        /* Check right subtree for duplicates */
        found = search(root->right, lastName);

        /* Check current node */
        if (strcmp(root->lastName, lastName) == 0) {
            printf("  Name : %s %s\n", root->firstName, root->lastName);
            printf("  Grade: %.2f\n", root->grade);
            printf("  -------------------------\n");
            found = 1;
        }
    }

    return found;
}

/* ─────────────────────────────────────────
 * readFile: Reads and parses students.txt
 * Format: Firstname|Lastname|Grade
 * Returns root of constructed BST
 * ───────────────────────────────────────── */
Node *readFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("ERROR: Could not open file '%s'\n", filename);
        return NULL;
    }

    /* Check if file is empty */
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        printf("ERROR: File '%s' is empty.\n", filename);
        fclose(fp);
        return NULL;
    }
    rewind(fp);

    Node *root = NULL;
    char line[200];
    int lineNum = 0;
    int recordsRead = 0;

    while (fgets(line, sizeof(line), fp)) {
        lineNum++;

        /* Remove trailing newline */
        line[strcspn(line, "\n")] = '\0';

        /* Skip empty lines */
        if (strlen(line) == 0) continue;

        /* Parse pipe-delimited record */
        char firstName[50], lastName[50];
        float grade;

        char *token = strtok(line, "|");
        if (!token) {
            printf("WARNING: Malformed record at line %d — skipping.\n", lineNum);
            continue;
        }
        strncpy(firstName, token, 49);
        firstName[49] = '\0';

        token = strtok(NULL, "|");
        if (!token) {
            printf("WARNING: Malformed record at line %d — skipping.\n", lineNum);
            continue;
        }
        strncpy(lastName, token, 49);
        lastName[49] = '\0';

        token = strtok(NULL, "|");
        if (!token) {
            printf("WARNING: Malformed record at line %d — skipping.\n", lineNum);
            continue;
        }
        grade = atof(token);

        /* Validate grade range */
        if (grade < 0 || grade > 100) {
            printf("WARNING: Invalid grade at line %d — skipping.\n", lineNum);
            continue;
        }

        root = insert(root, firstName, lastName, grade);
        recordsRead++;
    }

    fclose(fp);
    printf("Successfully loaded %d student records.\n", recordsRead);
    return root;
}

/* ─────────────────────────────────────────
 * inOrder: Prints all records in sorted
 * order (ascending by last name)
 * ───────────────────────────────────────── */
void inOrder(Node *root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("  %-15s %-15s %.2f\n",
           root->firstName,
           root->lastName,
           root->grade);
    inOrder(root->right);
}

/* ─────────────────────────────────────────
 * freeTree: Frees all allocated memory
 * ───────────────────────────────────────── */
void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* ─── Menu ─── */
void showMenu() {
    printf("\n╔══════════════════════════════════╗\n");
    printf("║     STUDENT BST SEARCH SYSTEM    ║\n");
    printf("╠══════════════════════════════════╣\n");
    printf("║ 1. Search by last name           ║\n");
    printf("║ 2. Print all records (sorted)    ║\n");
    printf("║ 3. Exit                          ║\n");
    printf("╚══════════════════════════════════╝\n");
    printf("Choose an option: ");
}

/* ─── Main ─── */
int main() {
    printf("=== Student BST Search System ===\n\n");

    /* Read and build BST from file */
    Node *root = readFile("students.txt");
    if (root == NULL) {
        printf("No records loaded. Exiting.\n");
        return 1;
    }

    int choice;
    char lastName[50];

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Enter last name to search: ");
                fgets(lastName, sizeof(lastName), stdin);
                lastName[strcspn(lastName, "\n")] = '\0';

                printf("\nSearch Results for '%s':\n", lastName);
                printf("  -------------------------\n");

                if (!search(root, lastName)) {
                    printf("  No student found with last name '%s'.\n", lastName);
                }
                break;

            case 2:
                printf("\nAll Student Records (sorted by last name):\n");
                printf("  %-15s %-15s %s\n", "First Name", "Last Name", "Grade");
                printf("  %-15s %-15s %s\n", "----------", "---------", "-----");
                inOrder(root);
                break;

            case 3:
                printf("\nFreeing memory and exiting...\n");
                freeTree(root);
                printf("Goodbye!\n");
                break;

            default:
                printf("\nInvalid option. Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}
