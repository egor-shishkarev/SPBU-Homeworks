#pragma once

#include <stdio.h>

// ��������� - ������, ����������� ��� ���������� ����� �������.
typedef struct List List;

// ������� ������ �������, ������������� ������ �������.
void printRoadTable(int** roadTable, const int countOfCities);

// �������, ������� ���������� ������ �� ����� � �������.
int** readFromFileToTable(FILE* file, int* countOfCities, int* countOfRoads);

// �������, ������� ������������ ������ �� ��������, ������ �� ���������� ����� ��������.
List** distributeCitiesByCapitals(FILE* filePath, int** roadTable, int countOfCities, int countOfCapitals);