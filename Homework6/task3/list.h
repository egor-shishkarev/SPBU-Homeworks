#pragma once
typedef struct List List;
List* createList(void);
int insert(List* list, char name[], char phone[], const int position, int* errorCode);
char* getName(List* list, int position);
char* getPhone(List* list, int position);