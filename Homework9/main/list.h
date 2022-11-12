#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct Node Node;
typedef struct List List;
List* createList(void);
void insertElement(List* list, const char* value);
void printList(List* list);