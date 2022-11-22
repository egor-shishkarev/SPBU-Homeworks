#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
typedef struct Node Node;
typedef struct List List;
List* createList(void);
void insertElement(List* list, const char* value, const int count);
void printList(List* list);
void deleteList(List** list);
void eraseList(List* list);
bool isElementInList(List* list, const char* value);