#include "capitals.h"
#include "list.h"
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <malloc.h>

int verificationIntScanf(void) {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		printf("Было введено нецелочисленное значение! \n");
	}
	return readValues;
}

bool test(void) {
	int countOfCities = 0;
	int countOfRoads = 0;
	FILE* file = fopen("test.txt", "r");
	int** roadTable = readFromFileToTable(file, &countOfCities, &countOfRoads);
	int table[25] = { 0, 0, 0, 1, 5, 
					  0, 0, 3, 0, 4, 
					  0, 3, 0, 0, 2, 
					  1, 0, 0, 0, 0, 
					  5, 4, 2, 0, 0 };
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (roadTable[i][j] != table[5 * i + j]) {
				return false;
			}
		}
	}
	int countOfCapitals = 0;
	fscanf(file, "%d", &countOfCapitals);
	List** capitals = distributeCitiesByCapitals(file, roadTable, countOfCities, countOfCapitals);
	int firstCapital[3] = { 3, 5, 2 };
	int secondCapital[2] = { 4, 1 };
	bool firstTest = listElement(capitals[0], 0) == firstCapital[0] && listElement(capitals[0], 1) == firstCapital[1] && listElement(capitals[0], 2) == firstCapital[2];
	bool secondTest = listElement(capitals[1], 0) == secondCapital[0] && listElement(capitals[1], 1) == secondCapital[1];
	bool result = firstTest && secondTest;
	for (int i = 0; i < countOfCities; ++i) {
		free(roadTable[i]);
	}
	free(roadTable);
	for (int i = 0; i < countOfCapitals; ++i) {
		deleteList(&capitals[i]);
	}
	free(capitals);
	return result;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!test()) {
		printf("Тесты не были пройдены!");
		return -1;
	}
	printf("Тесты пройдены успешно!\n");
	int countOfCities = 0;
	int countOfRoads = 0;
	FILE* file = fopen("states.txt", "r");
	int** roadTable = readFromFileToTable(file, &countOfCities, &countOfRoads);
	int countOfCapitals = 0;
	fscanf(file, "%d", &countOfCapitals);
	List** capitals = distributeCitiesByCapitals(file, roadTable, countOfCities, countOfCapitals);
	printf("Список столиц и городов их государства: \n");
	for (int i = 0; i < countOfCapitals; ++i) {
		printList(capitals[i]);
		printf("\n");
	}
 	for (int i = 0; i < countOfCities; ++i) {
		free(roadTable[i]);
	}
	free(roadTable);
	for (int i = 0; i < countOfCapitals; ++i) {
		deleteList(&capitals[i]);
	}
	free(capitals);
	return 0;
}