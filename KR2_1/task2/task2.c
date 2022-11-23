#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>

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
	int errorCode = 0;
	int arrayOfNumbers[10] = { 1, 6, 3, 8, 2, 5, 4, 7, 9, 0 };
	for (int i = 0; i < 10; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	binaryTreeSort(arrayOfNumbers, 10);
	printf("\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	return 0;
}


/*Реализовать сортировку на двоичном дереве поиска. Функция сортировки должна 
принимать массив, строить по нему двоичное дерево поиска, затем перезаписывать 
переданный ей массив результатом обхода дерева в прямом порядке, получая отсортированный массив.*/