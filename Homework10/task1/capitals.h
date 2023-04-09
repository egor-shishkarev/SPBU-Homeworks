#pragma once

#include <stdio.h>

// ��������� - ������, ����������� ��� ���������� ����� �������.
typedef struct List List;

// ��������� �������� ����� ��������� �����, � ����������� ����������� �� ����.
int findNewSity(int** roadTable, List* list, const int numberOfSities);

// �������, ������� �������� ����� ����� ����� ���������.
void nullAllRoadsBetweenCapitals(int** roadTable, const int numberOfCities, List** capitals);

// ������� ������ �������, ������������� ������ �������.
void printRoadTable(int** roadTable, const int countOfCities);

// �������, ������� ���������� ������ �� ����� � �������.
int** readFromFileToTable(FILE* file, int* countOfCities, int* countOfRoads);

// �������, ������� ������������ ������ �� ��������, ������ �� ���������� ����� ��������.
List** distributeCitiesByCapitals(FILE* filePath, int** roadTable, int countOfCities, int countOfCapitals);