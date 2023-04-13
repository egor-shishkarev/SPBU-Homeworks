#pragma once
#include <stdbool.h>

// Позволяет преобразовывать матрицу смежности, записанную в текстовом файле в dot файл.
int writeMatrixToDotFile(char* filePath);

// Запускает тесты для проверки ввода в dot файл.
bool test(void);