#pragma once
#include <stdbool.h>
//
typedef struct List List;
//
typedef struct Position Position;
//
List* createList();
//
Position* createPosition(List* list);
//
int deletePosition(List* list, Position* position, int* errorCode);
//
void deletePositionMemory(Position** position);
//
int getNextPosition(Position* position);
//
bool oneLeft(List* list);
//
int insert(List* list, const int value, const int position);
//
void clearList(List** list);
