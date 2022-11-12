#pragma once
#include "list.h"
#include <string.h>
#include <math.h>
typedef struct List List;
List** createTable(const int size);
void addElement(List** hashTable, const char* value, const int hashSize);
void printAllElements(List* list);
int depthOfList(List* list);