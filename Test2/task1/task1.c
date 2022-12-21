#include "TDArray.h"
#include <stdio.h>
#include <locale.h>

bool test(void) {
    int** TDArray = calloc(4, sizeof(int*));
    for (int i = 0; i < 4; ++i) {
        TDArray[i] = calloc(4, sizeof(int));
        for (int j = 0; j < 4; ++j) {
            TDArray[i][j] = 4 * i + j;
        }
    }
    int** result = searchSaddlePoint(TDArray, 4, 4);
    bool isTrue = result[3][0] == 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (TDArray[i][j] == 0 && i != 3 && j != 0) {
                return false;
            }
        }
    }
    return isTrue;
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!test()) {
        printf("Тесты не пройдены!");
        return -1;
    }
    printf("Тесты пройдены успешно.");
    printf("Введите количество строк и столбцов через Enter => ");
    const int lines = verificationIntScanf();
    const int columns = verificationIntScanf();
    int** array = createArray(lines, columns);
    printf("Вводите элеметы массива через Enter по строкам: ");
    addElements(array, lines, columns);
    int** result = searchSaddlePoint(array, lines, columns);
    printArray(array, lines, columns);
    printf("----------------\n");
    printArray(result, lines, columns);
    free(*array);
    free(*result);
    return 0;
}

/*Написать программу поиска седловых точек двумерного массива. 
Седловая точка — это элемент, наименьший в своей строке и наибольший в своем столбце. 
Если седловых точек несколько, вывести их все. Реализовать АТД двумерного массива 
(в отдельном модуле), содержащего помимо прочего функции для считывания из консоли, 
печать и поиск седловых точек.*/