#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* First = NULL;
Node* Last = NULL;

void insertFirstNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = newNode;
    First = Last = newNode;
    printf("Inserted %d as the first node.\n", value);
}

void insertEndNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = First;
    Last->next = newNode;
    Last = newNode;
    printf("Inserted %d at the end.\n", value);
}

void insertEnd(int value) {
    if (First == NULL) {
        insertFirstNode(value);
    } else {
        insertEndNode(value);
    }
    display();
}

void deleteBegin() {
    if (First == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    Node* temp = First;
    if (First == Last) {
        printf("Deleted %d from the beginning.\n", First->data);
        free(First);
        First = Last = NULL;
    } else {
        First = First->next;
        Last->next = First;
        printf("Deleted %d from the beginning.\n", temp->data);
        free(temp);
    }
    display();
}

void deleteEnd() {
    if (First == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    Node* temp = First;
    if (First == Last) {
        printf("Deleted %d from the end.\n", First->data);
        free(First);
        First = Last = NULL;
    } else {
        while (temp->next != Last) {
            temp = temp->next;
        }
        printf("Deleted %d from the end.\n", Last->data);
        free(Last);
        temp->next = First;
        Last = temp;
    }
    display();
}

void display() {
    if (First == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* current = First;
    printf("Circular List: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != First);
    printf("\n");
}

int main() {
    insertEnd(10);
    insertEnd(20);
    insertEnd(30);

    deleteBegin();

    deleteEnd();

    deleteEnd();


    return 0;
}
