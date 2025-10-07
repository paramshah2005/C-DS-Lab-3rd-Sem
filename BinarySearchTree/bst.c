#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return createNode(key);
    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    return node;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

Node* searchTree(Node* root, int key) {
    if (!root || root->data == key)
        return root;
    if (key < root->data)
        return searchTree(root->left, key);
    else
        return searchTree(root->right, key);
}

Node* maxValue(Node* root) {
    Node* curr = root;
    while (curr && curr->right != NULL)
        curr = curr->right;
    return curr;
}

Node* minValue(Node* root) {
    Node* curr = root;
    while (curr && curr->left != NULL)
        curr = curr->left;
    return curr;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
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

        Node* temp = minValue(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main() {
    Node* root = NULL;
    root = createNode(50);
    root->left = createNode(30);
    root->right = createNode(70);
    root->left->left = createNode(20);
    root->left->right = createNode(40);
    root->right->left = createNode(60);
    root->right->right = createNode(80);

    int choice, key;

    while (1) {
        printf("\n\n==== BST MENU ====\n");
        printf("1. Inorder Traversal\n");
        printf("2. Preorder Traversal\n");
        printf("3. Postorder Traversal\n");
        printf("4. Search for an Element\n");
        printf("5. Delete a Node\n");
        printf("6. Find Minimum Element\n");
        printf("7. Find Maximum Element\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;

        case 2:
            printf("Preorder Traversal: ");
            preorder(root);
            printf("\n");
            break;

        case 3:
            printf("Postorder Traversal: ");
            postorder(root);
            printf("\n");
            break;

        case 4:
            printf("Enter value to search: ");
            scanf("%d", &key);
            if (searchTree(root, key))
                printf("Element %d found in BST.\n", key);
            else
                printf("Element %d not found in BST.\n", key);
            break;

        case 5:
            printf("Enter value to delete: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
            printf("Node %d deleted (if it existed).\n", key);
            break;

        case 6:
            if (root)
                printf("Minimum element: %d\n", minValue(root)->data);
            else
                printf("Tree is empty.\n");
            break;

        case 7:
            if (root)
                printf("Maximum element: %d\n", maxValue(root)->data);
            else
                printf("Tree is empty.\n");
            break;

        case 8:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
