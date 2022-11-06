#include "tree.h"

typedef struct Node {
	int key;
	char* value;
	struct Node* leftChild;
	struct Node* rightChild;
	struct Node* parent;
 } Node;

typedef struct Tree {
	Node* root;
} Tree;

Node* nodeSearch(Node* node, const int key) {
	if (node->key > key) {
		return node->leftChild;
	} 
	return node->rightChild;
}

int choiceChild(Node* node, const int key) {
	return node->key > key ? 1 : -1;
}

int rightOrLeftChild(Node* node) {
	if (node->parent->leftChild == node) {
		return 1;
	}
	return -1;
}

Tree* createTree(void) {
	Tree* tree= malloc(sizeof(Tree));
	if (tree == NULL) {
		return;
	}
	tree->root = NULL;
	return tree;
}

void addElement(Tree* tree, const int key, const char* value) {
	if (tree->root == NULL) {
		Node* newNode = malloc(sizeof(Node));
		newNode->key = key;
		newNode->value = value;
		newNode->rightChild = NULL;
		newNode->leftChild = NULL;
		newNode->parent = NULL;
		tree->root = newNode;
	} else {
		Node* currentNode = tree->root;
		while (true) {
			if (nodeSearch(currentNode, key) != NULL && currentNode->key != key) {
				currentNode = nodeSearch(currentNode, key);
			} else { 
				break; 
			}
		}
		if (currentNode->key == key) {
			currentNode->value = value;
			return;
		}
		Node* newNode = malloc(sizeof(Node));
		newNode->key = key;
		newNode->value = value;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->parent = currentNode;
		if (choiceChild(currentNode, key) == 1) {
			currentNode->leftChild = newNode;
		} else {
			currentNode->rightChild = newNode;
		}
	}
	return;
}

char* searchValueFromKey(Tree* tree, const int key) {
	Node* currentNode = tree->root;
	while (true) {
		if (currentNode == NULL) {
			return "NULL";
		}
		if (currentNode->key > key) {
			currentNode = currentNode->leftChild;
		} else if (currentNode->key < key) {
			currentNode = currentNode->rightChild;
		} else if (currentNode->key == key) {
			return currentNode->value;
		}
	}
}

bool isKeyInTree(Tree* tree, const int key) {
	Node* currentNode = tree->root;
	while (true) {
		if (currentNode == NULL) {
			return false;
		}
		if (currentNode->key > key) {
			currentNode = currentNode->leftChild;
		}
		else if (currentNode->key < key) {
			currentNode = currentNode->rightChild;
		}
		else if (currentNode->key == key) {
			return tree;
		}
	}
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

void deleteElement(Tree* tree, const int key) {
	if (!isKeyInTree(tree, key)) {
		return;
	}
	Node* currentNode = tree->root;
	while (true) {
		if (currentNode->key > key) {
			currentNode = currentNode->leftChild;
		}
		else if (currentNode->key < key) {
			currentNode = currentNode->rightChild;
		}
		else if (currentNode->key == key) {
			break;
		}
	}
	if (currentNode->rightChild == NULL && currentNode->leftChild == NULL) {
		if (rightOrLeftChild(currentNode) == 1) {
			currentNode->parent->leftChild = NULL;
		} else {
			currentNode->parent->rightChild = NULL;
		}
		currentNode->key = NULL;
		currentNode->value = NULL;
		free(currentNode);
		return;
	}
	Node* replacementNode = theMostRightChild(currentNode);
	currentNode->key = replacementNode->key;
	currentNode->value = replacementNode->value;
	replacementNode->parent->rightChild = replacementNode->leftChild;
	free(replacementNode);
}

void deleteTreeRecursive(Node* node) {
	if (node == NULL) {
		return;
	}

	deleteTreeRecursive(node->leftChild);
	deleteTreeRecursive(node->rightChild);

	node->value = NULL;
	free(node);
	node = NULL;
}

void deleteTree(Tree** tree) {
	deleteTreeRecursive((*tree)->root);
	free(*tree);
	*tree = NULL;
}
