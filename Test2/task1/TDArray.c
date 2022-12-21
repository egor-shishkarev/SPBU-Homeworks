#include "TDArray.h"

typedef struct TDArray {
    int** array;
} TDArray;

int verificationIntScanf(void) {
    int readValues = 0;
    while (true) {
        int correctlyReadValues = scanf("%d", &readValues);
        while (getchar() != '\n') {
        }
        if (correctlyReadValues == 1) {
            break;
        }
        printf("Было введено нецелочисленное значение! \n");
    }
    return readValues;
}

int** createArray(const int lines, const int columns) {
    int** array = malloc(lines, sizeof(int*));
    for (int i = 0; i < lines; ++i) {
        array[i] = calloc(columns, sizeof(int));
    }
    return array;
}

void addElements(int** array, const int lines, const int columns) {
    for (int i = 0; i < lines; ++i) {
        printf("%d - ая строка: ", i);
        for (int j = 0; j < columns; ++j) {
            array[i][j] = verificationIntScanf();
        }
    }
}

void printArray(int** array, const int lines, const int columns) {
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

int** searchSaddlePoint(int** array, const int lines, const int columns) {
    int** result = createArray(lines, columns);
    for (int i = 0; i < lines; ++i) {
        int minElement = INT_MAX;
        for (int j = 0; j < columns; ++j) {
            if (array[i][j] < minElement) {
                minElement = array[i][j];
            }
        }
        for (int j = 0; j < columns; ++j) {
            if (array[i][j] == minElement) {
                result[i][j] = 1;
                for (int k = 0; k < lines; ++k) {
                    if (array[k][j] > array[i][j]) {
                        result[i][j] *= 0;
                        break;
                    }
                }
            }
        }
    }
    return result;
}