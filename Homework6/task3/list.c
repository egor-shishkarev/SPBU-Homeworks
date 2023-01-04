#include "list.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef enum deleteMode {
    erase,
    delete
} deleteMode;

typedef enum sortMode {
    name,
    phone
} sortMode;

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

List* createList(void) {
    return calloc(1, sizeof(List));
}

void addElement(List* list, char* name, char* phone, const int position) {
    if (list == NULL) {
        //*errorCode = -1;
        return;
    }
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        //*errorCode = -1;
        return;
    }
    newNode->position = position;
    char* newName = calloc(strlen(name) + 1, sizeof(char));
    if (newName == NULL) {
        free(newNode);
        //*errorCode = -1;
        return;
    }
    strcpy(newName, name);
    newNode->name = newName;
    char* newPhone = calloc(strlen(phone) + 1, sizeof(char));
    if (newPhone == NULL) {
        free(newNode);
        free(newName);
        //*errorCode = -1;
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

List* createAdditionalList(List* list, const int left, const int right) {
    List* additionalList = createList();
    Node* currentNode = list->head;
    if (left - right != 0 || currentNode->position != left) {
        while (currentNode->position != left) {
            currentNode = currentNode->next;
        }
    }
    for (int i = 0; i < right - left + 1; ++i) {
        addElement(additionalList, currentNode->name, currentNode->phone, currentNode->position);
        currentNode = currentNode->next;
    }
    return additionalList;
}

List* mergeLists(List* firstList, List* secondList, sortMode mode) {
    List* mergedList = createList();
    Node* firstListNode = firstList->head;
    Node* secondListNode = secondList->head;
    while (firstListNode != NULL || secondListNode != NULL) {
        if (firstListNode != NULL) {
            if (secondListNode != NULL) {
                if ((strcmp(firstListNode->name, secondListNode->name) >= 0 && mode == name) || (strcmp(firstListNode->phone, secondListNode->phone) >= 0 && mode == phone)) {
                    addElement(mergedList, secondListNode->name, secondListNode->phone, secondListNode->position);
                    secondListNode = secondListNode->next;
                } else {
                    addElement(mergedList, firstListNode->name, firstListNode->phone, firstListNode->position);
                    firstListNode = firstListNode->next;
                }
            } else {
                addElement(mergedList, firstListNode->name, firstListNode->phone, firstListNode->position);
                firstListNode = firstListNode->next;
            }
        } else {
            addElement(mergedList, secondListNode->name, secondListNode->phone, secondListNode->position);
            secondListNode = secondListNode->next;
        }
    }
    deleteList(&firstList, erase);
    deleteList(&secondList, erase);
    return mergedList;
}

List* splitList(List* list, const int leftIndex, const int rightIndex, sortMode mode) {
    const int middleIndex = (leftIndex + rightIndex) / 2;
    if (rightIndex - leftIndex > 0) {
        List* firstList = createAdditionalList(list, leftIndex, middleIndex);
        List* splittedFirstList = splitList(firstList, leftIndex, middleIndex, mode);
        List* secondList = createAdditionalList(list, middleIndex + 1, rightIndex);
        List* splittedSecondList = splitList(secondList, middleIndex + 1, rightIndex, mode);
        List* mergedList = mergeLists(splittedFirstList, splittedSecondList, mode);
        deleteList(&firstList, erase);
        deleteList(&secondList, erase);
        return mergedList;
    } else {
        return createAdditionalList(list, leftIndex, rightIndex);
    }

}

List* mergeSort(List* list, sortMode mode) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    List* mergedList = splitList(list, 0, list->length - 1, mode);
    return mergedList;
}

void readFromFile(List* list, const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        //*errorCode = -1;
        return;
    }
    if (list == NULL) {
        //*errorCode = -1;
        return;
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
        addElement(list, name, phone/*, errorCode*/, list->length);
        ++list->length;
        /*if (*errorCode == -1) {
            fclose(file);
            return;
        }*/
    }
    fclose(file);
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

void deleteElement(List* list, Node* node, deleteMode mode) {
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

void deleteList(List** list, deleteMode mode) {
    if ((*list) == NULL) {
        return;
    } else if ((*list)->head == NULL) {
        free((*list));
        return;
    }
    Node* currentNode = (*list)->head;
    while (currentNode != NULL) {
        deleteElement((*list), currentNode, mode);
        currentNode = (*list)->head;
    }
    free((*list));
    (*list) = NULL;
}
