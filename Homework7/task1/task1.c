#include "tree.h"
#include <stdio.h>

int main() {
	Tree* tree = createTree();
	addElement(tree, 8, "Egor");
	addElement(tree, 3, "Anton");
	addElement(tree, 10, "Masha");
	addElement(tree, 14, "Petr");
	addElement(tree, 13, "Evpatiy");
	addElement(tree, 1, "Evgeniy");
	addElement(tree, 6, "Roman");
	addElement(tree, 4, "Alla");
	addElement(tree, 7, "Ivan");
	printf("%s", searchValueFromKey(tree, 10));
	printf("\n%d", isKeyInTree(tree, 10));
	printf("%s", theMostRightChild(tree));
	return 0;
}