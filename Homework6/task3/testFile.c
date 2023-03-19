#include "list.h"
#include <stdbool.h>
#include <stdio.h>

bool createListTest(void) {
	int errorCode = 0;
	List* list = createList(&errorCode);
	if (list == NULL) {
		return false;
	}
	if (headOfList(list) == NULL) {
		deleteList(&list, delete);
		return true;
	}
	deleteList(&list, delete);
	return false;
}

bool readFromFileTest(void) {
	int errorCode = 0;
	List* list = readFromFile("testFile.txt", &errorCode);
	if (errorCode == -1) {
		return false;
	}
	if (errorCode == -1) {
		deleteList(&list, delete);
		return false;
	}
	Node* firstNode = headOfList(list);
	Node* secondNode = nextElement(firstNode);
	Node* thirdNode = nextElement(secondNode);
	bool firstTest = testNode(firstNode, "Pavel", "04");
	bool secondTest = testNode(secondNode, "Masha", "06");
	bool thirdTest = testNode(thirdNode, "Egor", "03");
	bool result = firstTest && secondTest && thirdTest;
	deleteList(&list, delete);
	return result;
}

bool mergeSortTest(void) {
	int errorCode = 0;
	List* list = readFromFile("testFile.txt", &errorCode);
	if (errorCode == -1) {
		return false;
	}
	if (errorCode == -1) {
		deleteList(&list, delete);
		return false;
	}
	List* nameSortList = mergeSort(list, 0, &errorCode);
	if (errorCode == -1) {
		deleteList(&list, delete);
		return false;
	}
	Node* firstNameNode = headOfList(nameSortList);
	bool nameResult = testNode(firstNameNode, "Egor", "03") && testNode(nextElement(firstNameNode), "Masha", "06") && testNode(nextElement(nextElement(firstNameNode)), "Pavel", "04");
	List* phoneSortList = mergeSort(list, 1, &errorCode);
	if (errorCode == -1) {
		deleteList(&list, delete);
		deleteList(&nameSortList, delete);
		return false;
	}
	Node* firstPhoneNode = headOfList(phoneSortList);
	bool phoneResult = testNode(firstPhoneNode, "Egor", "03") && testNode(nextElement(firstPhoneNode), "Pavel", "04") && testNode(nextElement(nextElement(firstPhoneNode)), "Masha", "06");
	deleteList(&list, delete);
	deleteList(&nameSortList, delete);
	deleteList(&phoneSortList, delete);
	return nameResult && phoneResult;
}

bool allTests(void) {
	return createListTest() && readFromFileTest() && mergeSortTest();
}