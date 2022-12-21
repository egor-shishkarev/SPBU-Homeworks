#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// Структура двумерного массива
typedef struct TDArray TDArray;
// Создаёт двумерный массив
TDArray* createArray(const int lines, const int columns);
// Добавление элементов в массив из консоли
void addElements(TDArray* arrayTD);
// Вывод массива
void printArray(TDArray* arrayTD);
// Функция поиска седловых точек, вовзращает массив, где 1 означает, что это точка седловая.
TDArray* searchSaddlePoint(TDArray* arrayTD);
// Удаление массива
void freeTDArray(TDArray** arrayTD);
// Вовзращает один элемент
int getElement(TDArray* arrayTD, const int i, const int j);
// Вставаить один элемент
void insertElement(TDArray* arrayTD, const int number, const int i, const int j);
// Ввод целового числа
int verificationIntScanf(void);