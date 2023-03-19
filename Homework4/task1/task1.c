#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>

#define BINARY_SIZE sizeof(int) * 8

int verificationIntScanf(void) {
    int readValues = 0;
    while (true) {
        int correctlyReadValues = scanf("%d", &readValues);
        while (getchar() != '\n') {
        }
        if (correctlyReadValues == 1) {
            break;
        }
        printf("Ошибка ввода. Введите целочисленное значение!\n");
    }
    return readValues;
}

void printBinary(const short* binaryNumber, const unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        printf("%d", binaryNumber[i]);
        if ((i + 1) % 8 == 0 ) {
            printf(" ");
        }
    }
    printf("\n");
}

void binaryRepresentation(int number, short* representation, const unsigned int size) {
    for (int i = size - 1; i >= 0; --i) {
        representation[i] = (short)(number & 1);
        number = number >> 1;
    }
}

void binarySum(const short* firstBinary, const short* secondBinary, short* sum, const unsigned int size) {
    bool overflow = false;
    for (int i = size - 1; i >= 0; --i) {
        sum[i] = (short) (firstBinary[i] ^ secondBinary[i] ^ overflow);
        overflow = (firstBinary[i] + secondBinary[i] + overflow) > 1;
    }
}

int decimalRepresentation(short* binaryNumber, const unsigned int size) {
    int sum = 0;
    int mask = 1;
    for (int i = size - 1; i >= 0; --i) {
        sum += binaryNumber[i] * mask;
        mask <<= 1;
    }
    return sum;
}

bool correspondenceTest(const short* binaryNumber, const short* rightNumber, const unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        if (binaryNumber[i] != rightNumber[i]) {
            return false;
        }
    }
    return true;
}

void increaseSize(short* shortNumber, short longNumber[BINARY_SIZE], unsigned int sizeOfShort) {
    if (shortNumber[0] == 1) {
        for (int i = 0; i < BINARY_SIZE - sizeOfShort; ++i) {
            longNumber[i] = 1;
        }
    }
    for (int i = sizeOfShort - 1; i >= 0; --i) {
        longNumber[BINARY_SIZE - sizeOfShort + i] = shortNumber[i];
    }
}

bool test(void) {
    int first = 117;
    int second = -7;
    int third = -117;

    short binaryFirst[BINARY_SIZE] = { 0 };
    short binarySecond[BINARY_SIZE] = { 0 };
    short binaryThird[BINARY_SIZE] = { 0 };
    binaryRepresentation(first, binaryFirst, BINARY_SIZE);
    binaryRepresentation(second, binarySecond, BINARY_SIZE);
    binaryRepresentation(third, binaryThird, BINARY_SIZE);

    short rightFirst[BINARY_SIZE] = { 0 }; 
    short rightFirstShort[] = { 0, 0, 0, 1, 1, 1, 0, 1, 0, 1 };
    increaseSize(rightFirstShort, rightFirst, 10);

    short rightSecond[BINARY_SIZE] = { 0 };
    short rightSecondShort[] = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 };
    increaseSize(rightSecondShort, rightSecond, 10);

    short rightThird[BINARY_SIZE] = { 0 };
    short rightThirdShort[] = { 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 };
    increaseSize(rightThirdShort, rightThird, 10);

    short firstAddition[BINARY_SIZE] = { 0 };
    short secondAddition[BINARY_SIZE] = { 0 };
    short thirdAddition[BINARY_SIZE] = { 0 };

    short rightFirstAddition[BINARY_SIZE] = { 0 };
    short rightFirstAdditionShort[BINARY_SIZE] = { 0, 0, 0, 1, 1, 0, 1, 1, 1, 0 };
    increaseSize(rightFirstAdditionShort, rightFirstAddition, 10);

    short rightSecondAddition[BINARY_SIZE] = { 1 };
    short rightSecondAdditionShort[BINARY_SIZE] = { 1, 1, 1, 0, 0, 0, 0, 1, 0, 0 };
    increaseSize(rightSecondAdditionShort, rightSecondAddition, 10);

    short rightThirdAddition[BINARY_SIZE] = { 0 };

    binarySum(binaryFirst, binarySecond, firstAddition, BINARY_SIZE);
    binarySum(binarySecond, binaryThird, secondAddition, BINARY_SIZE);
    binarySum(binaryFirst, binaryThird, thirdAddition, BINARY_SIZE);

    return correspondenceTest(binaryFirst, rightFirst, BINARY_SIZE) && correspondenceTest(binarySecond, rightSecond, BINARY_SIZE) && correspondenceTest(binaryThird, rightThird, BINARY_SIZE) &&
        correspondenceTest(firstAddition, rightFirstAddition, BINARY_SIZE) && correspondenceTest(secondAddition, rightSecondAddition, BINARY_SIZE) && correspondenceTest(thirdAddition, rightThirdAddition, BINARY_SIZE) &&
        decimalRepresentation(firstAddition, BINARY_SIZE) == 110 && decimalRepresentation(secondAddition, BINARY_SIZE) == -124 && decimalRepresentation(thirdAddition, BINARY_SIZE) == 0;
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!test()) {
        printf("Тесты не пройдены!");
        return -1;
    }
    printf("Тесты успешно пройдены!\n");
    printf("Введите два целых числа через Enter => ");
    const int firstNumber = verificationIntScanf();
    short firstBinary[BINARY_SIZE] = { 0 };
    binaryRepresentation(firstNumber, firstBinary, BINARY_SIZE);
    const int secondNumber = verificationIntScanf();
    short secondBinary[BINARY_SIZE] = { 0 };
    binaryRepresentation(secondNumber, secondBinary, BINARY_SIZE);
    printf("Первое число: \n");
    printBinary(firstBinary, BINARY_SIZE);
    printf("Второе число: \n");
    printBinary(secondBinary, BINARY_SIZE);
    short sum[BINARY_SIZE] = { 0 };
    printf("Сумма двух чисел: \n");
    binarySum(firstBinary, secondBinary, sum, BINARY_SIZE);
    printBinary(sum, BINARY_SIZE);
    printf("Сумма в десятичном: %d", decimalRepresentation(sum, BINARY_SIZE));
    return 0;
}
