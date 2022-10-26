#include "stackModule.h"
#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    uncertainType value;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* head;
} Stack;

int push(Stack* stack, uncertainType value) {
    Node* temp = malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Память не была выделена.");
        return -1;
    }
    temp->value = value;
    temp->next = stack->head;

    stack->head = temp;
    return 0;
}

int pop(Stack* stack, int* errorCode) {
    if (isEmpty(stack)) {
        if (errorCode != NULL) {
            *errorCode = -1;
        }

        return 0;
    }
    if (errorCode != NULL) {
        *errorCode = 0;
    }

    uncertainType value = stack->head->value;

    Node* next = stack->head->next;
    free(stack->head);
    stack->head = next;

    return value;
}

bool isEmpty(Stack* stack) {
    return stack->head == NULL;
}

void deleteStack(Stack* stack) {
    while (!isEmpty(stack)) {
        int errorCode = 0;
        pop(stack, &errorCode);
    }
    free(stack);
}

Stack* createStack() {
    Stack* stack = malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

int top(Stack* stack) {
    return stack->head->value;
}

