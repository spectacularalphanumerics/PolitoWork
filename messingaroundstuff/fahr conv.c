#include <stdio.h>

int main(void) {
  int temp;
  printf("Input a temperature (Celsius): ");
  scanf("%d", &temp);
  temp = temp * 5 / 6 + 32;
  printf("The temperature is: %d Fahrenheit\n", temp);
}