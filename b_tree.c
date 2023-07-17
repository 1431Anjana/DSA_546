#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the binary tree
struct TreeNode* insertNode(struct TreeNode* root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else {
        if (data < root->data) {
            root->left = insertNode(root->left, data);
        } else {
            root->right = insertNode(root->right, data);
        }
    }
    return root;
}

// Function to count the number of siblings at each level
void countSiblingsAtEachLevel(struct TreeNode* root, FILE* file) {
    if (root == NULL) {
        return;
    }

    struct TreeNode* queue[1000];
    int front = -1;
    int rear = -1;
    int currentLevelCount = 1;
    int nextLevelCount = 0;
    int level = 0;

    queue[++rear] = root;

    while (front < rear) {
        struct TreeNode* currentNode = queue[++front];
        currentLevelCount--;

        if (currentNode->left != NULL) {
            queue[++rear] = currentNode->left;
            nextLevelCount++;
        }

        if (currentNode->right != NULL) {
            queue[++rear] = currentNode->right;
            nextLevelCount++;
        }

        if (currentLevelCount == 0) {
            fprintf(file, "Level %d: %d siblings\n", level, nextLevelCount);
            level++;
            currentLevelCount = nextLevelCount;
            nextLevelCount = 0;
        }
    }
}

// Function to free the memory allocated to the tree
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    struct TreeNode* root = NULL;
    int data;

    // Read data from input.txt and construct the binary tree
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Failed to open input file!\n");
        return 1;
    }

    while (fscanf(inputFile, "%d", &data) != EOF) {
        root = insertNode(root, data);
    }

    fclose(inputFile);

    // Open output.txt for writing the result
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open output file!\n");
        freeTree(root);
        return 1;
    }

    // Count siblings at each level and write the result to output.txt
    countSiblingsAtEachLevel(root, outputFile);

    // Close the output file
    fclose(outputFile);

    // Free the memory allocated to the tree
    freeTree(root);

    printf("Sibling counts at each level have been written to output.txt.\n");

    return 0;
}

