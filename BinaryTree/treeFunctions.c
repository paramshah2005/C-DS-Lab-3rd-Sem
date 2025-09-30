//1. Write user-defined functions to perform the following operations on binary trees:
//i) Inorder traversal (Iterative)done
//ii) Postorder traversal (Iterative)done
//iii) Preorder traversal (Iterative)done
//iv) Print the parent of a given elementdone
//v) Print the depth (or height) of the tree
//vi) Print the ancestors of a given element
//vii) Count the number of leaf nodes in a binary tree
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct TreeNode{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* createNode(int data){
    TreeNode* newNode = (struct TreeNode*)malloc(sizeof(TreeNode));
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

void inorderIterative(TreeNode* root) {
    if (!root) return;

    TreeNode* stack[100];
    int top = -1;
    TreeNode* curr = root;

    while (curr != NULL || top != -1) {
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        printf("%d ", curr->data);
        curr = curr->right;
    }
}

void preorderIterative(TreeNode* root) {
    if (!root) return;

    TreeNode* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        TreeNode* node = stack[top--];
        printf("%d ", node->data);

        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
}

void postorderIterative(TreeNode* root) {
    if (!root) return;

    TreeNode* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;
    while (top1 != -1) {
        TreeNode* node = stack1[top1--];
        stack2[++top2] = node;

        if (node->left) stack1[++top1] = node->left;
        if (node->right) stack1[++top1] = node->right;
    }

    while (top2 != -1) {
        printf("%d ", stack2[top2--]->data);
    }
}

void printParent(TreeNode* root, int key) {
    if (root == NULL) return;
    if ((root->left && root->left->data == key) ||
        (root->right && root->right->data == key)) {
        printf("Parent of %d is %d\n", key, root->data);
        return;
    }
    printParent(root->left, key);
    printParent(root->right, key);
}

int depth(TreeNode* root) {
    if (root == NULL) return 0;
    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

int printAncestors(TreeNode* root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;
    if (printAncestors(root->left, key) || printAncestors(root->right, key)) {
        printf("%d ", root->data);
        return 1;
    }
    return 0;
}

int countLeaves(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int main() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int choice, key;
    while (1) {
        printf("\n--- Binary Tree Menu ---\n");
        printf("1. Inorder Traversal (Iterative)\n");
        printf("2. Preorder Traversal (Iterative)\n");
        printf("3. Postorder Traversal (Iterative)\n");
        printf("4. Print Parent of a Node\n");
        printf("5. Print Depth (Height) of Tree\n");
        printf("6. Print Ancestors of a Node\n");
        printf("7. Count Leaf Nodes\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Inorder Traversal: ");
                inorderIterative(root);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderIterative(root);
                break;
            case 3:
                printf("Postorder Traversal: ");
                postorderIterative(root);
                break;
            case 4:
                printf("Enter key: ");
                scanf("%d", &key);
                printParent(root, key);
                break;
            case 5:
                printf("Depth of tree: %d\n", depth(root));
                break;
            case 6:
                printf("Enter key: ");
                scanf("%d", &key);
                printf("Ancestors of %d: ", key);
                if (!printAncestors(root, key)) {
                    printf("Key not found");
                }
                printf("\n");
                break;
            case 7:
                printf("Number of leaf nodes: %d\n", countLeaves(root));
                break;
            case 8:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
}
