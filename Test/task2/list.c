#include "list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
} List;

int insert(List* list, char* value) {
    if (list == NULL) {
        return -1;
    }
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        return 1;
    }
    char* newValue = calloc(strlen(value) + 1, sizeof(char));
    strcpy(newValue, value);
    newNode->value = newValue;
    if (list->head == NULL) {
        newNode->next = NULL;
        list->head = newNode;
        list->tail = newNode;
        return 0;
    }
    Node* currentNode = list->head;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
    newNode->next = NULL;
    list->tail = newNode;
    return 0;
}

void deleteTopElement(List* list) {
    Node* currentNode = list->head;
    Node* newCurrentNode = currentNode->next;
    free(currentNode->value);
    free(currentNode);
    currentNode = NULL;
    list->head = newCurrentNode;
}

void deleteList(List** list) {
    if (*list == NULL) {
        free(*list);
        return;
    }
    while ((*list)->head != NULL) {
        deleteTopElement(*list);
    }
    free(*list);
    *list = NULL;
}

List* createList(void) {
    List* temp = malloc(sizeof(List));
    temp->head = NULL;
    temp->tail = NULL;
    return temp;
}

void addAStrings(List* list) {
    Node* currentNode = list->head;
    insert(list, (char)-1);
    while (currentNode->value != (char)-1) {
        if (currentNode->value[0] == 'a') {

        }
    }
}

void printList(List* list) {
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        printf("%s\n", currentNode->value);
        currentNode = currentNode->next;
    }
}