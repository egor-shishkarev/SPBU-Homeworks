#pragma once

// —труктура - список, необходима€ дл€ добавлени€ новых городов.
typedef struct List List;

// ѕозвол€ет находить новый незан€тый город, с минимальным рассто€нием до него.
int findNewSity(int** roadTable, List* list, const int numberOfSities);

// ‘ункци€, котора€ обнул€ет длину дорог между столицами.
void nullAllRoadsBetweenCapitals(int** roadTable, const int numberOfCities, List** capitals);

// ¬ыводит список городов, принадлежащих каждой столице.
void printRoadTable(int** roadTable, const int countOfCities);