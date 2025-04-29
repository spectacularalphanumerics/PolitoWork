#include <stdio.h>

int main(void) {
    int radius;
    float vol;
    printf("Input the radius: ");
    scanf("%d", &radius);
    vol = 3.14 * 4 / 3 * radius * radius * radius;
    printf("The volume of the sphere is %.2f\n", vol);
}