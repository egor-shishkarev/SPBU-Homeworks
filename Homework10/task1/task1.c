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

int main(void) {
	setlocale(LC_ALL, ".1251");
	FILE* file = fopen("states.txt", "r");
	int countOfCities = 0;
	fscanf(file, "%d", &countOfCities);
	int countOfRoads = 0;
	fscanf(file, "%d", &countOfRoads);
	int** roadTable = (int** )calloc(countOfCities, sizeof(int*));
	if (roadTable == NULL) {
		printf("Память не была выделена.");
		return -1;
	}
	for (int i = 0; i < countOfCities; ++i) {
		roadTable[i] = (int*)calloc(countOfCities, sizeof(int));
		if (roadTable[i] == NULL) {
			printf("Память не была выделена.");
			return -1;
		}
	}
	int numberOfEnterRoads = 0;
	while (true) {
		if (numberOfEnterRoads == countOfRoads) {
			break;
		}
		int firstNumberOfCity = 0;
		int secondNumberOfCity = 0;
		fscanf(file, "%d", &firstNumberOfCity);
		fscanf(file, "%d", &secondNumberOfCity);
		if (firstNumberOfCity > secondNumberOfCity) {
			firstNumberOfCity = firstNumberOfCity ^ secondNumberOfCity;
			secondNumberOfCity = firstNumberOfCity ^ secondNumberOfCity;
			firstNumberOfCity = firstNumberOfCity ^ secondNumberOfCity;
		}
		int lengthOfRoad = 0;
		fscanf(file, "%d", &lengthOfRoad);
		if (secondNumberOfCity > countOfCities) {
			printf("Такого города нет! Проверьте файл.\n");
			return -1;
		}
		roadTable[firstNumberOfCity - 1][secondNumberOfCity - 1] = lengthOfRoad;
		roadTable[secondNumberOfCity - 1][firstNumberOfCity - 1] = lengthOfRoad;
		++numberOfEnterRoads;
	}
	int countOfCapitals = 0;
	fscanf(file, "%d", &countOfCapitals);
	List** capitals = calloc(countOfCapitals, sizeof(List*));
	for (int i = 0; i < countOfCapitals; ++i) {
		capitals[i] = createList();
		int numberOfCapital = 0;
		fscanf(file, "%d", &numberOfCapital);
		insertElement(capitals[i], numberOfCapital - 1);
	}
	nullAllRoadsBetweenCapitals(roadTable, countOfCapitals, capitals);
	int numberOfRemainingCities = countOfCities - countOfCapitals;
	while (numberOfRemainingCities > 0) {
		int currentNumberOfCapitals = countOfCapitals;
		while (currentNumberOfCapitals > 0) {
			//printRoadTable(roadTable, countOfCities);
			numberOfRemainingCities -= findNewSity(roadTable, capitals[countOfCapitals - currentNumberOfCapitals], countOfCities);
			--currentNumberOfCapitals;
		}
	}
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
		deleteList(capitals[i]);
	}
	free(capitals);
	return 0;
}