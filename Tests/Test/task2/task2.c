﻿#include "list.h"
#include <stdio.h>

int main(void) {
	List* list = createList();
	insert(list, "a");
	insert(list, "b");
	insert(list, "c");
	printList(list);
	printf("\n");
	addAStrings(list);
	printList(list);
	deleteList(&list);
	return 0;
}

/*Без использования дополнительных структур данных реализовать односвязный список строк
и функцию, которая добавляет ему в конец все строки из исходного списка, начинающиеся с "a". 
Например, если передать функции список "a" "b" "c", она должна модифицировать его так, 
чтобы он содержал "a" "b" "c" "a". Функция принимает на вход один аргумент — список, и ничего не возвращает.*/ 