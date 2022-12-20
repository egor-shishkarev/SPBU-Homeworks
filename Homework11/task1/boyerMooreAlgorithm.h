#pragma once

#include <stdio.h>
#include <string.h>
#include <malloc.h>
// Функция вохвращает указатель на массив значений, 
// по которым нужно сдвигаться при сравнении строк.
int* createArrayOfPrefixFunction(char* string, int* errorCode);
// Вовзращает индекс первого совпадения строки в тексте.
int findString(char* text, char* string, int* offset);