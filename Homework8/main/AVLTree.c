#include <malloc.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char* key;
    char* value;
    int balance;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

typedef struct AVLTree {
    Node* root;
} AVLTree;

AVLTree* createTree(int* errorCode) {
    AVLTree* tree = calloc(1, sizeof(AVLTree));
    if (tree == NULL) {
        *errorCode = -1;
    }
    return tree;
}

void deleteTreeRecursion(Node* node) {
    if (node == NULL) {
        return;
    }
    deleteTreeRecursion(node->leftChild);
    deleteTreeRecursion(node->rightChild);
    free(node->key);
    free(node->value);
    free(node);
}

void deleteTree(AVLTree** tree) {
    if (*tree == NULL) {
        return;
    }
    if ((*tree)->root == NULL) {
        free(*tree);
        return;
    }
    deleteTreeRecursion((*tree)->root);
    free(*tree);
    *tree = NULL;
}

Node* createNode(const char* key, const char* value, int* errorCode) {
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL) {
        *errorCode = -1;
        return NULL;
    }
    newNode->key = calloc(strlen(key) + 1, sizeof(char));
    if (newNode->key == NULL) {
        free(newNode);
        *errorCode = -1;
        return NULL;
    }
    strcpy(newNode->key, key);
    newNode->value = calloc(strlen(value) + 1, sizeof(char));
    if (newNode->value == NULL) {
        free(newNode->key);
        free(newNode);
        *errorCode = -1;
        return NULL;
    }
    strcpy(newNode->value, value);
    return newNode;
}

Node* leftRotate(Node* currentNode) {
    Node* rightNode = currentNode->rightChild;
    Node* leftGrandson = rightNode->leftChild;
    rightNode->leftChild = currentNode;
    currentNode->rightChild = leftGrandson;
    if (rightNode->balance != 0) {
        currentNode->balance = 0;
        rightNode->balance = 0;
    }
    else {
        currentNode->balance = 1;
        rightNode->balance = -1;
    }
    return rightNode;
}

Node* bigLeftRotate(Node* currrentNode) {
    Node* rightNode = currrentNode->rightChild;
    Node* leftGrandson = rightNode->leftChild;
    Node* leftGrandGrandson = leftGrandson->leftChild;
    Node* rightGrandGrandson = leftGrandson->rightChild;
    leftGrandson->rightChild = rightNode;
    leftGrandson->leftChild = currrentNode;
    currrentNode->rightChild = leftGrandGrandson;
    rightNode->leftChild = rightGrandGrandson;
    if (leftGrandson->balance == 1) {
        currrentNode->balance = -1;
        rightNode->balance = 0;
    }
    else if (leftGrandson->balance == -1) {
        currrentNode->balance = 0;
        rightNode->balance = 1;
    }
    else {
        currrentNode->balance = 0;
        rightNode->balance = 0;
    }
    leftGrandson->balance = 0;
    return leftGrandson;
}

Node* rightRotate(Node* currentNode) {
    Node* leftNode = currentNode->leftChild;
    Node* rightGrandson = leftNode->rightChild;
    leftNode->rightChild = currentNode;
    currentNode->leftChild = rightGrandson;
    if (leftNode->balance != 0) {
        currentNode->balance = 0;
        leftNode->balance = 0;
    }
    else {
        currentNode->balance = -1;
        leftNode->balance = 1;
    }
    return leftNode;
}

Node* bigRightRotate(Node* currentNode) {
    Node* leftNode = currentNode->leftChild;
    Node* rightGrandson = leftNode->rightChild;
    Node* leftGrandGrandson = rightGrandson->leftChild;
    Node* rightGrandGrandson = rightGrandson->rightChild;
    rightGrandson->leftChild = leftNode;
    rightGrandson->rightChild = currentNode;
    leftNode->rightChild = leftGrandGrandson;
    currentNode->leftChild = rightGrandGrandson;
    if (rightGrandson->balance == 1) {
        currentNode->balance = 0;
        leftNode->balance = 1;
    }
    else if (rightGrandson->balance == -1) {
        currentNode->balance = -1;
        leftNode->balance = 0;
    }
    else {
        currentNode->balance = 0;
        leftNode->balance = 0;
    }
    rightGrandson->balance = 0;
    return rightGrandson;
}

Node* balance(Node* node) {
    if (node->balance == 2) {
        if (node->rightChild->balance >= 0) {
            return leftRotate(node);
        }
        return bigLeftRotate(node);
    }
    if (node->balance == -2) {
        if (node->leftChild->balance <= 0) {
            return rightRotate(node);
        }
        return bigRightRotate(node);
    }
    return node;
}

Node* insert(Node* node, const char* key, const char* value, int* errorCode) {
    if (node == NULL) {
        *errorCode = -1;
        return NULL;
    }
    int direction = 0;
    if (strcmp(key, node->key) < 0) {
        if (node->leftChild != NULL) {
            node->leftChild = insert(node->leftChild, key, value, errorCode);
        } else {
            Node* newNode = createNode(key, value, errorCode);
            if (*errorCode == -1) {
                return NULL;
            }
            node->leftChild = newNode;
        }
        direction = -1;
    } else if (strcmp(key, node->key) > 0) {
        if (node->rightChild != NULL) {
            node->rightChild = insert(node->rightChild, key, value, errorCode);
        } else {
            Node* newNode = createNode(key, value, errorCode);
            if (*errorCode == -1) {
                return NULL;
            }
            node->rightChild = newNode;
        }
        direction = 1;
    } else {
        free(node->value);
        node->value = calloc(strlen(value) + 1, sizeof(char));
        if (node->value == NULL) {
            *errorCode = -1;
            return NULL;
        }
        strcpy(node->value, value);
    }
    node->balance = node->balance + direction;
    return balance(node);
}

void addElement(AVLTree* tree, const char* key, const char* value, int* errorCode) {
    if (tree == NULL) {
        *errorCode = -1;
        return;
    }
    Node* currentNode = tree->root;
    if (currentNode == NULL) {
        Node* newNode = createNode(key, value, errorCode);
        if (*errorCode == -1) {
            return;
        }
        tree->root = newNode;
        return;
    }
    tree->root = insert(currentNode, key, value, errorCode);
}

char* searchValueFromKey(AVLTree* tree, const char* key) {
    Node* currentNode = tree->root;
    while (currentNode != NULL) {
        if (strcmp(key, currentNode->key) < 0) {
            currentNode = currentNode->leftChild;
        } else if (strcmp(key, currentNode->key) > 0) {
            currentNode = currentNode->rightChild;
        } else if (strcmp(key, currentNode->key) == 0) {
            return currentNode->value;
        }
    }
    return NULL;
}

bool isKeyInTree(AVLTree* tree, const char* key) {
    return searchValueFromKey(tree, key) != NULL;
}

Node* theMostRightChild(Node* node) {
    Node* currentNode = node;
    if (currentNode->leftChild != NULL) {
        currentNode = currentNode->leftChild;
    }
    while (currentNode->rightChild != NULL) {
        currentNode = currentNode->rightChild;
    }
    return currentNode;
}

Node* deleteNode(Node* currentNode, const char* key, int* errorCode) {
    if (currentNode == NULL) {
        return currentNode;
    }
    int direction = 0;
    if (strcmp(key, currentNode->key) < 0) {
        currentNode->leftChild = deleteNode(currentNode->leftChild, key, errorCode);
        direction = -1;
    } else if (strcmp(key, currentNode->key) > 0) {
        currentNode->rightChild = deleteNode(currentNode->rightChild, key, errorCode);
        direction = 1;
    } else {
        if (currentNode->rightChild == NULL || currentNode->leftChild == NULL) {
            Node* child = currentNode->rightChild != NULL ? currentNode->rightChild : currentNode->leftChild;
            if (child == NULL) {
                free(currentNode->key);
                free(currentNode->value);
                free(currentNode);
                currentNode = NULL;
            } else {
                free(currentNode->key);
                free(currentNode->value);
                memcpy(currentNode, child, sizeof(Node));
                free(child);
            }
        } else {
            Node* additionalNode = theMostRightChild(currentNode);
            char* newKey = calloc(strlen(additionalNode->key) + 1, sizeof(char));
            if (newKey == NULL) {
                *errorCode = -1;
                return currentNode;
            }
            char* newValue = calloc(strlen(additionalNode->value) + 1, sizeof(char));
            if (newValue == NULL) {
                *errorCode = -1;
                free(newKey);
                return currentNode;
            }
            strcpy(newKey, additionalNode->key);
            strcpy(newValue, additionalNode->value);
            currentNode->value = newValue;
            Node* newNode = currentNode;
            currentNode = deleteNode(currentNode, additionalNode->key, errorCode);
            newNode->key = newKey;
        }
    }
    if (currentNode != NULL) {
        currentNode->balance = currentNode->balance - direction;
        return balance(currentNode);
    }
    return currentNode;
}

void deleteElement(AVLTree* tree, const char* key, int* errorCode) {
    if (tree == NULL) {
        *errorCode = -1;
        return;
    }
    *errorCode = 0;
    tree->root = deleteNode(tree->root, key, errorCode);
}
