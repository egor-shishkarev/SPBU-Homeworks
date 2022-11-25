#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH_OF_ARRAY 20

int quickSort(int* arrayOfNumbers, const int arrayLength) {
    int left = 0;
    int right = arrayLength - 1;
    int middle = arrayOfNumbers[0];
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
}

int main() {
    int arrayOfNumbers[LENGTH_OF_ARRAY] = { 0 };
    srand(clock(NULL));
    for (int i = LENGTH_OF_ARRAY / 2; i < LENGTH_OF_ARRAY; ++i) {
        arrayOfNumbers[i] = rand() % 100;
    }
    for (int i = 0; i <= LENGTH_OF_ARRAY / 2; ++i) {
        arrayOfNumbers[i] = rand() % 100;
    }
    for (int i = 0; i < LENGTH_OF_ARRAY; ++i) {
        printf("%d ", arrayOfNumbers[i]);
    }
    quickSort(arrayOfNumbers, LENGTH_OF_ARRAY);
    printf("\n");
    for (int i = 0; i < LENGTH_OF_ARRAY; ++i) {
        printf("%d ", arrayOfNumbers[i]);
    }
    return 0;
}