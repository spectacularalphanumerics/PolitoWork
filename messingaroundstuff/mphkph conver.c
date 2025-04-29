#include <stdio.h>
#include <string.h>
int main(void) {
    //    variable declarations
    float out;
    char choice;
    float speed;

    printf("Which value do you have already? (k/m): ");
    scanf("%c", &choice);
    printf("Input 0 when you want to stop.\n");

    while (speed != 0) {
        printf("Speed: ");
        scanf("%f", &speed);
        if (choice == 'k') {
            out = speed / 1.6;
            printf("%.2f mph\n", out);
        }
        else if (choice == 'm') {
            out = speed * 1.6;
            printf("%.2f kph\n", out);
        }
    }
    return 0;
}