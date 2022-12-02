#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

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

bool binarySearch(int* arrayOfNumbers, const int lengthOfArray, const int elementToSearch) {
    if (lengthOfArray <= 0 || arrayOfNumbers == NULL) {
        return -1;
    }
    int left = -1;
    int right = lengthOfArray;
    while (left + 1 != right) {
        const int middle = (left + right) / 2;
        if (arrayOfNumbers[middle] < elementToSearch) {
            left = middle;
        } else if (arrayOfNumbers[middle] == elementToSearch) {
            return true;
        }
        else {
            right = middle;
        }
    }
    return arrayOfNumbers[right] == elementToSearch;
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

bool testSearch(int* arrayOfNumbers, const int lengthOfArray, const int numberToSearch) {
    const int result = smartQuickSort(arrayOfNumbers, 0, lengthOfArray - 1);
    return binarySearch(arrayOfNumbers, lengthOfArray, numberToSearch) && result == 0;
}

bool correctCase(void) {
    int arrayOfNumbers[20] = { 1242, 23, 235, 25325, 253, 676, 897, 214, 1243, 546, 5767, 4446, 6118, 984, 100, 365, 784, 1, 20, 36 };
    smartQuickSort(arrayOfNumbers, 0, 19);
    for (int i = 0; i < 20; ++i) {
        if (!testSearch(arrayOfNumbers, 20, arrayOfNumbers[i])) {
            return false;
        }
    }
    return !testSearch(arrayOfNumbers, 20, 101) && !testSearch(arrayOfNumbers, 20, 2);
}

bool incorrectCase(void) {
    int arrayOfNumbers[1] = { 0 };
    return !testSearch(arrayOfNumbers, 0, 0);
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!(correctCase() && incorrectCase() && testQuickSort() && testInsertionSort())) {
        printf("Тесты не пройдены!");
        return -1;
    }
    printf("Тесты пройдены!\n");
    printf("Введите два числа через Enter. \nПервое - количество элементов массива, \nвторое - количество случайных чисел, для которых вы хотите проверить - содержатся они в сгенерированном массиве или нет => ");
    const int numberOfElements = verificationIntScanf();
    int *arrayOfNumbers = calloc(numberOfElements, sizeof(int));
    if (arrayOfNumbers == NULL) {
        printf("Произошла ошибка, массив не был создан.");
        return 1;
    }
    const int numberToSearch = verificationIntScanf();
    int *arrayToSearch = calloc(numberToSearch, sizeof(int));
    if (arrayToSearch == NULL) {
        printf("Произошла ошибка, массив не был создан.");
        return 1;
    }
    srand(time(NULL));
    for (int i = 0; i < numberOfElements; ++i) {
        arrayOfNumbers[i] = rand() % 100 + 1;
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
    for (int i = 0; i < numberToSearch; ++i) {
        arrayToSearch[i] = rand() % 100 + 1;
    }
    smartQuickSort(arrayToSearch, 0, numberToSearch - 1);
    printf("\nМассив для поиска: \n");
    for (int i = 0; i < numberToSearch; ++i) {
        printf("%d ", arrayToSearch[i]);
    }
    int currentNumber = -1;
    for (int i = 0; i < numberToSearch; ++i) {
        if (currentNumber == arrayToSearch[i] && i != 0) {
            continue;
        }
        const bool result = binarySearch(arrayOfNumbers, numberOfElements, arrayToSearch[i]);
        printf("\n%d - %s", arrayToSearch[i], result ? "true" : "false");
        currentNumber = arrayToSearch[i];
        
    }
    free(arrayOfNumbers);
    free(arrayToSearch);
    return 0;
}