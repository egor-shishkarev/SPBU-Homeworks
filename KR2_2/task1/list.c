#include "list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* previous;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
    Node* a;
    Node* b;
} List;

int insert(List* list, int value) {
    if (list == NULL) {
        return NULL;
    }
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->value = value;
    if (list->head == NULL) {
        list->head = newNode;
        newNode->previous = NULL;
        newNode->next = NULL;
        list->tail = newNode;
        list->a = newNode;
        return 0;
    }
    if (list->b == NULL) {
        list->head->next = newNode;
        newNode->previous = list->head;
        newNode->next = NULL;
        list->tail = newNode;
        list->b = newNode;
        return 0;
    }

    if (value < list->a->value) {
        newNode->next = list->a;
        newNode->previous = list->a->previous;
        if (list->a->previous != NULL) {
            list->a->previous->next = newNode;
        }
        if (list->a->previous == NULL) {
            list->head = newNode;
        }
        list->a->previous = newNode;
    } else if (value >= list->a->value && value <= list->b->value) {
        newNode->next = list->b;
        newNode->previous = list->b->previous;
        list->b->previous->next = newNode;
        list->b->previous = newNode;
    } else {
        newNode->previous = list->tail;
        list->tail->next = newNode;
        newNode->next = NULL;
        list->tail = newNode;
    }
    return 0;
}

int deleteElement(List* list, const int value) {
    if (list == NULL) {
        return -1;
    }
    Node* currentNode = list->head;
    while (currentNode != NULL && currentNode->value != value) {
        currentNode = currentNode->next;
    }
    if (currentNode == NULL) {
        return -1;
    }
    if (currentNode->previous != NULL) {
        currentNode->previous->next = currentNode->next;
    } else {
        list->head = currentNode->next;
    }
    if (currentNode->next != NULL) {
        currentNode->next->previous = currentNode->previous;
    }
    free(currentNode);
}

List* createList(const int a, const int b) {
    List* list = malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->a = NULL;
    list->b = NULL;
    list->head = NULL;
    list->tail = NULL;
    insert(list, a);
    insert(list, b);
    return list;
}

void printListInFile(List* list, const char* g) {
    FILE* file = fopen(g, "w");
    if (file == NULL) {
        file = fopen(g, "a");
        fclose(file);
    }
    file = fopen(g, "w");
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        fprintf(file, "%d", currentNode->value);
        fprintf(file, "%s", " ");
        currentNode = currentNode->next;
    }
    fclose(file);
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