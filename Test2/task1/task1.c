#include "TDArray.h"
#include <stdio.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, ".1251");
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