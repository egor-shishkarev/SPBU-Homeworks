#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

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

bool test(void) {
    int arrayOfNumbers[8] = {5, 2, 7, 4, 9, 10, 3, 5};
    const int firstElement = arrayOfNumbers[0];
    quickSort(arrayOfNumbers, 8);
    bool flagIsLess = true;
    for (int i = 0; i < 8; ++i) {
        if (arrayOfNumbers[i] < firstElement && !flagIsLess) {
            return false;
        }
        if (flagIsLess && arrayOfNumbers[i] > firstElement) {
            flagIsLess = false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "-test") == 0) {
        if (!test()) {
            return -1;
        }
        return 0;
    }
    setlocale(LC_ALL, ".1251");
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