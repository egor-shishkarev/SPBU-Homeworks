#include "hashTable.h"
#include <stdio.h>
#include <locale.h>

int main(void) {
	setlocale(LC_ALL, ".1251");
	const int hashSize = 37;
	List** hashTable = createTable(hashSize);
	FILE* file = fopen("text.txt", "r");
 	while (!feof(file)) {
		char* buffer = calloc(100, sizeof(char));
		int currentChar = getc(file);
		int currentPosition = 0;
		while (currentChar != 32 && currentChar != -1) {
			buffer[currentPosition] = (char)currentChar;
			++currentPosition;
			currentChar = getc(file);
		}
		if (!strcmp(buffer, "")) {
			free(buffer);
			continue;
		}
		addElement(hashTable, buffer, hashSize);
		free(buffer);
	}
	fclose(file);
	int* listDepth = calloc(hashSize, sizeof(int));
	int sumOfDepths = 0;
	int maxDepth = 0;
	for (int i = 0; i < hashSize; ++i) {
		//printf("%d-й список\n", i + 1);
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
