#include <stdio.h>
#include <stdlib.h>

// Structure for each node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// 1. makeNull() – make tree empty
struct Node* makeNull(struct Node* root) {
    if (root != NULL) {
        makeNull(root->left);
        makeNull(root->right);
        free(root);
    }
    return NULL;
}

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 2. insert() – insert a node into BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return newNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// 3. find() – search for a value
struct Node* find(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    if (key < root->data)
        return find(root->left, key);
    else
        return find(root->right, key);
}

// 4. findMax() – find maximum value
struct Node* findMax(struct Node* root) {
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

// 5. findMin() – find minimum value
struct Node* findMin(struct Node* root) {
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

// 6. delete() – delete a node from BST
struct Node* delete(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = delete(root->left, key);
    else if (key > root->data)
        root->right = delete(root->right, key);
    else {
        // Node with one or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: get inorder successor (min in right subtree)
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

// Inorder traversal (Left - Root - Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function to test all operations
int main() {
    struct Node* root = NULL;

    // Insert elements
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // Find operation
    int key = 40;
    if (find(root, key))
        printf("%d found in BST.\n", key);
    else
        printf("%d not found in BST.\n", key);

    // Find minimum and maximum
    printf("Minimum value: %d\n", findMin(root)->data);
    printf("Maximum value: %d\n", findMax(root)->data);

    // Delete a few nodes
    printf("Deleting 20...\n");
    root = delete(root, 20);
    inorder(root);
    printf("\n");

    printf("Deleting 30...\n");
    root = delete(root, 30);
    inorder(root);
    printf("\n");

    printf("Deleting 50...\n");
    root = delete(root, 50);
    inorder(root);
    printf("\n");

    // makeNull() – free the entire tree
    root = makeNull(root);
    printf("Tree made empty.\n");

    return 0;
}