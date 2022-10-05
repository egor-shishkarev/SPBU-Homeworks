//Реализовать сортировку выбором только элементов массива с чётными индексами. Например, массив [5, 4, 3, 2, 1] должен быть отсортирован как [1, 4, 3, 2, 5]. 
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>

int verificationIntScanf() {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		printf("Ошибка ввода. Введите целочисленное значение!\n");
	}
	return readValues;
}

void choiceSortEven(int *arrayOfNumbers,const int lengthOfArray) {
	int currentElement = 0;
	while (currentElement < lengthOfArray) {
		while (arrayOfNumbers[currentElement] < arrayOfNumbers[currentElement - 2] && currentElement >= 2) {
			const int buffer = arrayOfNumbers[currentElement - 2];
			arrayOfNumbers[currentElement - 2] = arrayOfNumbers[currentElement];
			arrayOfNumbers[currentElement] = buffer;
			currentElement -= 2;
		}
		currentElement += 2;
	}
}

bool testSort(int *rightArrayOfNumbers, int *arrayOfNumbers,const int lengthOfArray) {
	choiceSortEven(arrayOfNumbers, lengthOfArray);
	bool allIsRight = true;
	for (int i = 0; i < lengthOfArray; ++i) {
		if (rightArrayOfNumbers[i] != arrayOfNumbers[i]) {
			allIsRight = false;
			break;
		}
	}
	return allIsRight;
}

bool test1() {
	int arrayOfNumbers[5] = { 5,4,3,2,1 };
	int rightArray[5] = { 1,4,3,2,5 };
	return testSort(rightArray, arrayOfNumbers, 5);
}

bool test2() {
	int arrayOfNumbers[10] = { 8,9,5,4,7,3,9,2,1,5};
	int rightArray[10] = { 1,9,5,4,7,3,8,2,9,5 };
	return testSort(rightArray, arrayOfNumbers, 10);
}

int main() {
	setlocale(LC_ALL, ".1251");
	if (!test1() && test2()) {
		printf("Тесты не пройдены!");
		return 1;
	}
	printf("Тесты успешно пройдены!\n");
	printf("Данная программа сортирует вставками только числа, стоящие на четных индексах.\nВведите число элементов массива => ");
	int numberOfElements = verificationIntScanf();
	int* arrayOfNumbers = (int*)calloc(numberOfElements, sizeof(int));
	printf("Вводите элементы массива через Enter:\n");
	for (int i = 0; i < numberOfElements; ++i) {
		arrayOfNumbers[i] = verificationIntScanf();
	}
	choiceSortEven(arrayOfNumbers, numberOfElements);
	for (int i = 0; i < numberOfElements; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	free(arrayOfNumbers);
	return 0;
}