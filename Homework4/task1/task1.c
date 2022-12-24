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
    for (int i = 0; i < size; ++i) {
        printf("%d", binaryNumber[i]);
        if ((i + 1) % 8 == 0 ) {
            printf(" ");
        }
    }
    printf("\n");
}

void binaryRepresentation(int number, short* repressentation, const unsigned int size) {
    for (int i = size - 1; i >= 0; --i) {
        repressentation[i] = (short)(number & 1);
        number = number >> 1;
    }
}

void binarySum(const short* firstBinary, const short* secondBinary, short* sum, const unsigned int size) {
    bool overflow = false;
    for (int i = size - 1; i >= 0; --i) {
        sum[i] = (short) (firstBinary[i] ^ secondBinary[i] ^ overflow);
        overflow = (firstBinary[i] + secondBinary[i] + overflow) > 1 ? true : false;
    }
}

int decimalRepresentation(short* binaryNumber, const unsigned int size) {
    int sum = 0;
    int mask = 1;
    for (int i = size - 1; i > 0; --i) {
        sum += binaryNumber[i] * mask;
        mask <<= 1;
    }
    sum -= binaryNumber[0] * mask;
    return sum;
}

bool correspondenceTest(const short* binaryNumber, const short* right, const unsigned int size) {
    for (int i = 0; i < size; ++i) {
        if (binaryNumber[i] != right[i]) {
            return false;
        }
    }
    return true;
}

bool test(void) {
    int first = 117;
    int second = -7;
    int third = -117;

    short binaryFirst[10] = { 0 };
    short binarySecond[10] = { 0 };
    short binaryThird[10] = { 0 };
    binaryRepresentation(first, binaryFirst, 10);
    binaryRepresentation(second, binarySecond, 10);
    binaryRepresentation(third, binaryThird, 10);

    short rightFirst[10] = {0, 0, 0, 1, 1, 1, 0, 1, 0, 1};
    short rightSecond[10] = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 };
    short rightThird[10] = { 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 };

    short firstAddition[10] = { 0 };
    short secondAddition[10] = { 0 };
    short thirdAddition[10] = { 0 };

    short rightFirstAddition[10] = {0, 0, 0, 1, 1, 0, 1, 1, 1, 0 };
    short rightSecondAddition[10] = { 1, 1, 1, 0, 0, 0, 0, 1, 0, 0 };
    short rightThirdAddition[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    binarySum(binaryFirst, binarySecond, firstAddition, 10);
    binarySum(binarySecond, binaryThird, secondAddition, 10);
    binarySum(binaryFirst, binaryThird, thirdAddition, 10);

    return correspondenceTest(binaryFirst, rightFirst, 10) && correspondenceTest(binarySecond, rightSecond, 10) && correspondenceTest(binaryThird, rightThird, 10) && \
        correspondenceTest(firstAddition, rightFirstAddition, 10) && correspondenceTest(secondAddition, rightSecondAddition, 10) && correspondenceTest(thirdAddition, rightThirdAddition, 10) && \
        decimalRepresentation(firstAddition, 10) == 110 && decimalRepresentation(secondAddition, 10) == -124 && decimalRepresentation(thirdAddition, 10) == 0;
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!(test())) {
        printf("Тесты не пройдены!");
        return -1;
    }
    printf("Тесты успешно пройдены!\n");
    printf("Введите два целых числа => ");
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

