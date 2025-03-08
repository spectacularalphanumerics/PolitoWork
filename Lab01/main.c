#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char operation;
    float op1, op2, result;

    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("File could not be opened\n");
        return 1;
    }
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("File could not be opened\n");
        fclose(inputFile);
        return 1;
    }

    while (fscanf(inputFile, " %c %f %f", &operation, &op1, &op2) == 3) {

        switch (operation) {
            case '+':
                result = op1 + op2;
            continue;
            case '-':
                result = op1 - op2;
            continue;
            case '*':
                result = op1 * op2;
            continue;
            case '/':
                if (op2 != 0) {
                    result = op1 / op2;
                } else {
                    printf("Error: Division by zero is not allowed.\n");
                    return 1; // Exit the program with an error code
                }
            continue;
            default:
                printf("Error: Invalid operation.\n");
                continue;
        }

        fprintf(outputFile, "%f\n", result);

    }

    fclose(inputFile);
    fclose(outputFile);
    printf("Done\n");

    return 0;
}