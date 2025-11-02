#include <stdio.h>
#include <stdlib.h> 

#define MAX_SIZE 100


void push(int stack[], int *top, int maxSize);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);
void clearScreen();

int main() {
    int stack[MAX_SIZE];
    int top = -1;  
    int choice;

    do {
        printf("\n=== Stack Operations Menu ===\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                push(stack, &top, MAX_SIZE);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

        if (choice != 5) {
            printf("\nPress Enter to continue...");
            getchar(); 
            getchar();
            clearScreen(); 
        }

    } while(choice != 5);

    return 0;
}

void clearScreen() {
    system("cls");
}

void push(int stack[], int *top, int maxSize) {
    if(*top == maxSize - 1) {
        printf("Stack Overflow! Cannot push more elements.\n");
        return;
    }

    int element;
    printf("Enter element to push: ");
    scanf("%d", &element);

    (*top)++;
    stack[*top] = element;
    printf("Element %d pushed to stack.\n", element);
}

void pop(int stack[], int *top) {
    if(*top == -1) {
        printf("Stack Underflow! No elements to pop.\n");
        return;
    }

    int poppedElement = stack[*top];
    (*top)--;
    printf("Element %d popped from stack.\n", poppedElement);
}

void peek(int stack[], int top) {
    if(top == -1) {
        printf("Stack is empty. Nothing to peek.\n");
        return;
    }

    printf("Top element is: %d\n", stack[top]);
}

void display(int stack[], int top) {
    if(top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements (top to bottom):\n");
    int i;
    for(i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}

