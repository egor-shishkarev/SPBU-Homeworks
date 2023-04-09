#include "AVLTree.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX_STRING_SIZE 50

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

bool test(void) {
    int errorCode = 0;
    AVLTree* tree = createTree(&errorCode);
    addElement(tree, "8", "A", &errorCode);
    if (errorCode == -1) {
        deleteTree(&tree);
        return false;
    }
    addElement(tree, "5", "B", &errorCode);
    if (errorCode == -1) {
        deleteTree(&tree);
        return false;
    }
    addElement(tree, "9", "C", &errorCode);
    if (errorCode == -1) {
        deleteTree(&tree);
        return false;
    }
    addElement(tree, "1", "D", &errorCode);
    if (errorCode == -1) {
        deleteTree(&tree);
        return false;
    }
    bool firstTest = strcmp(searchValueFromKey(tree, "5"), "B") == 0;
    deleteElement(tree, "8", &errorCode);
    if (errorCode == -1) {
        deleteTree(&tree);
        return false;
    }
    bool secondTest = !isKeyInTree(tree, "8");
    deleteTree(&tree);
    return firstTest && secondTest && tree == NULL;
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!test()) {
        printf("Тесты не пройдены!");
        return -1;
    }
    printf("Тесты были пройдены!\n");
    printf("Данная программа - словарь, который интерактивно работает с ключами и значениями.\n");
    printf("Введите следующие числа, чтобы выполнить предложенные команды:\n0 - выйти\n1 - добавить значение по ключу в словарь\n2 - \
получить значение по ключу\n3 - проверить наличие ключа в словаре\n4 - удалить ключ и его значение\n");
    int errorCode = 0;
    AVLTree* tree = createTree();
    while (true) {
        printf("Введите команду => ");
        int mode = verificationIntScanf();
        switch (mode) {
        case 0: {
            deleteTree(&tree); 
            printf("Работа окончена!");
            return 0;
        }
        case 1: {
            printf("Введите ключ => "); 
            char key[MAX_KEY_SIZE] = { 0 };
            gets(key);
            printf("Введите значение длинной не более %d символов => ", MAX_STRING_SIZE);
            char value[MAX_STRING_SIZE] = { 0 };
            gets(value);
            addElement(tree, key, value, &errorCode);
            if (errorCode == -1) {
                printf("Произошла ошибка в работе!");
                return -1;
            }
            break;
        }
        case 2: {
            printf("Введите ключ => "); 
            char key[MAX_KEY_SIZE] = { 0 };
            gets(key);
            char* value = searchValueFromKey(tree, key);
            if (value == NULL) {
                printf("Данного ключа нет в дереве!\n");
            } else {
                printf("Значение по данному ключу - %s\n", value);
            }
            break;
        }
        case 3: {
            printf("Введите ключ => "); 
            char key[MAX_KEY_SIZE] = { 0 };
            gets(key);
            printf(isKeyInTree(tree, key) ? "Данный ключ есть в словаре.\n" : "Данного ключа нет в словаре!\n");
            break;
        }
        case 4: {
            printf("Введите ключ, значение для которого хотите удалить => "); 
            char key[MAX_KEY_SIZE] = { 0 };
            gets(key);
            deleteElement(tree, key, &errorCode);
            if (errorCode == -1) {
                printf("Произошла ошибка в работе!");
                return -1;
            }
            break;
        }
        default: {
            printf("Данной команды нет в списке, повторите ввод!\n");
            continue;
        }
        }
    }
    return 0;
}