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

void nullColumn(int** roadTable, const int numberOfCities, const int numberOfColumn) {
	for (int i = 0; i < numberOfCities; ++i) {
		roadTable[i][numberOfColumn] = 0;
	}
}


int findNewSity(int** roadTable, List* list, const int numberOfCities) {
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

void printRoadTable(int** roadTable, const int countOfCities) {
	printf("\n");
	for (int i = 0; i < countOfCities; ++i) {
		for (int j = 0; j < countOfCities; ++j) {
			printf("[%d][%d] = %d ", i, j, roadTable[i][j]);
		}
		printf("\n");
	}
}