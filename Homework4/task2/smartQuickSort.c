#include "smartQuickSort.h"
#include <stdlib.h>

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
