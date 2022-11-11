#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

unsigned long long recursionFibonacci(unsigned long long number) {
	if (number > 93 || number < 1) {
		return 0;
	}
	if (number == 1 || number == 2) {
		return 1;
	}
	return recursionFibonacci(number - 1) + recursionFibonacci(number - 2);
}

unsigned long long iterativeFibonacci(unsigned long long number) {
	if (number > 93 || number < 1) {
		return 0;
	}
	unsigned long long firstNumber = 1;
	unsigned long long secondNumber = 1;
	unsigned long long thirdNumber = firstNumber + secondNumber;
	for (int i = 0; i < number - 1; ++i) {
		firstNumber = secondNumber;
		secondNumber = thirdNumber;
		thirdNumber = firstNumber + secondNumber;
	}
	return firstNumber;
}

int verificationIntScanf() {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		printf("Ошибка ввода. Введите целочисленное значение!\n");
	}
	return readValues;
}

bool fibonacciTest(unsigned long long number) {
	unsigned long long fibonacciRightNumbers[93] = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377,
		610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393,
		196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465,
		14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296,
		433494437, 701408733, 1134903170, 1836311903, 2971215073, 4807526976,
		7778742049, 12586269025, 20365011074, 32951280099, 53316291173,
		86267571272, 139583862445, 225851433717, 365435296162, 591286729879,
		956722026041, 1548008755920, 2504730781961, 4052739537881, 6557470319842,
		10610209857723, 17167680177565, 27777890035288, 44945570212853, 72723460248141,
		117669030460994, 190392490709135, 308061521170129, 498454011879264, 806515533049393,
		1304969544928657, 2111485077978050, 3416454622906707, 5527939700884757, 8944394323791464,
		14472334024676221, 23416728348467685, 37889062373143906, 61305790721611591, 99194853094755497,
		160500643816367088, 259695496911122585, 420196140727489673, 679891637638612258, 1100087778366101931,
		1779979416004714189, 2880067194370816120, 4660046610375530309, 7540113804746346429, 12200160415121876738 };
	if (number < 1 || number > 93) {
		return iterativeFibonacci(number) == 0 && recursionFibonacci(number) == 0;
	}
	if (number < 20) {
		return iterativeFibonacci(number) == fibonacciRightNumbers[number - 1] && recursionFibonacci(number) == fibonacciRightNumbers[number - 1];
	}
	return iterativeFibonacci(number) == fibonacciRightNumbers[number - 1];
	
}

bool testCorrectCase() {
	bool allTestsAreTrue = true;
	for (int i = 1; i < 94; ++i) {
		allTestsAreTrue *= fibonacciTest(i);
	}
	return allTestsAreTrue;
}

bool testIncorrectCase() {
	return fibonacciTest(-10) && fibonacciTest(120);
}

bool testEdgeCase() {
	return fibonacciTest(0) && fibonacciTest(93) && fibonacciTest(94);
}

int main() {
	setlocale(LC_ALL, ".1251");
	if (!(testCorrectCase() && testIncorrectCase() && testEdgeCase())) {
		printf("Тест провален!");
		return 1;
	}
	printf("Тесты пройдены успешно!\n");
	printf("Предупреждение! \nРекурсивный алгоритм работает долго: после 38 числа время выполнения больше одной секунды.\n");
	printf("Исходя из исследования, разница во времени работы алгоритмов становится заметна на 35 числе.\n");
	printf("Введите номер числа фиббоначи, которое вы хотите найти (Максимально возможное верно полученное число - 93) => ");
	int numberToSearch = verificationIntScanf();
	if (numberToSearch > 93) {
		printf("Вы ввели значение, для которого будет выведен неверный ответ, оно было автоматически изменено на максимально возможное.\n");
		numberToSearch = 93;
	}
	int flagOfRecursive = 1;
	if (numberToSearch > 38) {
		printf("Внимание! Вы уверены, что хотите использовать рекурсивный алгоритм? Введите 1, если хотите и 0, если нет => ");
		flagOfRecursive = verificationIntScanf();
	}
	switch (flagOfRecursive) {
	case 1:
		printf("Результат работы рекурсивного алгоритма = %llu \n", recursionFibonacci(numberToSearch));
		printf("Результат работы итеративного алгоритма = %llu ", iterativeFibonacci(numberToSearch));
		break;
	case 0:
		printf("Результат работы итеративного алгоритма = %llu ", iterativeFibonacci(numberToSearch));
		break;
	default:
		printf("Значение введено неверно!");
		break;
	}
	return 0;
}