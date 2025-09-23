#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

struct PrintJob {
    int docID;
    char name[50];
};

struct PrintJob queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = -1;

int isFull() {
    return (rear == MAX_QUEUE_SIZE - 1);
}

int isEmpty() {
    return (front > rear);
}

void enqueue(int id, char* name) {
    if (isFull()) {
        printf("Queue is full! Cannot enqueue more jobs.\n");
        return;
    }
    rear++;
    queue[rear].docID = id;
    strcpy(queue[rear].name, name);
    printf("Enqueued: Document '%s' with ID %d\n", name, id);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! No jobs to print.\n");
        return;
    }
    printf("Printing: Document '%s' with ID %d\n", queue[front].name, queue[front].docID);
    front++;
}

int main() {
    int numJobs;
    int docID;
    char docName[50];

    printf("=== Printer Queue Simulation (FIFO using Array) ===\n");
    printf("Enter the number of print jobs arriving: ");
    scanf("%d", &numJobs);

    printf("\n--- Simulating job arrivals and enqueuing ---\n");
    for (int i = 0; i < numJobs; i++) {
        printf("\nJob %d:\n", i + 1);
        printf("Enter document ID: ");
        scanf("%d", &docID);
        printf("Enter document name: ");
        scanf("%s", docName);
        enqueue(docID, docName);
    }

    printf("\n--- Simulating printing ---\n");
    while (!isEmpty()) {
        dequeue();
    }

    printf("\nAll jobs printed. Queue is now empty.\n");
    return 0;
}

