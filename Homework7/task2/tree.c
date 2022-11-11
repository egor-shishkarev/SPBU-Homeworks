#include "tree.h"

typedef struct Node {
	char* value;
	struct Node* leftChild;
	struct Node* rightChild;
	struct Node* parent;
} Node;

typedef struct Tree {
	Node* root;
} Tree;

void addPartToTree(Tree* tree, char operation, char* operand1, char* operand2, Node* currentNode) {
	currentNode->value = operation;
	if (operand1[0] == '(') {

	} else {
		char* newValue = calloc(strlen(operand1), sizeof(char));
		strcpy(newValue, operand1);
		Node* newNode = malloc(sizeof(Node));
		newNode->parent = currentNode;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->value = newValue;
		currentNode->leftChild = newNode;
	}
	if (operand2[0] == '(') {

	} else {
		char* newValue = calloc(strlen(operand2), sizeof(char));
		strcpy(newValue, operand2);
		Node* newNode = malloc(sizeof(Node));
		newNode->parent = currentNode;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->value = newValue;
		currentNode->rightChild = newNode;
	}
	printf("[%c] [%s] [%s]", operation, operand1, operand2);
	printf("(%c (%s %s))", currentNode->value, currentNode->leftChild->value, currentNode->rightChild->value);
}


char* getOperation(char* arrayOfSymbols) {
	return arrayOfSymbols[1];
}

char* getOperand1(char* arrayOfSymbols) {
	int numberOfOpenBrackets = 0;
	int numberOfClosedBrackets = 0;
	const int lengthOfString = strlen(arrayOfSymbols);
	for (int i = 0; i < lengthOfString; ++i) {
		if (arrayOfSymbols[i] == '(') { 
			++numberOfOpenBrackets;
		}
		else if (arrayOfSymbols[i] == ')') {
			++numberOfClosedBrackets;
		}
		if (numberOfOpenBrackets == numberOfClosedBrackets + 1 && numberOfOpenBrackets > 1) {
			char operation = arrayOfSymbols[1];
			char* operand1 = calloc(i - 3 + 2, sizeof(char));
			if (operand1 == NULL) {
				return -1;
			}
			for (int j = 2; j < i; ++j) {
				operand1[j - 2] = arrayOfSymbols[j + 1];
			}
			char* operand2 = calloc(lengthOfString - i - 3, sizeof(char));
			if (operand2 == NULL) {
				return -1;
			}
			for (int k = i + 2; k < lengthOfString - 2; ++k) {
				operand2[k - i - 2] = arrayOfSymbols[k];
			}
			break;
		}
	}
	if (numberOfClosedBrackets == numberOfOpenBrackets) {
		int currentPosition = 3;
		while (arrayOfSymbols[currentPosition] != ' ') {
			++currentPosition;
		}
		char* operand1 = calloc(currentPosition - 3 + 1, sizeof(char));
		if (operand1 == NULL) {
			return -1;
		}
		for (int i = 3; i < currentPosition; ++i) {
			operand1[i - 3] = arrayOfSymbols[i];
		}
		char* operand2 = calloc(lengthOfString - 2 - currentPosition + 1, sizeof(char));
		if (operand2 == NULL) {
			return -1;
		}
		for (int i = currentPosition + 1; i < lengthOfString - 1; ++i) {
			operand2[i - currentPosition - 1] = arrayOfSymbols[i];
		}
		Node* node = malloc(sizeof(Node));
		node->parent = NULL;
		node->leftChild = NULL;
		node->rightChild = NULL;
		tree->root = node;
		addPartToTree(tree, arrayOfSymbols[1], operand1, operand2, tree->root);
	}
}

char* getOperand2(char* arrayOfSymbols) {

}
Tree* createParseTree(const char* arrayOfSymbols, const int lengthOfString) {
	Tree* tree = malloc(sizeof(Tree));
	if (tree == NULL) {
		return -1;
	}
	tree->root = NULL;
	int numberOfOpenBrackets = 0;
	int numberOfClosedBrackets = 0;
	for (int i = 0; i < lengthOfString; ++i) {
		if (arrayOfSymbols[i] == '(') {
			++numberOfOpenBrackets;
		} else if (arrayOfSymbols[i] == ')') {
			++numberOfClosedBrackets;
		}
		if (numberOfOpenBrackets == numberOfClosedBrackets + 1 && numberOfOpenBrackets > 1) {
			char operation = arrayOfSymbols[1];
			char* operand1 = calloc(i - 3 + 2, sizeof(char));
			if (operand1 == NULL) {
				return -1;
			}
			for (int j = 2; j < i; ++j) {
				operand1[j - 2] = arrayOfSymbols[j + 1];
			}
			char* operand2 = calloc(lengthOfString - i - 3, sizeof(char));
			if (operand2 == NULL) {
				return -1;
			}
			for (int k = i + 2; k < lengthOfString - 2; ++k) {
				operand2[k - i - 2] = arrayOfSymbols[k];
			}
			Node* node = malloc(sizeof(Node));
			node->parent = NULL;
			node->leftChild = NULL;
			node->rightChild = NULL;
			tree->root = node;
			addPartToTree(arrayOfSymbols[1], operation, operand1, operand2, tree->root);
			break;
		}
	}
	if (numberOfClosedBrackets == numberOfOpenBrackets) {
		int currentPosition = 3;
		while (arrayOfSymbols[currentPosition] != ' ') {
			++currentPosition;
		}
		char* operand1 = calloc(currentPosition - 3 + 1, sizeof(char));
		if (operand1 == NULL) {
			return -1;
		}
		for (int i = 3; i < currentPosition; ++i) {
			operand1[i - 3] = arrayOfSymbols[i];
		}
		char* operand2 = calloc(lengthOfString - 2 - currentPosition + 1, sizeof(char));
		if (operand2 == NULL) {
			return -1;
		}
		for (int i = currentPosition + 1; i < lengthOfString - 1; ++i) {
			operand2[i - currentPosition - 1] = arrayOfSymbols[i];
		}
		Node* node = malloc(sizeof(Node));
		node->parent = NULL;
		node->leftChild = NULL;
		node->rightChild = NULL;
		tree->root = node;
		addPartToTree(tree, arrayOfSymbols[1], operand1 , operand2, tree->root);
	}
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

long long int charToInt(char* number) {
	int currentPosition = 0;
	int result = 0;
	if (number[0] == '-') {
		currentPosition = 1;
	}
	while (number[currentPosition] != '\0') {
		result *= 10;
		result += (int)number[currentPosition] - 48;
		++currentPosition;
	}
	return result - 2 * result * (number[0] == '-');
}