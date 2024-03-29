﻿#include "smartQuickSort.h"
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h> 
#include <locale.h>
#include <time.h>
#include <stdlib.h>

int verificationIntScanf(void) {
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

int maxCountInSortArray(int* arrayOfNumbers, const int lengthOfArray) {
    if (arrayOfNumbers == NULL || lengthOfArray <= 0) {
        return 0;
    }
    int element = arrayOfNumbers[0];
    int countOfElements = 0;
    int maxCount = 1;
    int currentElement = element;
    for (int i = 0; i < lengthOfArray; ++i) {
        if (arrayOfNumbers[i] == currentElement) {
            ++countOfElements;
        }
        else {
            if (countOfElements > maxCount) {
                maxCount = countOfElements;
                element = currentElement;
            }
            countOfElements = 1;
            currentElement = arrayOfNumbers[i];
        }
    }
    if (countOfElements > maxCount) {
        element = arrayOfNumbers[lengthOfArray - 1];
    }
    return element;
}

bool testQuickSort(void) {
    int arrayOfNumbers[10] = { 1, 6, 5, 3, 2, 6, 4, 8, 0, -5 };
    const int rightArray[10] = { -5, 0, 1, 2, 3, 4, 5, 6, 6, 8 };
    const int result = smartQuickSort(arrayOfNumbers, 0, 9);
    bool allAreTrue = true;
    for (int i = 0; i < 10; ++i) {
        if (rightArray[i] != arrayOfNumbers[i]) {
            allAreTrue = false;
            break;
        }
    }
    return allAreTrue && result == 0;
}

bool testInsertionSort(void) {
    int arrayOfNumbers[10] = { 1, 6, 5, 3, 2, 6, 4, 8, 0, -5 };
    const int rightArray[10] = { -5, 0, 1, 2, 3, 4, 5, 6, 6, 8 };
    const int result = insertionSort(arrayOfNumbers, 0, 9);
    bool allAreTrue = true;
    for (int i = 0; i < 10; ++i) {
        if (rightArray[i] != arrayOfNumbers[i]) {
            allAreTrue = false;
            break;
        }
    }
    return allAreTrue && result == 0;
}

bool testMostFrequentlyElement(int* arrayOfNumbers, const int lengthOfArray, const int rightNumber) {
    const int result = smartQuickSort(arrayOfNumbers, 0, lengthOfArray - 1);
    return result == 0 && maxCountInSortArray(arrayOfNumbers, lengthOfArray) == rightNumber;
}

bool correctCase(void) {
    int arrayOfNumbers[10] = { 7, 5, 6, 1, 2, 7, 12, 4, 4, 1 };
    return testMostFrequentlyElement(arrayOfNumbers, 10, 1) || testMostFrequentlyElement(arrayOfNumbers, 10, 4) || testMostFrequentlyElement(arrayOfNumbers, 10, 7);
}

bool incorrectCase(void) {
    int arrayOfNumbers[4] = { 1, 2, 3, 1 };
    return !testMostFrequentlyElement(arrayOfNumbers, 0, 1);
}

int* readArrayFromFile(const char* path, int* numberOfElements, int* errorCode) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return NULL;
    }
    fscanf(file, "%d", numberOfElements);
    int* arrayOfNumbers = calloc(*numberOfElements, sizeof(int));
    if (arrayOfNumbers == NULL) {
        fclose(file);
        *errorCode = -1;
        return NULL;
    }
    for (int i = 0; i < *numberOfElements; ++i) {
        fscanf(file, "%d", &arrayOfNumbers[i]);
    }
    fclose(file);
    return arrayOfNumbers;
}

bool readTest(void) {
    int numberOfElements = 0;
    int errorCode = 0;
    int* arrayFromFile = readArrayFromFile("test.txt", &numberOfElements, &errorCode);
    int rightArray[] = { 9, 7, 2, 1, 3, 4, 5, 2, 0, 9 };
    if (!(numberOfElements == 10 && errorCode == 0)) {
        free(arrayFromFile);
        return false;
    }
    for (int i = 0; i < 10; ++i) {
        if (arrayFromFile[i] != rightArray[i]) {
            free(arrayFromFile);
            return false;
        }
    }
    free(arrayFromFile);
    return true;
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!(correctCase() && incorrectCase() && testInsertionSort() && testQuickSort() && readTest())) {
        printf("Тесты не пройдены!");
        return -1;
    }
    printf("Тесты пройдены!\n");
    printf("Данная программа находит наиболее часто встречающийся элемент в массиве.\n");
    int numberOfElements = 0;
    int errorCode = 0;
    int* arrayOfNumbers = readArrayFromFile("array.txt", &numberOfElements, &errorCode);
    if (arrayOfNumbers == NULL) {
        printf("Произошла ошибка!");
        return -1;
    }
    if (errorCode != 0) {
        printf("Произошла ошибка при выделении памяти!");
        return -1;
    }
    printf("Созданный массив: \n");
    for (int i = 0; i < numberOfElements; ++i) {
        printf("%d ", arrayOfNumbers[i]);
    }
    smartQuickSort(arrayOfNumbers, 0, numberOfElements - 1);
    printf("\nОтсортированный массив: \n");
    for (int i = 0; i < numberOfElements; ++i) {
        printf("%d ", arrayOfNumbers[i]);
    }
    printf("\nНаиболее часто встречающийся элемент в массиве => %d", maxCountInSortArray(arrayOfNumbers, numberOfElements));
    free(arrayOfNumbers);
    return 0;
}