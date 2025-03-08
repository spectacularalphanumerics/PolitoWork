#include <stdio.h>

#define pi 3.14
void square();
void circle();
int main() {
    char input;
    printf("Please enter Q for square or I for circle: ");
    scanf("%c", &input);
    printf("\n");

    switch (input) {
        case 'Q':
            square();
        break;
        case 'I':
            circle();
        break;
        default:
            printf("Please enter a valid input\n");
        break;
    }
    return 0;
}

void square() {
    float area;
    int x;
    char rand;
    printf("Please enter D to use diagonal length or S to use side length: ");
    scanf(" %c", &rand);
    printf("\nPlease enter length: ");
    scanf(" %d", &x);
    if (rand == 'D') {
        area = (x*x) / 2.0;
    } else if (rand == 'S') {
        area = x * x;
    } else {
        printf("Invalid input\n");
    }
    printf("The area is %f\n", area);
}

void circle() {
    float area;
    int x;
    char rand;
    printf("Please enter D to use diameter length or R to use radius length: ");
    scanf(" %c", &rand);
    printf("\n Please enter length: ");
    scanf(" %d", &x);
    if (rand == 'D') {
        area = (pi * x * x) / 4.0; ;
    } else if (rand == 'R') {
        area = x*x*pi;
    } else {
        printf("Invalid input\n");
    }
    printf("The area is %f\n", area);
}