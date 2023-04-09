#pragma once

#include <stdio.h>

// Структура - список, необходимая для добавления новых городов.
typedef struct List List;

// Позволяет находить новый незанятый город, с минимальным расстоянием до него.
int findNewSity(int** roadTable, List* list, const int numberOfSities);

// Функция, которая обнуляет длину дорог между столицами.
void nullAllRoadsBetweenCapitals(int** roadTable, const int numberOfCities, List** capitals);

// Выводит список городов, принадлежащих каждой столице.
void printRoadTable(int** roadTable, const int countOfCities);

// Функция, которая записывает дороги из файла в таблицу.
int** readFromFileToTable(FILE* file, int* countOfCities, int* countOfRoads);

// Функция, которая распределяет города по столицам, исходя из расстояния между городами.
List** distributeCitiesByCapitals(FILE* filePath, int** roadTable, int countOfCities, int countOfCapitals);