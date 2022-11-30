#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>

int bubbleSort(int* arrayOfNumbers, const int lengthOfArray) {
    if (arrayOfNumbers == NULL || lengthOfArray <= 0) {
        return -1;
    }
    for (int i = 0; i < lengthOfArray; ++i) {
        bool flagOfChanged = false;
        for (int j = lengthOfArray - 1; j > i; --j) {
            if (arrayOfNumbers[j] < arrayOfNumbers[j - 1]) {
                const int buffer = arrayOfNumbers[j];
                arrayOfNumbers[j] = arrayOfNumbers[j - 1];
                arrayOfNumbers[j - 1] = buffer;
                flagOfChanged = true;
            }
        }
        if (!flagOfChanged) {
            break;
        }
    }
    return 0;
}

int countSort(int* arrayOfNumbers, const int lengthOfArray) {
    if (arrayOfNumbers == NULL || lengthOfArray <= 0) {
        return -1;
    }
    int maxNumber = INT_MIN;
    int minNumber = INT_MAX;
    for (int i = 0; i < lengthOfArray; ++i) {
        maxNumber = max(maxNumber, arrayOfNumbers[i]);
        minNumber = min(minNumber, arrayOfNumbers[i]);
    }
    int* arrayForCount = calloc(maxNumber - minNumber + 1, sizeof(int));
    if (arrayForCount == NULL) {
        printf("Память не была выделена!");
        return -1;
    }
    for (int i = 0; i < lengthOfArray; ++i) {
        ++arrayForCount[arrayOfNumbers[i] - minNumber];
    }
    int currentElement = 0;
    for (int i = 0; i <= maxNumber - minNumber; ++i) {
        while (arrayForCount[i]) {
            arrayOfNumbers[currentElement] = i + minNumber;
            ++currentElement;
            --arrayForCount[i];
        }
    }
    free(arrayForCount);
    return 0;
}

bool testCountSort(void) {
    int arrayOfNumbers[10] = { 8, 1, 5, 6, 4, 9, 0, 3, 2, 7 };
    const int errorCode = countSort(arrayOfNumbers, 10);
    for (int i = 0; i < 10; ++i) {
        if (arrayOfNumbers[i] != i) {
            return false;
        }
    }
    return errorCode == 0;
}

bool testBubbleSort(void) {
    int arrayOfNumbers[10] = { 4, 2, 5, 1, 7, 3, 9, 8, 6, 0 };
    const int errorCode = bubbleSort(arrayOfNumbers, 10);
    for (int i = 0; i < 10; ++i) {
        if (arrayOfNumbers[i] != i) {
            return false;
        }
    }
    return errorCode == 0;
}

bool incorrectCase(void) {
    int* arrayOfNumbers = NULL;
    int rightArray[3] = { 1, 2, 3 };
    return bubbleSort(arrayOfNumbers, 0) == -1 && bubbleSort(rightArray, -1) == -1 & countSort(arrayOfNumbers, 0) == -1 && countSort(rightArray, -1) == -1;
}

int main() {
    setlocale(LC_ALL, ".1251");
    if (!(testBubbleSort() && testCountSort() && incorrectCase())) {
        printf("Тесты не были пройдены!");
        return -1;
    }
    printf("Тесты пройдены успешно!\n");
    srand(time(NULL));
    const int lengthOfArray = 10000;
    int* arrayOfNumbersForBubble = calloc(lengthOfArray, sizeof(int));
    if (arrayOfNumbersForBubble == NULL) {
        printf("Память не была выделена!");
        return -1;
    }
    for (int i = 0; i < lengthOfArray; ++i) {
        arrayOfNumbersForBubble[i] = rand();
    }
    int* arrayOfNumbersForCount = calloc(lengthOfArray, sizeof(int));
    if (arrayOfNumbersForCount == NULL) {
        printf("Память не была выделена!");
        return -1;
    }
    memcpy(arrayOfNumbersForCount, arrayOfNumbersForBubble, lengthOfArray);
    unsigned int startBubbleSort = clock();
    bubbleSort(arrayOfNumbersForBubble, lengthOfArray);
    unsigned int endBubbleSort = clock();
    free(arrayOfNumbersForBubble);
    printf("Время работы алгоритма сортировки пузырьком => %u мс", endBubbleSort - startBubbleSort);
    unsigned int startCountSort = clock();
    countSort(arrayOfNumbersForCount, lengthOfArray);
    unsigned int endCountSort = clock();
    free(arrayOfNumbersForCount);
    printf("\nВремя работы алгоритма сортировки подсчетом => %u мс", endCountSort - startCountSort);
    return 0;
}