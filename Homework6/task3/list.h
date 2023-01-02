#pragma once

//
typedef struct Node Node;

// 
typedef struct List List;

//
List* createList(void);

//
void insert(List* list, const char name[], const char phone[], const int position, int* errorCode);

//
char* getName(List* list, int position);

//
char* getPhone(List* list, int position);

//
List* mergeSort(List* listFirst, List* listSecond, const int countFirst, const int countSecond);

//
Node* getNextPosition(Node* head);