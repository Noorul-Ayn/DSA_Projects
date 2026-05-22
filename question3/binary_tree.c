#include <stdio.h>
#include <stdlib.h>

/* ─── Node Structure ─── */
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

/* ─── Queue Node for BFS ─── */
typedef struct QueueNode {
    Node *treeNode;
    struct QueueNode *next;
} QueueNode;

/* ─── Queue Structure ─── */
typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

/* ─── Queue Operations ─── */
Queue *createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, Node *treeNode) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

Node *dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    QueueNode *temp = q->front;
    Node *treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return treeNode;
}

int isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

void freeQueue(Queue *q) {
    while (!isQueueEmpty(q)) dequeue(q);
    free(q);
}

/* ─── Create a New Tree Node ─── */
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("ERROR: Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* ─── Insert Using Level-Order (BFS) ─── */
/*
 * Rule: Elements are inserted level by level, left to right.
 * This guarantees a complete binary tree structure.
 * For each existing node, left child is filled first,
 * then right child, before moving to the next level.
 */
Node *insertLevelOrder(Node *root, int data) {
    Node *newNode = createNode(data);

    if (root == NULL) return newNode;

    Queue *q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        Node *current = dequeue(q);

        if (current->left == NULL) {
            current->left = newNode;
            freeQueue(q);
            return root;
        } else {
            enqueue(q, current->left);
        }

        if (current->right == NULL) {
            current->right = newNode;
            freeQueue(q);
            return root;
        } else {
            enqueue(q, current->right);
        }
    }

    freeQueue(q);
    return root;
}

/* ─── Build Tree from Array ─── */
Node *buildTree(int arr[], int n) {
    if (n == 0) return NULL;
    Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertLevelOrder(root, arr[i]);
    }
    return root;
}

/* ─── Print Root ─── */
void printRoot(Node *root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    printf("\nRoot Node: %d\n", root->data);
}

/* ─── Print All Leaf Nodes ─── */
void printLeaves(Node *root) {
    if (root == NULL) return;

    Queue *q = createQueue();
    enqueue(q, root);

    printf("\nLeaf Nodes: ");
    while (!isQueueEmpty(q)) {
        Node *current = dequeue(q);

        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }

        if (current->left)  enqueue(q, current->left);
        if (current->right) enqueue(q, current->right);
    }
    printf("\n");
    freeQueue(q);
}

/* ─── Find Parent of a Node ─── */
Node *findParent(Node *root, int target) {
    if (root == NULL || root->data == target) return NULL;

    Queue *q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        Node *current = dequeue(q);

        if ((current->left  && current->left->data  == target) ||
            (current->right && current->right->data == target)) {
            freeQueue(q);
            return current;
        }

        if (current->left)  enqueue(q, current->left);
        if (current->right) enqueue(q, current->right);
    }

    freeQueue(q);
    return NULL;
}

/* ─── Print Parent of Selected Node ─── */
void printParent(Node *root, int target) {
    if (root->data == target) {
        printf("\nNode %d is the root — it has no parent.\n", target);
        return;
    }

    Node *parent = findParent(root, target);
    if (parent == NULL) {
        printf("\nNode %d not found in the tree.\n", target);
    } else {
        printf("\nParent of %d: %d\n", target, parent->data);
    }
}

/* ─── Print Siblings of Selected Node ─── */
void printSiblings(Node *root, int target) {
    if (root->data == target) {
        printf("\nNode %d is the root — it has no siblings.\n", target);
        return;
    }

    Node *parent = findParent(root, target);
    if (parent == NULL) {
        printf("\nNode %d not found in the tree.\n", target);
        return;
    }

    printf("\nSiblings of %d: ", target);
    int found = 0;

    if (parent->left && parent->left->data != target) {
        printf("%d ", parent->left->data);
        found = 1;
    }
    if (parent->right && parent->right->data != target) {
        printf("%d ", parent->right->data);
        found = 1;
    }

    if (!found) printf("None");
    printf("\n");
}

/* ─── Print Grandchildren of Selected Node ─── */
void printGrandchildren(Node *root, int target) {
    /* Find the target node first */
    Queue *q = createQueue();
    enqueue(q, root);
    Node *targetNode = NULL;

    while (!isQueueEmpty(q)) {
        Node *current = dequeue(q);
        if (current->data == target) {
            targetNode = current;
            break;
        }
        if (current->left)  enqueue(q, current->left);
        if (current->right) enqueue(q, current->right);
    }
    freeQueue(q);

    if (targetNode == NULL) {
        printf("\nNode %d not found in the tree.\n", target);
        return;
    }

    printf("\nGrandchildren of %d: ", target);
    int found = 0;

    /* Grandchildren = children of target's children */
    if (targetNode->left) {
        if (targetNode->left->left) {
            printf("%d ", targetNode->left->left->data);
            found = 1;
        }
        if (targetNode->left->right) {
            printf("%d ", targetNode->left->right->data);
            found = 1;
        }
    }
    if (targetNode->right) {
        if (targetNode->right->left) {
            printf("%d ", targetNode->right->left->data);
            found = 1;
        }
        if (targetNode->right->right) {
            printf("%d ", targetNode->right->right->data);
            found = 1;
        }
    }

    if (!found) printf("None");
    printf("\n");
}

/* ─── Check if Node Exists ─── */
int nodeExists(Node *root, int target) {
    if (root == NULL) return 0;

    Queue *q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        Node *current = dequeue(q);
        if (current->data == target) {
            freeQueue(q);
            return 1;
        }
        if (current->left)  enqueue(q, current->left);
        if (current->right) enqueue(q, current->right);
    }

    freeQueue(q);
    return 0;
}

/* ─── Free Entire Tree ─── */
void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* ─── Menu ─── */
void showMenu() {
    printf("\n╔══════════════════════════════════╗\n");
    printf("║       BINARY TREE EXPLORER       ║\n");
    printf("╠══════════════════════════════════╣\n");
    printf("║ 1. Print root node               ║\n");
    printf("║ 2. Print all leaf nodes          ║\n");
    printf("║ 3. Find siblings of a node       ║\n");
    printf("║ 4. Find parent of a node         ║\n");
    printf("║ 5. Find grandchildren of a node  ║\n");
    printf("║ 6. Exit                          ║\n");
    printf("╚══════════════════════════════════╝\n");
    printf("Choose an option: ");
}

/* ─── Main ─── */
int main() {
    /* 68 distinct integers */
    int arr[] = {
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
        51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
        61, 62, 63, 64, 65, 66, 67, 68
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== Binary Tree System ===\n");
    printf("Building tree with %d nodes using level-order insertion...\n", n);

    Node *root = buildTree(arr, n);
    printf("Tree constructed successfully!\n");

    int choice, value;
    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printRoot(root);
                break;

            case 2:
                printLeaves(root);
                break;

            case 3:
                printf("Enter node value: ");
                scanf("%d", &value);
                if (!nodeExists(root, value)) {
                    printf("\nNode %d does not exist in the tree.\n", value);
                } else {
                    printSiblings(root, value);
                }
                break;

            case 4:
                printf("Enter node value: ");
                scanf("%d", &value);
                if (!nodeExists(root, value)) {
                    printf("\nNode %d does not exist in the tree.\n", value);
                } else {
                    printParent(root, value);
                }
                break;

            case 5:
                printf("Enter node value: ");
                scanf("%d", &value);
                if (!nodeExists(root, value)) {
                    printf("\nNode %d does not exist in the tree.\n", value);
                } else {
                    printGrandchildren(root, value);
                }
                break;

            case 6:
                printf("\nFreeing memory and exiting...\n");
                freeTree(root);
                printf("Goodbye!\n");
                break;

            default:
                printf("\nInvalid option. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}
