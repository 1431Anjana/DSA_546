
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of a node
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to allocate a new node with the given data
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to right rotate subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a node into the AVL tree
struct Node* insert(struct Node* node, int data) {
    // Perform the normal BST insertion
    if (node == NULL)
        return (newNode(data));

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Duplicate keys are not allowed
        return node;

    // Update the height of the ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of the ancestor node to check if it became unbalanced
    int balance = getBalance(node);

    // If the node becomes unbalanced, there are four possible cases:

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Function to store the elements of the AVL tree in a file
void storeInOrder(struct Node* root, FILE* file) {
    if (root == NULL)
        return;

    storeInOrder(root->left, file);
    fprintf(file, "%d ", root->data);
    storeInOrder(root->right, file);
}

int main() {
    FILE* input_file = fopen("input.txt", "w");
    FILE* output_file = fopen("output.txt", "w");

    if (input_file == NULL || output_file == NULL) {
        printf("Failed to open files!\n");
        return 1;
    }

    // Generate random numbers and store them in the file
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        int num = rand() % 100; // Generate a random number between 0 and 99
        fprintf(input_file, "%d ", num);
    }

    fclose(input_file); // Close the input file

    input_file = fopen("input.txt", "r"); // Reopen the input file for reading

    struct Node* root = NULL;
    int num;

    // Read numbers from the file and build the AVL tree
    while (fscanf(input_file, "%d", &num) != EOF) {
        root = insert(root, num);
    }

    // Perform user-defined operations on the AVL tree
    int choice, search_key, delete_key;
    while (1) {
        printf("1. Insert\n2. Delete\n3. Search\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number to insert: ");
                scanf("%d", &num);
                root = insert(root, num);
                break;

            case 2:
                printf("Enter the number to delete: ");
                scanf("%d", &delete_key);
                root = deleteNode(root, delete_key);
                break;

            case 3:
                printf("Enter the number to search: ");
                scanf("%d", &search_key);
                struct Node* result = search(root, search_key);
                if (result != NULL)
                    printf("Found: %d\n", result->data);
                else
                    printf("Not found: %d\n", search_key);
                break;

            case 4:
                // Store the final output in a file
                storeInOrder(root, output_file);

                // Close files
                fclose(input_file);
                fclose(output_file);

                return 0;

            default:
                printf("Invalid choice!\n");
                break;
        }

        printf("\n");
    }
}
