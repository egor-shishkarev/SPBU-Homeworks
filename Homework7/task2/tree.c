#include "tree.h"

typedef struct Node {
	int key;
	char value;
	struct Node* leftChild;
	struct Node* rightChild;
	struct Node* parent;
} Node;

typedef struct Tree {
	Node* root;
} Tree;

Tree* createTree(int* errorCode) {
	Tree* tree = malloc(sizeof(Tree));
	if (tree == NULL) {
		*errorCode = -1;
		return -1;
	}
	tree->root = NULL;
	return tree;
}


Tree* createParseTree(const char* arrayOfSymbols, const int lengthOfString) {
	Tree* tree = malloc(sizeof(Tree));
	if (tree == NULL) {
		return -1;
	}
	tree->root = NULL;

	return tree;
}

void deleteTreeRecursive(Node* node) {
	if (node == NULL) {
		return;
	}

	deleteTreeRecursive(node->leftChild);
	deleteTreeRecursive(node->rightChild);

	free(node->value);
	node->value = NULL;
	free(node);
	node = NULL;
}

void deleteTree(Tree** tree) {
	if ((*tree) == NULL) {
		return;
	}
	deleteTreeRecursive((*tree)->root);
	free(*tree);
	*tree = NULL;
}