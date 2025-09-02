
#include <stdio.h>
#include <stdlib.h>

typedef struct Poly {
    int coeff, exp;
    struct Poly* prev;
    struct Poly* next;
} Poly;

Poly* createNode(int c, int e) {
    Poly* node = (Poly*)malloc(sizeof(Poly));
    node->coeff = c;
    node->exp = e;
    node->prev = node->next = NULL;
    return node;
}

void insertPoly(Poly** head, int c, int e) {
    Poly* node = createNode(c, e);
    if (*head == NULL) {
        *head = node;
        return;
    }
    Poly* temp = *head;
    while (temp->next && temp->exp > e) temp = temp->next;

    if (temp == *head && e > temp->exp) {
        node->next = *head;
        (*head)->prev = node;
        *head = node;
    } else {
        while (temp->next && temp->exp < e) temp = temp->next;
        if (temp->exp == e) {
            temp->coeff += c;
            free(node);
            return;
        } else if (temp->exp < e) {
            node->next = temp;
            node->prev = temp->prev;
            if (temp->prev) temp->prev->next = node;
            else *head = node;
            temp->prev = node;
        } else {
            node->prev = temp;
            node->next = temp->next;
            if (temp->next) temp->next->prev = node;
            temp->next = node;
        }
    }
}

void displayPoly(Poly* head) {
    if (!head) {
        printf("0\n");
        return;
    }
    Poly* temp = head;
    while (temp) {
        printf("%dx^%d ", temp->coeff, temp->exp);
        if (temp->next && temp->next->coeff >= 0) printf("+ ");
        temp = temp->next;
    }
    printf("\n");
}

Poly* addPoly(Poly* P, Poly* Q) {
    Poly* result = NULL;
    Poly *p1 = P, *p2 = Q;
    while (p1 && p2) {
        if (p1->exp == p2->exp) {
            insertPoly(&result, p1->coeff + p2->coeff, p1->exp);
            p1 = p1->next; p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            insertPoly(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            insertPoly(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }
    while (p1) { insertPoly(&result, p1->coeff, p1->exp); p1 = p1->next; }
    while (p2) { insertPoly(&result, p2->coeff, p2->exp); p2 = p2->next; }
    return result;
}

int main() {
    Poly *P = NULL, *Q = NULL, *Sum = NULL;

    insertPoly(&P, 5, 2);
    insertPoly(&P, 4, 1);
    insertPoly(&P, 2, 0);

    insertPoly(&Q, 5, 1);
    insertPoly(&Q, 5, 0);

    printf("P(x) = "); displayPoly(P);
    printf("Q(x) = "); displayPoly(Q);

    Sum = addPoly(P, Q);
    printf("Sum = "); displayPoly(Sum);

    return 0;
}
