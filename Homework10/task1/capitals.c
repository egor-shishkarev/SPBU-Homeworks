#include "list.h"
#include "capitals.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node {
	int number;
	Node* next;
} Node;

typedef struct List {
	Node* head;
	Node* tail;
} List;

int** readFromFileToTable(FILE* file, int* countOfCities, int* countOfRoads) {
	fscanf(file, "%d", countOfCities);
	fscanf(file, "%d", countOfRoads);
	int** roadTable = (int**)calloc(*countOfCities, sizeof(int*));
	if (roadTable == NULL) {
		printf("Память не была выделена.");
		return NULL;
	}
	for (int i = 0; i < *countOfCities; ++i) {
		roadTable[i] = (int*)calloc(*countOfCities, sizeof(int));
		if (roadTable[i] == NULL) {
			for (int j = 0; j < i; ++j) {
				free(roadTable[j]);
			}
			printf("Память не была выделена.");
			return NULL;
		}
	}
	int numberOfEnterRoads = 0;
	while (true) {
		if (numberOfEnterRoads == *countOfRoads) {
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
		if (secondNumberOfCity > *countOfCities) {
			printf("Такого города нет! Проверьте файл.\n");
			return NULL;
		}
		roadTable[firstNumberOfCity - 1][secondNumberOfCity - 1] = lengthOfRoad;
		roadTable[secondNumberOfCity - 1][firstNumberOfCity - 1] = lengthOfRoad;
		++numberOfEnterRoads;
	}
	return roadTable;
}

void nullColumn(int** roadTable, const int numberOfCities, const int numberOfColumn) {
	for (int i = 0; i < numberOfCities; ++i) {
		roadTable[i][numberOfColumn] = 0;
	}
}

void nullAllRoadsBetweenCapitals(int** roadTable, const int numberOfCapitals, List** capitals) {
	for (int i = 0; i < numberOfCapitals; ++i) {
		for (int j = i + 1; j < numberOfCapitals; ++j) {
			const int firstCity = capitals[i]->head->number;
			const int secondCity = capitals[j]->head->number;
			roadTable[firstCity][secondCity] = 0;
			roadTable[secondCity][firstCity] = 0;
		}
	}
}

int findMinimumLength(int** roadTable, const int numberOfCities, const int numberOfCity, int* currentMinimum, const int newCity) {
	int currentCity = newCity;
	for (int i = 0; i < numberOfCities; ++i) {
		if (roadTable[numberOfCity][i] < *currentMinimum && roadTable[numberOfCity][i] != 0) {
			*currentMinimum = roadTable[numberOfCity][i];
			currentCity = i;
		}
	}
	return currentCity;
}

int findNewCity(int** roadTable, List* list, const int numberOfCities) {
	int currentMinimum = INT_MAX;
	Node* currentNode = list->head;
	int newSity = list->tail->number;
	while (currentNode != NULL) {
		newSity = findMinimumLength(roadTable, numberOfCities, currentNode->number, &currentMinimum, newSity);
		currentNode = currentNode->next;
	}
	if (newSity == list->tail->number) {
		return 0;
	}
	insertElement(list, newSity);
	nullColumn(roadTable, numberOfCities, newSity);
	Node* firstElement = list->head;
	Node* secondElement = list->head->next;
	while (true) {
		if (firstElement->next == NULL) {
			break;
		}
		while (secondElement != NULL) {
			roadTable[firstElement->number][secondElement->number] = 0;
			roadTable[secondElement->number][firstElement->number] = 0;
			secondElement = secondElement->next;
		}
		firstElement = firstElement->next;
	}
	return 1;
}

List** distributeCitiesByCapitals(FILE* file, int** roadTable, int countOfCities, int countOfCapitals) {
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
			numberOfRemainingCities -= findNewCity(roadTable, capitals[countOfCapitals - currentNumberOfCapitals], countOfCities);
			--currentNumberOfCapitals;
		}
	}
	return capitals;
}

void printRoadTable(int** roadTable, const int countOfCities) {
	printf("\n");
	for (int i = 0; i < countOfCities; ++i) {
		for (int j = 0; j < countOfCities; ++j) {
			printf("[%d][%d] = %d ", i, j, roadTable[i][j]);
		}
		printf("\n");
	}
}