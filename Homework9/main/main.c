//#include "hashTable.h"
#include "hashTable.h"
#include <stdio.h>
#include <locale.h>

int main(void) {
	setlocale(LC_ALL, ".1251");
	const int hashSize = 10;
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
		addElement(hashTable, buffer, hashSize);
		free(buffer);
	}
	fclose(file);
	for (int i = 0; i < hashSize; ++i) {
		printf("%d-й список\n", i + 1);
		printAllElements(hashTable[i]);
	}
	return 0;
}

/*Посчитать частоты встречаемости слов в тексте с помощью хеш-таблицы. 
На входе файл с текстом, вывести на консоль все слова, встречающиеся 
в этом тексте с количеством раз, которое встречается каждое слово. 
Словом считается последовательность символов, разделённая пробелами, 
разные словоформы считаются разными словами. Хеш-таблицу реализовать в 
отдельном модуле, использующем модуль «Список». Подсчитать и вывести 
также коэффициент заполнения хеш-таблицы, максимальную и среднюю длину списка в сегменте таблицы.

Количество "бесплатных" попыток сдачи — 3.*/

