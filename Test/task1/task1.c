#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
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

char* binaryToDecimal(char* arrayOfSymbols) {
    if (arrayOfSymbols == NULL) {
        return NULL;
    }
    int result = 0;
    int currentSymbol = strlen(arrayOfSymbols) - 1;
    const int amountOfSymbols = currentSymbol + 1;
    while (currentSymbol >= 0) {
        if (arrayOfSymbols[currentSymbol] == '1') {
            const int currentPow = amountOfSymbols - currentSymbol - 1;
            result += pow(2, currentPow);
        }
        --currentSymbol;
    }
    char* decimalNumber = calloc(11, sizeof(char));
    int numberOfDigits = 0;
    while (result / (int) pow(10, numberOfDigits) != 0) {
        ++numberOfDigits;
    }
    for (int i = 0; i < numberOfDigits; ++i) {
        if (result == 0) {
            break;
        }
        decimalNumber[i] = (char) (result / (int) pow(10, numberOfDigits - i - 1)) + 48;
        result %= (int) pow(10, numberOfDigits - i - 1);
    }
    if (amountOfSymbols == 1 && arrayOfSymbols[0] == '0') {
        return "0";
    }
    return decimalNumber;
}

bool test(void) {
    return strcmp(binaryToDecimal("101"), "5") && strcmp(binaryToDecimal("1111"), "15") && strcmp(binaryToDecimal("0"), "0") && strcmp(binaryToDecimal("000110"), "6");
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!test()) {
        printf("Тесты не пройдены!");
        return -1;
    }
    printf("Тесты пройдены успешно!");
    printf("Введите двоичное представление числа => ");
    char* arrayOfSymbols = calloc(33, sizeof(char));
    scanf("%s", arrayOfSymbols);
    printf("%s", binaryToDecimal(arrayOfSymbols));
    return 0;
}