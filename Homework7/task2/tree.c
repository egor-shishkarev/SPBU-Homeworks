#include "tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUMBER_SIZE 5

typedef struct Node {
	char* value;
	struct Node* leftChild;
	struct Node* rightChild;
} Node;

typedef struct Tree {
	Node* root;
} Tree;

void addToTreeRecursion(FILE* file, Node* node, int* errorCode) {
	getc(file);
	char* operator = calloc(2, sizeof(char));
	if (operator == NULL) {
		*errorCode = -1;
		return;
	}
	operator[0] = getc(file);
	getc(file);
	char* nextSymbol = calloc(2, sizeof(char));
	nextSymbol[0] = (char)getc(file);
	if (nextSymbol[0] == '(') {
		ungetc(nextSymbol[0], file);
		Node* newLeftNode = calloc(1, sizeof(Node));
		if (newLeftNode == NULL) {
			free(operator);
			free(nextSymbol);
			*errorCode = -1;
			return;
		}
		node->value = operator;
		node->leftChild = newLeftNode;
		addToTreeRecursion(file, newLeftNode, errorCode);
		if (*errorCode == -1) {
			free(newLeftNode);
			free(operator);
			free(nextSymbol);
			return;
		}
	} else {
		ungetc(nextSymbol[0], file);
		node->leftChild = calloc(1, sizeof(Node));
		if (node->leftChild == NULL) {
			*errorCode = -1;
			return;
		}
		node->leftChild->value = calloc(MAX_NUMBER_SIZE + 1, sizeof(char));
		if (node->leftChild->value == NULL) {
			free(node->leftChild);
			*errorCode = -1;
			return;
		}
		fscanf(file, "%s", node->leftChild->value);
	}
	getc(file);
	nextSymbol[0] = (char)getc(file);
	if (nextSymbol[0] == '(') {
		ungetc(nextSymbol[0], file);
		Node* newRightNode = calloc(1, sizeof(Node));
		if (newRightNode == NULL) {
			free(operator);
			free(nextSymbol);
			*errorCode = -1;
			return;
		}
		node->rightChild = newRightNode;
		addToTreeRecursion(file, newRightNode, errorCode);
		if (*errorCode == -1) {
			free(newRightNode);
			free(operator);
			free(nextSymbol);
			return;
		}
	} else {
		ungetc(nextSymbol[0], file);
		node->rightChild = calloc(1, sizeof(Node));
		if (node->rightChild == NULL) {
			free(operator);
			free(nextSymbol);
			*errorCode = -1;
			return;
		}
		node->rightChild->value = calloc(MAX_NUMBER_SIZE + 1, sizeof(char));
		if (node->rightChild->value == NULL) {
			free(node->rightChild);
			free(operator);
			free(nextSymbol);
			*errorCode = -1;
			return;
		}
		node->value = operator;
		fscanf(file, "%[^)]", node->rightChild->value);
		getc(file);
	}
}

Tree* readFileToTree(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		return NULL;
	}
	Tree* tree = calloc(1, sizeof(Tree));
	if (tree == NULL) {
		return NULL;
	}
	tree->root = malloc(sizeof(Node));
	if (tree->root == NULL) {
		fclose(file);
		return NULL;
	}
	int errorCode = 0;
	addToTreeRecursion(file, tree->root, &errorCode);
	if (errorCode == -1) {
		fclose(file);
		deleteTree(&tree);
		return NULL;
	}
	fclose(file);
	return tree;
}

void deleteTreeRecursive(Node* node) {
	if (node == NULL) {
		return;
	}
	deleteTreeRecursive(node->leftChild);
	deleteTreeRecursive(node->rightChild);
	free(node->value);
	free(node);
	node = NULL;
}

void deleteTree(Tree** tree) {
	if (*tree == NULL) {
		return;
	}
	if ((*tree)->root == NULL) {
		free(*tree);
		*tree = NULL;
		return;
	}
	deleteTreeRecursive((*tree)->root);
	free(*tree);
	*tree = NULL;
}

bool isOperation(char* arrayOfSymbols) {
	return arrayOfSymbols[0] == '+' || arrayOfSymbols[0] == '-' || arrayOfSymbols[0] == '*' || arrayOfSymbols[0] == '/';
}

void treeTraversal(Node* node) {
	if (isOperation(node->value)) {
		printf("(%s ", node->value);
	} else {
		printf("%s ", node->value);
	}
	if (node->leftChild != NULL) {
		treeTraversal(node->leftChild);
	}
	if (node->rightChild != NULL) {
		treeTraversal(node->rightChild);
	}
	if (node->rightChild != NULL && node->leftChild != NULL) {
		printf(") ");
	}
}

void treePrint(Tree* tree) {
	treeTraversal(tree->root);
}

int calculateResult(Node* node) {
	if (isOperation(node->value)) {
		const char operation = (node->value)[0];
		switch (operation) {
		case '+': {
			return calculateResult(node->leftChild) + calculateResult(node->rightChild);
		}
		case '-': {
			return calculateResult(node->leftChild) - calculateResult(node->rightChild);
		}
		case '*': {
			return calculateResult(node->leftChild) * calculateResult(node->rightChild);
		}
		case '/': {
			return calculateResult(node->leftChild) / calculateResult(node->rightChild);
		}
		}
	} else if (node != NULL) {
		return atoi(node->value);
	}
	return 0;
}

int treeResult(Tree* tree) {
	return calculateResult(tree->root);
}
