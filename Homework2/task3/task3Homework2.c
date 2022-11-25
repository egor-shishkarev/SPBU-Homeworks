#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>

void bubbleSort(int* arrayOfNumbers, const int lengthOfArray) {
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
}

int countSort(int* arrayOfNumbers, const int lengthOfArray) {
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
}

int main() {
    setlocale(LC_ALL, ".1251");
    srand(time(NULL));
    const int lengthOfArray = 100000;
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