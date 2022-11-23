#include "hashTable.h"
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main(void) {
	setlocale(LC_ALL, ".1251");
	int hashSize = 1;
	List** hashTable = createTable(hashSize);
	FILE* file = fopen("text.txt", "r");
	int numberOfElements = 0;
	int errorCode = 0;
	List* listOfWords = createList();
 	while (!feof(file)) {
		char* buffer = calloc(100, sizeof(char));
		if (buffer == NULL) {
			return -1;
		}
		int currentChar = getc(file);
		int currentPosition = 0;
		while (currentChar != 32 && currentChar != -1 && currentChar != 10) {
			if (currentChar == 46 || currentChar == 44) {
				currentChar = getc(file);
				continue;
			}
			if (currentChar >= 65 && currentChar <= 90) {
				currentChar += 32;
			}
			buffer[currentPosition] = (char)currentChar;
			++currentPosition;
			currentChar = getc(file);
		}
		if (!strcmp(buffer, "")) {
			free(buffer);
			continue;
		}
		if (!isElementInList(listOfWords, buffer)) {
			++numberOfElements;
		}
		insertElement(listOfWords, buffer, 1);
		addElement(hashTable, buffer, 1, hashSize);
		if (hashSize <= numberOfElements) {
			hashTable = increaseTable(hashTable, hashSize, (int)ceil(1.05 * numberOfElements), &errorCode);
			hashSize = (int)ceil(1.05 * numberOfElements);
		}
		free(buffer);
		/*for (int i = 0; i < hashSize; ++i) {
			printf("%d - ый список\n", i + 1);
			printAllElements(hashTable[i]);
		}*/
	}
	fclose(file);
	int* listDepth = calloc(hashSize, sizeof(int));
	int sumOfDepths = 0;
	int maxDepth = 0;
	for (int i = 0; i < hashSize; ++i) {
		printf("%d-й список\n", i + 1);
		listDepth[i] = depthOfList(hashTable[i]);
		if (listDepth[i] > maxDepth) {
			maxDepth = listDepth[i];
		}
		sumOfDepths += listDepth[i];
		printAllElements(hashTable[i]);
	}
	printf("Коэффициент заполнения таблицы - %f\n", (float)sumOfDepths / hashSize);
	printf("Максимальная длина списка - %d\n", maxDepth);
	printf("Средняя длина списка - %f\n", (float)sumOfDepths / hashSize);
	for (int i = 0; i < hashSize; ++i) {
		deleteList(&hashTable[i]);
	}
	free((*hashTable));
	return 0;
}
