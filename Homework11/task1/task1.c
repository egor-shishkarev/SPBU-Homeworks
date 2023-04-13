#include "boyerMooreAlgorithm.h"
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE_OF_STRING 1000

int verificationIntScanf(void) {
    int readValues = 0;
    while (true) {
        int correctlyReadValues = scanf("%d", &readValues);
        while (getchar() != '\n') {
        }
        if (correctlyReadValues == 1 && readValues > 0) {
            break;
        }
        printf("Было введено нецелочисленное или неположительное значение! \n");
    }
    return readValues;
}

int* findIndex(const char* path, const char* stringToFind) {
    int* result = calloc(2, sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    int errorCode = 0;
    int* offset = createArrayOfPrefixFunction(stringToFind, &errorCode);
    if (errorCode == -1) {
        return NULL;
    }
    FILE* file = fopen(path, "r");
    int currentLine = 1;
    while (!feof(file)) {
        char buffer[MAX_SIZE_OF_STRING] = "";
        if (fgets(buffer, MAX_SIZE_OF_STRING, file) == 0) {
            break;
        }
        const int index = findString(buffer, stringToFind, offset);
        if (index < strlen(buffer)) {
            fclose(file);
            free(offset);
            result[0] = currentLine;
            result[1] = index;
            return result;
        }
        ++currentLine;
    }
    fclose(file);
    free(offset);
    return result;
}

bool test(void) {
    int* test1 = findIndex("testFile.txt", "text");
    int* test2 = findIndex("testFile.txt", "lo");
    int* test3 = findIndex("testFile.txt", "d");
    int* test4 = findIndex("testFile.txt", "gjsnk");
    int* incorrectTest = findIndex("testFile.txt", "boyer");
    bool noNullTest = test1 != NULL && test2 != NULL && test3 != NULL && test4 != NULL && incorrectTest != NULL;
    if (!noNullTest) {
        return false;
    }
    bool result = test1[0] == 3 && test1[1] == 1 && test2[0] == 2 && test2[1] == 2 && test3[0] == 5 && test3[1] == 4 && test4[0] == 6 && test4[1] == 9 && incorrectTest[0] == 0;
    free(test1);
    free(test2);
    free(test3);
    free(test4);
    free(incorrectTest);
    return result;
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!test()) {
        printf("Тесты не были пройдены!");
        return -1;
    }
    printf("Тесты пройдены успешно.\n");
    printf("Введите длину строки, которую хотите найти => ");
    const int lengthOfString = verificationIntScanf();
    printf("Введите строку, которую хотите найти => ");
    char* stringToFind = calloc(lengthOfString + 1, sizeof(char));
    scanf("%s", stringToFind);
    int* result = findIndex("text.txt", stringToFind);
    if (result[0] == 0) {
        printf("Данной строки нет в тексте!");
    } else {
        printf("Первый раз строка встретилась на %d строке, %d индексе", result[0], result[1]);
    }
    free(stringToFind);
    free(result);
    return 0;
}
