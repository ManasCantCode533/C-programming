#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}Node;

Node* makeNull(Node* root) {
    if (root != NULL) {
        makeNull(root->left);
        makeNull(root->right);
        free(root);
    }
    return NULL;
}
Node* newNode(int data) {
    Node* Newnode = (Node*)malloc(sizeof(Node));
    Newnode->data = data;
    Newnode->left = Newnode->right = NULL;
    return Newnode;
}
Node* insert(Node* root, int data) {
    if (root == NULL)
        return newNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}
Node* find(Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    if (key < root->data)
        return find(root->left, key);
    else
        return find(root->right, key);
}
Node* findMax(Node* root) {
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}
Node* findMin (Node* root) {
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}
Node* delete(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = delete(root->left, key);
    else if (key > root->data)
        root->right = delete(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
int main() {
    struct Node* root = NULL;
    root = insert(root, 50);
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
    int key = 40;
    if (find(root, key))
        printf("%d found in BST.\n", key);
    else
        printf("%d not found in BST.\n", key);
    printf("Minimum value: %d\n", findMin(root)->data);
    printf("Maximum value: %d\n", findMax(root)->data);
    printf("Deleting 20...\n");
    root = delete(root, 20);
    inorder(root);
    printf("\n");  
    root = makeNull(root);
    printf("Tree made empty.\n");
    return 0;
}