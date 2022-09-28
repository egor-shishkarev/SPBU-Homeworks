#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>


#define lengthArray 100000
#define maxInt 32768

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
        if (!(flagOfChanged)) {
            break;
        }
    }
    unsigned int endBubbleSort = clock();
    return endBubbleSort - startBubbleSort;
}

unsigned int countSort(int arrayOfNumbers[], const int lengthOfArray) {
    unsigned int startCountSort = clock();
    int arrayForCount[maxInt] = { 0 };
    int pointerForCountMin = lengthArray;
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
    int arrayOfNumbersForBubble[lengthArray] = { 0 };
    for (int i = 0; i < lengthArray; ++i) {
        arrayOfNumbersForBubble[i] = rand();
    }
    int arrayOfNumbersForCount[lengthArray] = { 0 };
    copyArray(arrayOfNumbersForBubble, lengthArray, arrayOfNumbersForCount);
    unsigned int timeForBubble = bubbleSort(arrayOfNumbersForBubble, lengthArray);
    printf("Время работы алгоритма сортировки пузырьком => %u мс", timeForBubble);
    unsigned int timeForCount = countSort(arrayOfNumbersForCount, lengthArray);
    printf("\nВремя работы алгоритма сортировки подсчетом => %u мс", timeForCount);
    return 0;
}