#pragma once

#include <stdio.h>

// Структура - список, необходимая для добавления новых городов.
typedef struct List List;

// Выводит список городов, принадлежащих каждой столице.
void printRoadTable(int** roadTable, const int countOfCities);

// Функция, которая записывает дороги из файла в таблицу.
int** readFromFileToTable(FILE* file, int* countOfCities, int* countOfRoads);

// Функция, которая распределяет города по столицам, исходя из расстояния между городами.
List** distributeCitiesByCapitals(FILE* filePath, int** roadTable, int countOfCities, int countOfCapitals);