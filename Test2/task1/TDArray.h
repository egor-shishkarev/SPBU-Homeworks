#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TDArray TDArray;
TDArray* createArray(const int lines, const int columns);
void addElements(TDArray* arrayTD);
int verificationIntScanf(void);
void printArray(TDArray* arrayTD);
TDArray* searchSaddlePoint(TDArray* arrayTD);
void freeTDArray(TDArray** arrayTD);
int getElement(TDArray* arrayTD, const int i, const int j);
void insertElement(TDArray* arrayTD, const int number, const int i, const int j);