﻿#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>

int main() {
	setlocale(LC_ALL, ".UTF-8");
	printf("Данная программа находит наиболее часто встречающийся элемент в массиве.\n");
	FILE* file = fopen("test1.txt", "r");
	if (file == NULL) {
		printf("Файл не найден.");
		return 1;
	}
	char *data[300] = { 0 };
	int linesRead = 0;
	while (!feof(file)) {
		char *buffer = malloc(sizeof(char) * 300); // fscanf(file, "%[^ \ ▶ Или:fgets(buffer, sizeof(buffer), file); ▶ Working directory n ]", buffer);
		const int readBytes = fgets(buffer, sizeof(buffer), file); //  fgets(buffer, sizeof(buffer), file);
		if (readBytes < 0) {
			free(buffer);
			break;
		}
		data[linesRead] = buffer;
		++linesRead;
	}
	fclose(file);
	printf("Созданный массив: \n");
	for (int i = 0; i < linesRead; ++i) {
		printf("%s", data[i]);
	}
	return 0;
}