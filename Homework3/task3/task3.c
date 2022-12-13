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

int insertionSort(int* arrayOfNumbers, const int firstIndex, const int lastIndex) {
    if (arrayOfNumbers == NULL || firstIndex < 0 || lastIndex < 0 || lastIndex < firstIndex) {
        return -1;
    }
    int sortElement = firstIndex + 1;
    while (sortElement <= lastIndex) {
        int currentElement = sortElement;
        while (arrayOfNumbers[currentElement] < arrayOfNumbers[currentElement - 1] && currentElement >= firstIndex + 1) {
            const int buffer = arrayOfNumbers[currentElement - 1];
            arrayOfNumbers[currentElement - 1] = arrayOfNumbers[currentElement];
            arrayOfNumbers[currentElement] = buffer;
            --currentElement;
        }
        ++sortElement;
    }
    return 0;
}

int smartQuickSort(int* arrayOfNumbers, int firstIndex, int lastIndex) {
    if (arrayOfNumbers == NULL || firstIndex > lastIndex || firstIndex < 0 || lastIndex < 0) {
        return -1;
    }
    int left = firstIndex;
    int right = lastIndex;
    int middle = arrayOfNumbers[(left + right) / 2];
    if (lastIndex - firstIndex < 9) {
        return insertionSort(arrayOfNumbers, firstIndex, lastIndex);
    }
    do {
        while (arrayOfNumbers[left] < middle) {
            ++left;
        }
        while (arrayOfNumbers[right] > middle) {
            --right;
        }
        if (left <= right) {
            const int buffer = arrayOfNumbers[left];
            arrayOfNumbers[left] = arrayOfNumbers[right];
            arrayOfNumbers[right] = buffer;
            ++left;
            --right;
        }
    } while (left <= right);
    smartQuickSort(arrayOfNumbers, firstIndex, right);
    smartQuickSort(arrayOfNumbers, left, lastIndex);
    return 0;
}

int maxCountInSortArray(int* arrayOfNumbers, const int lengthOfArray) {
    if (arrayOfNumbers == NULL || lengthOfArray <= 0) {
        return NULL;
    }
    int element = arrayOfNumbers[0];
    int countOfElements = 0;
    int maxCount = 1;
    int currentElement = element;
    for (int i = 0; i < lengthOfArray; ++i) {
        if (arrayOfNumbers[i] == currentElement) {
            ++countOfElements;
        } else {
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

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!(correctCase() && incorrectCase() && testInsertionSort() && testQuickSort())) {
        printf("Тесты не пройдены!");
        return -1;
    }
    printf("Тесты пройдены!\n");
    printf("Данная программа находит наиболее часто встречающийся элемент в массиве.\nЕсли хотите ввести свой массив - введите 1. \nЕсли хотите увидеть пример - введите 0. => ");
    const int flagOfMode = verificationIntScanf();
    if (flagOfMode != 1 && flagOfMode != 0) {
        printf("Значение не было распознано, работа программы завершена.");
        return 1;
    }
    printf("Введите длину массива => ");
    const int numberOfElements = verificationIntScanf();
    int* arrayOfNumbers = calloc(numberOfElements, sizeof(int));
    if (arrayOfNumbers == NULL) {
        printf("Произошла ошибка, массив не был создан.");
        return -1;
    }
    switch (flagOfMode) {
    case 0:
        srand(time(NULL));
        for (int i = 0; i < numberOfElements; ++i) {
            arrayOfNumbers[i] = rand() % 10 + 1;
        }
        break;
    case 1:
        printf("Вводите элементы через enter => ");
        for (int i = 0; i < numberOfElements; ++i) {
            arrayOfNumbers[i] = verificationIntScanf();
        }
        break;
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