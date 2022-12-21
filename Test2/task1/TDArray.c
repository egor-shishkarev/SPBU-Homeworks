#include "TDArray.h"

typedef struct TDArray {
    int* array;
    int lines;
    int columns;
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

TDArray* createArray(const int lines, const int columns) {
    TDArray* arrayTD = malloc(sizeof(TDArray));
    arrayTD->columns = columns;
    arrayTD->lines = lines;
    arrayTD->array = calloc(lines * columns, sizeof(int));
    return arrayTD;
}

void addElements(TDArray* arrayTD) {
    const int lines = arrayTD->lines;
    const int columns = arrayTD->columns;
    for (int i = 0; i < lines; ++i) {
        printf("%d - ая строка: ", i);
        for (int j = 0; j < columns; ++j) {
            arrayTD->array[arrayTD->lines * i + j] = verificationIntScanf();
        }
    }
}

void printArray(TDArray* arrayTD) {
    const int lines = arrayTD->lines;
    const int columns = arrayTD->columns;
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf("%d ", arrayTD->array[arrayTD->lines * i + j]);
        }
        printf("\n");
    }
}

TDArray* searchSaddlePoint(TDArray* arrayTD) {
    const int lines = arrayTD->lines;
    const int columns = arrayTD->columns;
    TDArray* result = createArray(lines, columns);
    for (int i = 0; i < lines; ++i) {
        int minElement = INT_MAX;
        for (int j = 0; j < columns; ++j) {
            if (arrayTD->array[arrayTD->lines * i + j] < minElement) {
                minElement = arrayTD->array[arrayTD->lines * i + j];
            }
        }
        for (int j = 0; j < columns; ++j) {
            if (arrayTD->array[arrayTD->lines * i + j] == minElement) {
                result->array[result->lines * i + j] = 1;
                for (int k = 0; k < lines; ++k) {
                    if (arrayTD->array[arrayTD->lines * k + j] > arrayTD->array[arrayTD->lines * i + j]) {
                        result->array[result->lines * i + j] *= 0;
                        break;
                    }
                }
            }
        }
    }
    return result;
}

void freeTDArray(TDArray** arrayTD) {
    free((*arrayTD)->array);
    free((*arrayTD));
}

int getElement(TDArray* arrayTD, const int i, const int j) {
    return arrayTD->array[arrayTD->lines * i + j];
}

void insertElement(TDArray* arrayTD, const int number, const int i, const int j) {
    arrayTD->array[arrayTD->lines * i + j] = number;
}