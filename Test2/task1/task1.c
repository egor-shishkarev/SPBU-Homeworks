#include "TDArray.h"
#include <stdio.h>
#include <locale.h>

bool test(void) {
    TDArray* arrayTD = createArray(4, 4);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            insertElement(arrayTD, 4 * i + j, i, j);
        }
    }
    TDArray* result = searchSaddlePoint(arrayTD);
    bool isTrue = getElement(result, 3, 0) == 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (getElement(arrayTD, i, j) == 0 && i != 3 && j != 0) {
                return false;
            }
        }
    }
    freeTDArray(&arrayTD);
    freeTDArray(&result);
    return isTrue;
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!test()) {
        printf("Тесты не пройдены!");
        return -1;
    }
    printf("Тесты пройдены успешно.\n");
    printf("Введите количество строк и столбцов через Enter => ");
    const int lines = verificationIntScanf();
    const int columns = verificationIntScanf();
    TDArray* arrayTD = createArray(lines, columns);
    printf("Вводите элеметы массива через Enter по строкам: ");
    addElements(arrayTD, lines, columns);
    TDArray* result = searchSaddlePoint(arrayTD, lines, columns);
    printArray(arrayTD, lines, columns);
    freeTDArray(&arrayTD);
    printf("Седловые точки находятся на индексах: \n");
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (getElement(result, i, j) == 1) {
                printf("%d - ая строка %d - столбец\n", i + 1, j + 1);
            }
        }
    }
    freeTDArray(&result);
    return 0;
}
