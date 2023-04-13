#pragma once

// Функция возвращает указатель на массив значений, 
// по которым нужно сдвигаться при сравнении строк.
int* createArrayOfPrefixFunction(const char* string, int* errorCode);

// Вовзращает индекс первого совпадения строки в тексте.
int findString(const char* text, const char* string, int* offset);