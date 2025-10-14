#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
    int height;
} Node;

int max(int a, int b) { return (a > b) ? a : b; }

int height(Node *n) {
    if (n == NULL) return 0;
    return n->height;
}

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(Node* n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int search(Node* root, int key) {
    if (root == NULL) return 0;
    if (key == root->key) return 1;
    if (key < root->key) return search(root->left, key);
    else return search(root->right, key);
}

int main() {
    Node* root = NULL;
    int choice, key;
    printf("AVL Tree Implementation\n");
    while (1) {
        printf("\n1. Insert\n2. Inorder\n3. Preorder\n4. Postorder\n5. Search\n6. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter key: ");
                if (scanf("%d", &key) != 1) {
                    int c; while ((c = getchar()) != '\n' && c != EOF) {}
                    break;
                }
                if (search(root, key)) printf("Key already exists.\n");
                else root = insert(root, key);
                break;
            case 2:
                if (root == NULL) printf("Empty tree.\n");
                else { printf("Inorder: "); inorder(root); printf("\n"); }
                break;
            case 3:
                if (root == NULL) printf("Empty tree.\n");
                else { printf("Preorder: "); preorder(root); printf("\n"); }
                break;
            case 4:
                if (root == NULL) printf("Empty tree.\n");
                else { printf("Postorder: "); postorder(root); printf("\n"); }
                break;
            case 5:
                printf("Enter key to search: ");
                if (scanf("%d", &key) != 1) {
                    int c; while ((c = getchar()) != '\n' && c != EOF) {}
                    break;
                }
                if (search(root, key)) printf("Key found.\n");
                else printf("Key not found.\n");
                break;
            case 6:
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
