#include <stdio.h>
#include "My_library.h"

int main() {
	int p=10, q=20;
	double x = 5.25;
	
	sayHello();
	printf("sum of %d and %d is %d\n", p, q, add(p, q));
	printf("Radius: %1f Area: %1f", x, area(x));
	
	return 0;
}
