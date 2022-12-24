#pragma once
//
typedef struct Node Node;
//
typedef struct List List;
//
int findNewSity(int** roadTable, List* list, const int numberOfSities);
//
void nullAllRoadsBetweenCapitals(int** roadTable, const int numberOfCities, List** capitals);
//
printRoadTable(int** roadTable, const int countOfCities);