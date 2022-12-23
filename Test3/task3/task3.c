#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#define MAX_LENGTH_OF_STRING 100

typedef enum State {
    start,
    plus,
    digitsAfterPlus,
    openBracket,
    digitsIntoBrackets,
    closedBracket,
    digitsAfterBracket,
    firstDash,
    digitsAfterFirstDash,
    secondDash,
    digitsAfterSecondDash
};

bool isDigit(const char symbol) {
    return symbol >= '0' && symbol <= '9';
}

bool isPhone(const char* string) {
    int currentState = start;
    int index = -1;
    int lengthOfString = strlen(string) - 1;
    while (index < lengthOfString) {
        ++index;
        switch (currentState) {
        case start: {
            if (string[index] == ' ') {
                break;
            } else if (string[index] == '+') {
                currentState = plus;
                break;
            } else {
                return false;
            }
        }
        case plus: {
            if (isDigit(string[index])) {
                currentState = digitsAfterPlus;
                break;
            } else {
                return false;
            }
        }
        case digitsAfterPlus: {
            if (string[index] == '(') {
                currentState = openBracket;
                break;
            } else if (isDigit(string[index])) {
                break;
            } else {
                return false;
            }
        }
        case openBracket: {
            if (isDigit(string[index])) {
                currentState = digitsIntoBrackets;
                break;
            } else {
                return false;
            }
        }
        case digitsIntoBrackets: {
            if (isDigit(string[index])) {
                break;
            } else if (string[index] == ')') {
                currentState = closedBracket;
                break;
            } else {
                return false;
            }
        }
        case closedBracket: {
            if (isDigit(string[index])) {
                break;
            } else if (string[index] == '-') {
                currentState = firstDash;
                break;
            } else {
                return false;
            }
        }
        case firstDash: {
            if (isDigit(string[index])) {
                currentState = digitsAfterFirstDash;
                break;
            } else {
                return false;
            }
        }
        case digitsAfterFirstDash: {
            if (isDigit(string[index])) {
                break;
            } else if (string[index] == '-') {
                currentState = secondDash;
                break;
            } else {
                return false;
            }
        }
        case secondDash: {
            if (isDigit(string[index])) {
                currentState = digitsAfterSecondDash;
                break;
            } else {
                return false;
            }
        }
        case digitsAfterSecondDash: {
            if (isDigit(string[index])) {
                break;
            } else {
                return false;
            }
        }
        }
    }
    return currentState == digitsAfterSecondDash;
}

bool test(void) {
    char* uncorrectTest1 = "";
    char* uncorrectTest2 = "7(911)732-65-18";
    char* uncorrectTest3 = "+(911)345-23-78";
    char* uncorrectTest4 = "+7911)124-65-13";
    char* uncorrectTest5 = "+7(911542-12-65";
    char* uncorrectTest6 = "+123(911)7433252-12";
    char* uncorrectTest7 = "+789(786)532-534346";

    char* correctTest1 = "+7(923)456-23-12";
    char* correctTest2 = "+276216733213722780(441620231345230)165030023730232780228728-7520727238702380237-5875320430473";
    char* correctTest3 = "+3(2)1-0-0";
    bool allUncorrectTests = isPhone(uncorrectTest1) || isPhone(uncorrectTest2) || isPhone(uncorrectTest3) || isPhone(uncorrectTest4) || isPhone(uncorrectTest5) || \
        isPhone(uncorrectTest6) || isPhone(uncorrectTest7);
    bool allCorrectTests = isPhone(correctTest1) && isPhone(correctTest2) && isPhone(correctTest3);
    return !allUncorrectTests && allCorrectTests;
}

int main(void) {
    // [+]\([digit]+\)(digit)+[-](digit)+[-](digit)+  ||  digit = 0|1|...|9, \( и \) - символы ( и ), соответственно
    setlocale(LC_ALL, ".1251");
    if (!(test())) {
        printf("Тесты не были пройдены!");
        return -1;
    }
    printf("Тесты пройдены успешно.");
    printf("Введите строку максимальной длины %d\n", MAX_LENGTH_OF_STRING);
    printf("Введите строку => ");
    char string[MAX_LENGTH_OF_STRING] = { "" };
    scanf("%s", string);
    printf("%s", isPhone(string) ? "Да, это номер телефона" : "Нет, это не номер телефона");
    return 0;
}
