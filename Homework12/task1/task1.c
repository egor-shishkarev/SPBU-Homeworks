#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STRING_SIZE 101

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

typedef enum State {
    start,
    digits,
    point,
    digitsAfterPoint,
    exponent,
    exponentSign,
    digitsAfterExponent,
    end
} State;

bool isNumber(const char* string) {
    State currentState = start;
    int currentIndex = -1;
    const int lengthOfString = strlen(string);
    while (currentIndex + 1 <= lengthOfString - 1) {
        ++currentIndex;
        switch (currentState) {
        case start: {
            if (isDigit(string[currentIndex])) {
                currentState = digits;
            } else {
                currentState = end;
            }
            break;
        }
        case digits: {
            if (isDigit(string[currentIndex])) {
            } else if (string[currentIndex] == '.') {
                currentState = point;
            } else if (string[currentIndex] == 'E') {
                currentState = exponent;
            } else {
                currentState = end;
            }
            break;
        }
        case point: {
            if (isDigit(string[currentIndex])) {
                currentState = digitsAfterPoint;
            } else {
                currentState = end;
            }
            break;
        }
        case digitsAfterPoint: {
            if (isDigit(string[currentIndex])) {
            } else if (string[currentIndex] == 'E') {
                currentState = exponent;
            } else {
                currentState = end;
            }
            break;
        }
        case exponent: {
            if (string[currentIndex] == '+' || string[currentIndex] == '-') {
                currentState = exponentSign;
            } else if (isDigit(string[currentIndex])) {
                currentState = digitsAfterExponent;
            } else {
                currentState = end;
            }
            break;
        }
        case exponentSign: {
            if (isDigit(string[currentIndex])) {
                currentState = digitsAfterExponent;
            } else {
                currentState = end;
            }
            break;
        }
        case digitsAfterExponent: {
            if (isDigit(string[currentIndex])) {
            } else {
                currentState = end;
            }
            break;
        }
        case end: {
            return false;
        }
        }
    }
    return currentState == digits || currentState == digitsAfterPoint || currentState == digitsAfterExponent;
}

bool test(void) {
    char* test1 = "2512378371.4E-616";
    char* test2 = "451.133";
    char* test3 = "456";
    char* test4 = "1E1";

    char* uncorrectCase1 = ".1344";
    char* uncorrectCase2 = "27317.+124";
    char* uncorrectCase3 = "1202E";
    char* uncorrectCase4 = "4615.E123";
    char* uncorrectCase5 = "4512ololo.E-4";
    return isNumber(test1) && isNumber(test2) && isNumber(test3) && isNumber(test4) && !isNumber(uncorrectCase1) && !isNumber(uncorrectCase2) && !isNumber(uncorrectCase3) && \
        !isNumber(uncorrectCase4) && !isNumber(uncorrectCase5);
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!test()) {
        printf("Тесты не были пройдены!");
        return -1;
    }
    printf("Тесты успешно пройдены.\n");
    printf("Введите строку длиной не более 100 символов, которую хотите проверить на принадлежность к вещественным числам => ");
    char string[MAX_STRING_SIZE] = { "" };
    scanf("%s", string);
    printf("%s", isNumber(string) ? "Да" : "Нет");
    return 0;
}
