#include "graphVizInteraction.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, ".1251");
    if (argc < 2) {
        printf("Недостаточно аргументов, введите заново!");
        return -1;
    }
    if (argc == 2 && !strcmp(argv[1], "-test")) {
        if (!test()) {
            printf("Тесты не были пройдены!");
            return -1;
        }
        printf("Тесты пройдены успешно.");
        return 0;
    }
    int errorCode = writeMatrixToDotFile(argv[1]);
    if (errorCode == -1) {
        printf("Файл с матрицей смежности был введен неправильно, проверьте %s", argv[1]);
    }
    system("script.bat");
}