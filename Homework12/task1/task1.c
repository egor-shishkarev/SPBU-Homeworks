#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

int verificationIntScanf(void) {
    int readValues = 0;
    while (true) {
        int correctlyReadValues = scanf("%d", &readValues);
        while (getchar() != '\n') {
        }
        if (correctlyReadValues == 1) {
            break;
        }
        printf("Было введено нецелочисленное значение! \n");
    }
    return readValues;
}

bool isDigit(const char symbol) {
    return symbol >= '0' && symbol <= '9';
}

bool isNumber(const char* string) {
    int currentState = 0;
    int currentIndex = -1;
    const int lengthOfString = strlen(string);
    while (currentIndex + 1 <= lengthOfString - 1) {
        ++currentIndex;
        switch (currentState) {
        case 0: {
            if (isDigit(string[currentIndex])) {
                currentState = 1;
            }
            else {
                currentState = 7;
            }
            break;
        }
        case 1: {
            if (string[currentIndex] == '.') {
                currentState = 2;
            }
            else if (!isDigit(string[currentIndex])) {
                currentState = 7;
            }
            break;
        }
        case 2: {
            if (isDigit(string[currentIndex])) {
                currentState = 3;
            }
            else {
                currentState = 7;
            }
            break;
        }
        case 3: {
            if (string[currentIndex] == 'E') {
                currentState = 4;
            }
            else if (!isDigit(string[currentIndex])) {
                currentState = 7;
            }
            break;
        }
        case 4: {
            if (string[currentIndex] == '+' || string[currentIndex] == '-') {
                currentState = 5;
            }
            else {
                currentState = 7;
            }
            break;
        }
        case 5: {
            if (isDigit(string[currentIndex])) {
                currentState = 6;
            }
            else {
                currentState = 7;
            }
            break;
        }
        case 6: {
            if (!isDigit(string[currentIndex])) {
                currentState = 7;
            }
            break;
        }
        case 7: {
            return false;
            break;
        }
        }
    }
    return currentState == 1 || currentState == 3 || currentState == 6;
}

bool test(void) {
    char* test1 = "2512378371.4E-616";
    char* test2 = "451.133";
    char* test3 = "456";

    char* uncorrectCase1 = ".1344";
    char* uncorrectCase2 = "27317.+124";
    char* uncorrectCase3 = "1202E";
    char* uncorrectCase4 = "4615.E123";
    char* uncorrectCase5 = "4512ololo.E-4";
    return isNumber(test1) && isNumber(test2) && isNumber(test3) && !isNumber(uncorrectCase1) && !isNumber(uncorrectCase2) && !isNumber(uncorrectCase3) && \
        !isNumber(uncorrectCase4) && !isNumber(uncorrectCase5);
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!test()) {
        printf("Тесты не были пройдены!");
        return -1;
    }
    printf("Тесты успешно пройдены.\n");
    printf("Введите максимальное число символов в вашей строке => ");
    const int length = verificationIntScanf();
    printf("Введите строку, которую хотите проверить на принадлежность к вещественным числам => ");
    char* string = calloc(length, sizeof(char));
    scanf("%s", string);
    printf("%s", isNumber(string) ? "Да" : "Нет");
    free(string);
    return 0;
} // 2512378371.E-616
/* */
