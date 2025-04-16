#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	float a, b, sum;
	if (argc != 3) {
		printf("The execution should be %s <number1> <number2>!", argv[0]);
		return 1;
	}
	a = atof(argv[1]);
	b = atof(argv[2]);
	sum = a+b;
	printf("Program %s computes %f + %f = %f\n", argv[0], a, b, sum);
	return 0;
}
