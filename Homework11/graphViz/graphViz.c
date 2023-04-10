#include "graphVizInteraction.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, ".1251");
    if (argc < 2) {
        printf("Недостаточно аргументов, введите заново!");
        return -1;
    }
    int errorCode = writeMatrixToDotFile(argv[1]);
    if (errorCode == -1) {
        printf("Файл с матрицей смежности был введен неправильно, проверьте %s", argv[1]);
    }
    system("script.bat");
}