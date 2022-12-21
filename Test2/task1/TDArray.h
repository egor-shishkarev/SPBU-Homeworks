#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TDArray TDArray;
int** createArray(const int lines, const int columns);
void addElements(int** array, const int lines, const int columns);
int verificationIntScanf(void);
void printArray(int** array, const int lines, const int columns);
int** searchSaddlePoint(int** array, const int lines, const int columns);