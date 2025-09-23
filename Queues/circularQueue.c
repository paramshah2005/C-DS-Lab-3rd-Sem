#include <stdio.h>
#define MAX_SIZE 5

int queue[MAX_SIZE];
int front = 0;
int rear = 0;

int isEmpty() {
    return (front == rear);
}

int isFull() {
    return ((rear + 1) % MAX_SIZE == front);
}

void enqueue(int data) {
    if (isFull()) {
        printf("Queue is full! Cannot enqueue %d\n", data);
        return;
    }
    queue[rear] = data;
    rear = (rear + 1) % MAX_SIZE;
    printf("Enqueued: %d\n", data);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! Cannot dequeue.\n");
        return;
    }
    printf("Dequeued: %d\n", queue[front]);
    front = (front + 1) % MAX_SIZE;
}

void display() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    int i = front;
    while (i != rear) {
        printf("%d ", queue[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main() {
    printf("-------------Circular Queue-------------\n", MAX_SIZE);

    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    dequeue();
    display();

    enqueue(40);
    enqueue(50);
    enqueue(60);
    display();

    dequeue();
    dequeue();
    dequeue();
    display();

    return 0;
}
