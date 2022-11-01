#include "list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* previous;
} Node;

typedef struct List {
    Node* head;
} List;

int insert(List* list, int value) {
    if (list == NULL) {
        return -1;
    }

    Node* temp = malloc(sizeof(Node));
    if (temp == NULL) {
        return 1;
    }

    if (list->head == NULL) {
        temp->value = value;
        temp->previous = NULL;
        temp->next = NULL;
        list->head = temp;
        return 0;
    }

    Node* currentNode = list->head;
    while (currentNode->next != NULL) {
        if (currentNode->value >= value) {
            break;
        }
        currentNode = currentNode->next;
    }
    bool isEnd = currentNode->value < value;

    if (isEnd) {
        temp->value = value;
        temp->previous = currentNode;
        temp->next = NULL;
        currentNode->next = temp;
        return 0;
    }
    if (currentNode->previous != NULL) {
        currentNode->previous->next = temp;
    }
    temp->value = value;
    temp->previous = currentNode->previous;
    currentNode->previous = temp;
    temp->next = currentNode;
    if (list->head == currentNode) {
        list->head = temp;
    }
    return 0;
}

int getValue(List* list, int* errorCode) {
    if (list == NULL || list->head == NULL) {
        *errorCode = -1;
        return 0;
    }
    return list->head->value;
}

int deleteElement(List* list, int value) {
    if (list == NULL) {
        return -1;
    }
    bool isEnd = false;
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        if (currentNode->value == value) {
            break;
        }
        currentNode = currentNode->next;
    }

    if (currentNode == NULL) {
        return -1;
    }
    if (currentNode->previous != NULL) {
        currentNode->previous->next = currentNode->next;
    }
    else {
        list->head = currentNode->next;
    }
    if (currentNode->next != NULL) {
        currentNode->next->previous = currentNode->previous;
    }
    free(currentNode);
    return 0;
}

void deleteList(List** list) {
    if (*list == NULL) {
        free(*list);
        return;
    }
    Node* currentNode = (*list)->head;
    while (currentNode != NULL) {
        deleteElement(*list, currentNode->value);
        currentNode = (*list)->head;
    }
    free(*list);
    *list = NULL;
}

List* createList(void) {
    List* temp = malloc(sizeof(List));
    temp->head = NULL;
    return temp;
}

void printList(List* list) {
    if (list == NULL) {
        return -1;
    }
    printf("Отсортированный список: \n");
    Node* temp = list->head;
    if (temp == NULL) {
        printf("Список пуст!");
    }
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}