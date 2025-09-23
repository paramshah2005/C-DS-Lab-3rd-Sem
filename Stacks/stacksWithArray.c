#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
char arr[MAX];
int top = -1;

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == MAX - 1;
}

void push(char c)
{
    if (isFull())
        return;
    arr[++top] = c;
}

char pop()
{
    if (isEmpty())
        return '\0';
    return arr[top--];
}

char peek()
{
    if (isEmpty())
        return '\0';
    return arr[top];
}

int isPalindrome(char *str)
{
    top = -1;
    for (int i = 0; i < strlen(str); i++)
    {
        push(str[i]);
    }
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != pop())
            return 0;
    }
    return 1;
}

int isBalanced(char *expr)
{
    top = -1;
    for (int i = 0; expr[i] != '\0'; i++)
    {
        char c = expr[i];
        if (c == '(' || c == '{' || c == '[')
            push(c);
        else if (c == ')' || c == '}' || c == ']')
        {
            if (isEmpty() ||
                (c == ')' && peek() != '(') ||
                (c == '}' && peek() != '{') ||
                (c == ']' && peek() != '['))
            {
                return 0;
            }
            else
                pop();
        }
    }
    return isEmpty();
}

int main()
{
    int choice;
    char *str = (char *)malloc(MAX * sizeof(char));
    char *expr = (char *)malloc(MAX * sizeof(char));

    do {
        printf("\nMenu:\n");
        printf("1. Check if a string is a palindrome\n");
        printf("2. Check if an expression has balanced brackets\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter a string: ");
                fgets(str, MAX, stdin);
                str[strcspn(str, "\n")] = '\0';
                if (isPalindrome(str))
                    printf("%s is a palindrome.\n", str);
                else
                    printf("%s is not a palindrome.\n", str);
                break;
            case 2:
                printf("Enter an expression: ");
                fgets(expr, MAX, stdin);
                expr[strcspn(expr, "\n")] = '\0';
                if (isBalanced(expr))
                    printf("%s is balanced.\n", expr);
                else
                    printf("%s is not balanced.\n", expr);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    free(str);
    free(expr);
    return 0;
}
