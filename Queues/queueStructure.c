#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    char name[50];
    int age;
    int priority;
    struct Patient* next;
};

struct PriorityQueue {
    struct Patient* front;
};

struct PriorityQueue* createQueue() {
    struct PriorityQueue* q = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    q->front = NULL;
    return q;
}

int isEmpty(struct PriorityQueue* q) {
    return (q->front == NULL);
}

void enqueue(struct PriorityQueue* q, char* name, int age, int priority) {
    struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    strcpy(newPatient->name, name);
    newPatient->age = age;
    newPatient->priority = priority;
    newPatient->next = NULL;

    if (isEmpty(q) || priority > q->front->priority) {
        newPatient->next = q->front;
        q->front = newPatient;
    } else {
        struct Patient* current = q->front;
        while (current->next != NULL && priority <= current->next->priority) {
            current = current->next;
        }
        newPatient->next = current->next;
        current->next = newPatient;
    }
    printf("Enqueued: %s (Age: %d, Priority: %d)\n", name, age, priority);
}

void dequeue(struct PriorityQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return;
    }
    struct Patient* temp = q->front;
    printf("Dequeued: %s (Age: %d, Priority: %d)\n", temp->name, temp->age, temp->priority);
    q->front = q->front->next;
    free(temp);
}

void display(struct PriorityQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    struct Patient* temp = q->front;
    printf("Queue elements (by priority):\n");
    while (temp != NULL) {
        printf("- %s (Age: %d, Priority: %d)\n", temp->name, temp->age, temp->priority);
        temp = temp->next;
    }
}

int main() {
    struct PriorityQueue* q = createQueue();
    printf("=== Priority Queue of Patients (Linked List) ===\n");
    printf("(Higher priority number = higher priority)\n\n");

    enqueue(q, "Alice", 30, 3);
    enqueue(q, "Bob", 45, 1);
    enqueue(q, "Charlie", 25, 5);
    enqueue(q, "Diana", 35, 2);
    enqueue(q, "Eve", 28, 4);
    display(q);

    printf("\n--- Dequeuing highest priority ---\n");
    dequeue(q);
    display(q);

    dequeue(q);
    display(q);

    return 0;
}
