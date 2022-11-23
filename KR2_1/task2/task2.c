#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

bool test(void) {
	int arrayOfNumbers[10] = { 5, 3, 2, 4, 7, 8, 0, 9, 1, 6 };
	binaryTreeSort(arrayOfNumbers, 10);
	for (int i = 0; i < 10; ++i) {
		if (arrayOfNumbers[i] != i) {
			return false;
		}
	}
	return true;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!test()) {
		printf("Тесты не пройдены!");
		return -1;
	}
	printf("Тесты успешно пройдены, функция сортировки деревом работает!");
	return 0;
}


/*Реализовать сортировку на двоичном дереве поиска. Функция сортировки должна 
принимать массив, строить по нему двоичное дерево поиска, затем перезаписывать 
переданный ей массив результатом обхода дерева в прямом порядке, получая отсортированный массив.*/