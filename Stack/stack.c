#include <stdio.h>
#include "stackModule.h"

int main() {
	Stack* stack = createStack();
	push(stack, 100);
	push(stack, 200);
	push(stack, 300);
	int e = 0;
	pop(stack, &e);
	printf("%d", top(stack));
	printf("%d", top(stack));
	printf("%d", top(stack));
	return 0;
}
