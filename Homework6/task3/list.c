#include "list.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char* name;
    char* phone;
    int position;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
    int length;
} List;

List* createList(int* errorCode) {
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = -1;
        return NULL;
    }
    return list;
}

void addElement(List* list, char* name, char* phone, const int position, int* errorCode) {
    if (list == NULL) {
        *errorCode = -1;
        return;
    }
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        *errorCode = -1;
        return;
    }
    newNode->position = position;
    char* newName = calloc(strlen(name) + 1, sizeof(char));
    if (newName == NULL) {
        free(newNode);
        *errorCode = -1;
        return;
    }
    strcpy(newName, name);
    newNode->name = newName;
    char* newPhone = calloc(strlen(phone) + 1, sizeof(char));
    if (newPhone == NULL) {
        free(newNode);
        free(newName);
        *errorCode = -1;
        return;
    }
    strcpy(newPhone, phone);
    newNode->phone = newPhone;
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

List* createAdditionalList(List* list, const int left, const int right, int* errorCode) {
    List* additionalList = createList(errorCode);
    if (*errorCode == -1) {
        return NULL;
    }
    if (list == NULL) {
        *errorCode = -1;
        return NULL;
    }
    Node* currentNode = list->head;
    if (left - right != 0 || currentNode->position != left) {
        while (currentNode->position != left) {
            currentNode = currentNode->next;
        }
    }
    for (int i = 0; i < right - left + 1; ++i) {
        addElement(additionalList, currentNode->name, currentNode->phone, currentNode->position, errorCode);
        if (*errorCode == -1) {
            return NULL;
        }
        currentNode = currentNode->next;
    }
    return additionalList;
}

bool nodeComparison(Node* firstNode, Node* secondNode, SortMode mode) {
    if (mode == name && strcmp(firstNode->name, secondNode->name) >= 0) {
        return true;
    } else if (strcmp(firstNode->phone, secondNode->phone) >= 0 && mode == phone) {
        return true;
    } else {
        return false;
    }
}

List* mergeLists(List* firstList, List* secondList, SortMode mode, int* errorCode) {
    List* mergedList = createList(errorCode);
    if (mergedList == NULL) {
        *errorCode = -1;
        return NULL;
    }
    if (*errorCode == -1) {
        deleteList(&mergedList, erase);
        return NULL;
    }
    if (firstList == NULL || secondList == NULL) {
        *errorCode = -1;
        deleteList(&mergedList, erase);
        return NULL;
    }
    Node* firstListNode = firstList->head;
    Node* secondListNode = secondList->head;
    while (firstListNode != NULL || secondListNode != NULL) {
        if (firstListNode != NULL) {
            if (secondListNode != NULL) {
                if (nodeComparison(firstListNode, secondListNode, mode)) {
                    addElement(mergedList, secondListNode->name, secondListNode->phone, secondListNode->position, errorCode);
                    if (*errorCode == -1) {
                        deleteList(&mergedList, erase);
                        return NULL;
                    }
                    secondListNode = secondListNode->next;
                } else {
                    addElement(mergedList, firstListNode->name, firstListNode->phone, firstListNode->position, errorCode);
                    if (*errorCode == -1) {
                        deleteList(&mergedList, erase);
                        return NULL;
                    }
                    firstListNode = firstListNode->next;
                }
            } else {
                addElement(mergedList, firstListNode->name, firstListNode->phone, firstListNode->position, errorCode);
                if (*errorCode == -1) {
                    deleteList(&mergedList, erase);
                    return NULL;
                }
                firstListNode = firstListNode->next;
            }
        } else {
            addElement(mergedList, secondListNode->name, secondListNode->phone, secondListNode->position, errorCode);
            if (*errorCode == -1) {
                deleteList(&mergedList, erase);
                return NULL;
            }
            secondListNode = secondListNode->next;
        }
    }
    deleteList(&firstList, erase);
    deleteList(&secondList, erase);
    return mergedList;
}

List* recursivePartOfMergeSort(List* list, const int leftIndex, const int rightIndex, SortMode mode, int* errorCode) {
    if (list == NULL) {
        *errorCode = -1;
        return NULL;
    }
    const int middleIndex = (leftIndex + rightIndex) / 2;
    if (rightIndex - leftIndex > 0) {
        List* firstList = createAdditionalList(list, leftIndex, middleIndex, errorCode);
        if (firstList == NULL) {
            *errorCode = -1;
            return NULL;
        } else if (*errorCode == -1) {
            deleteList(&firstList, erase);
            return NULL;
        }
        List* splittedFirstList = recursivePartOfMergeSort(firstList, leftIndex, middleIndex, mode, errorCode);
        if (splittedFirstList == NULL) {
            deleteList(&firstList, erase);
            *errorCode = -1;
            return NULL;
        } else if (*errorCode == -1) {
            deleteList(&firstList, erase);
            deleteList(&splittedFirstList, erase);
            return NULL;
        }
        List* secondList = createAdditionalList(list, middleIndex + 1, rightIndex, errorCode);
        if (secondList == NULL) {
            deleteList(&firstList, erase);
            deleteList(&splittedFirstList, erase);
            *errorCode = -1;
            return NULL;
        } else if (*errorCode == -1) {
            deleteList(&firstList, erase);
            deleteList(&splittedFirstList, erase);
            deleteList(&secondList, erase);
            return NULL;
        }
        List* splittedSecondList = recursivePartOfMergeSort(secondList, middleIndex + 1, rightIndex, mode, errorCode);
        if (splittedSecondList == NULL) {
            deleteList(&firstList, erase);
            deleteList(&splittedFirstList, erase);
            deleteList(&secondList, erase);
            *errorCode = -1;
            return NULL;
        } else if (*errorCode == -1) {
            deleteList(&firstList, erase);
            deleteList(&splittedFirstList, erase);
            deleteList(&secondList, erase);
            deleteList(&splittedSecondList, erase);
            return NULL;
        }
        List* mergedList = mergeLists(splittedFirstList, splittedSecondList, mode, errorCode);
        if (mergedList == NULL) {
            deleteList(&firstList, erase);
            deleteList(&splittedFirstList, erase);
            deleteList(&secondList, erase);
            deleteList(&splittedSecondList, erase);
            *errorCode = -1;
            return NULL;
        } else if (*errorCode == -1) {
            deleteList(&firstList, erase);
            deleteList(&splittedFirstList, erase);
            deleteList(&secondList, erase);
            deleteList(&splittedSecondList, erase);
            deleteList(&firstList, erase);
            return NULL;
        }
        deleteList(&firstList, erase);
        deleteList(&secondList, erase);
        return mergedList;
    } else {
        List* oneElementList = createAdditionalList(list, leftIndex, rightIndex, errorCode);
        if (oneElementList == NULL) {
            *errorCode = -1;
            return NULL;
        } else if (*errorCode == -1) {
            deleteList(&oneElementList, erase);
            return NULL;
        }
        return oneElementList;
    }
}

List* mergeSort(List* list, SortMode mode, int* errorCode) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    List* mergedList = recursivePartOfMergeSort(list, 0, list->length - 1, mode, errorCode);
    return mergedList;
}

List* readFromFile(const char* path, int* errorCode) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        *errorCode = -1;
        return NULL;
    }
    List* list = createList(errorCode);
    if (*errorCode == -1) {
        return NULL;
    }
    while (!feof(file)) {
        char name[MAX_NAME_SIZE] = { "" };
        if (fscanf(file, "%s", &name) == -1) {
            break;
        }
        char phone[MAX_PHONE_SIZE] = { "" };
        if (fscanf(file, "%s", &phone) == -1) {
            break;
        }
        addElement(list, name, phone, list->length, errorCode);
        ++list->length;
        if (*errorCode == -1) {
            fclose(file);
            return NULL;
        }
    }
    fclose(file);
    return list;
}

void printList(List* list) {
    if (list == NULL || list->head == NULL) {
        printf("Список пуст или не существует!\n");
        return;
    }
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        printf("%s - %s\n", currentNode->name, currentNode->phone);
        currentNode = currentNode->next;
    }
}

void deleteElement(List* list, Node* node, DeleteMode mode) {
    Node* currentNode = list->head;
    if (currentNode != node) {
        while (currentNode->next != node) {
            currentNode = currentNode->next;
        }
    }
    if (node == list->head) {
        list->head = list->head->next;
    } else if (node == list->tail) {
        currentNode->next = NULL;
    } else {
        currentNode->next = node->next;
    }
    if (mode == delete) {
        free(node->name);
        free(node->phone);
    }
    free(node);
}

void deleteList(List** list, DeleteMode mode) {
    if ((*list) == NULL) {
        return;
    } else if ((*list)->head == NULL) {
        free(*list);
        return;
    }
    Node* currentNode = (*list)->head;
    while (currentNode != NULL) {
        deleteElement((*list), currentNode, mode);
        currentNode = (*list)->head;
    }
    free(*list);
    *list = NULL;
}

Node* headOfList(List* list) {
    return list->head;
}

Node* nextElement(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->next;
}

bool testNode(Node* node, char* name, char* phone) {
    return strcmp(node->name, name) == 0 && strcmp(node->phone, phone) == 0;
}
