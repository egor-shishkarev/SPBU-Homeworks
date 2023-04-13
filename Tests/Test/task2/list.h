#pragma once
// 
typedef struct List List;
// 
int insert(List* list, char* value);
// 
void deleteTopElement(List* list);
// 
void deleteList(List** list);
// 
List* createList(void);
// 
void printList(List* list);
//
void addAStrings(List* list);