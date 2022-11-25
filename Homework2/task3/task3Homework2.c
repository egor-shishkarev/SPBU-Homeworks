#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

#define LENGTH_ARRAY 100000
#define MAX_INT 32768

unsigned int bubbleSort(int arrayOfNumbers[], const int lengthOfArray) {
    unsigned int startBubbleSort = clock();
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
    unsigned int endBubbleSort = clock();
    return endBubbleSort - startBubbleSort;
}

unsigned int countSort(int arrayOfNumbers[], const int lengthOfArray) {
    unsigned int startCountSort = clock();
    int arrayForCount[MAX_INT] = { 0 };
    int pointerForCountMin = LENGTH_ARRAY;
    int pointerForCountMax = 0;
    for (int i = 0; i < lengthOfArray; ++i) {
        ++arrayForCount[arrayOfNumbers[i]];
        pointerForCountMin = min(pointerForCountMin, arrayOfNumbers[i]);
        pointerForCountMax = max(pointerForCountMax, arrayOfNumbers[i]);
    }
    int currentElement = 0;
    for (int i = pointerForCountMin; i <= pointerForCountMax; ++i) {
        while (arrayForCount[i]) {
            arrayOfNumbers[currentElement] = i;
            ++currentElement;
            --arrayForCount[i];
        }
    }
    unsigned int endCountSort = clock();
    return endCountSort - startCountSort;
}

void copyArray(int firstArray[], const int lengthOfArray, int secondArray[]) {
    for (int i = 0; i < lengthOfArray; ++i) {
        secondArray[i] = firstArray[i];
    }
}

int main() {
    setlocale(LC_ALL, ".1251");
    srand(clock());
    int arrayOfNumbersForBubble[LENGTH_ARRAY] = { 0 };
    for (int i = 0; i < LENGTH_ARRAY; ++i) {
        arrayOfNumbersForBubble[i] = rand();
    }
    int arrayOfNumbersForCount[LENGTH_ARRAY] = { 0 };
    copyArray(arrayOfNumbersForBubble, LENGTH_ARRAY, arrayOfNumbersForCount);
    unsigned int timeForBubble = bubbleSort(arrayOfNumbersForBubble, LENGTH_ARRAY);
    printf("Время работы алгоритма сортировки пузырьком => %u мс", timeForBubble);
    unsigned int timeForCount = countSort(arrayOfNumbersForCount, LENGTH_ARRAY);
    printf("\nВремя работы алгоритма сортировки подсчетом => %u мс", timeForCount);
    return 0;
}