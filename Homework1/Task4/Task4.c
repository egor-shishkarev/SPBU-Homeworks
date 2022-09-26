#include <stdio.h>
#include <math.h>

int main() {
	int countWays[28] = {0};
	for (int i = 0; i < 28; ++i) {
		countWays[i] = 0;
	}
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			for (int k = 0; k < 10; ++k) {
				countWays[i + j + k] += 1;
			}
		}
	}
	int sumWays = 0;
	for (int i = 0; i < 28; ++i) {
		sumWays += pow(countWays[i], 2);
	}
	printf("%d", sumWays);
}