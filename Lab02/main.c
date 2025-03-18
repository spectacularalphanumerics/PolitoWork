#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int encoding(FILE *fin, FILE *fout) {
    FILE *inputFile = fopen(fin, "r");
    FILE *outputFile = fopen(fout, "w");

    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile); // Close the input file if output file fails to open
        return 1;
    }



    int k = 0; // Counter for numeric characters
    char prevChar = '\0'; // Track the previous character

    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        if (isdigit(ch)) {
            // Re-encode numeric characters
            int newChar = ch + k;
            if (newChar > '9') {
                newChar -= 10; // Wrap around after '9'
            }
            fputc(newChar, outputFile);
            k = (k + 1) % 10; // Increment k and wrap around after 9
        } else if (isalpha(ch)) {
            // Re-encode alphabetic characters
            if (isalpha(prevChar)) {
                int h = isupper(prevChar) ? prevChar - 'A' : prevChar - 'a';
                int newChar = ch + h;
                if (isupper(ch) && newChar > 'Z') {
                    newChar -= 26; // Wrap around after 'Z'
                } else if (islower(ch) && newChar > 'z') {
                    newChar -= 26; // Wrap around after 'z'
                }
                fputc(newChar, outputFile);
            } else {
                fputc(ch, outputFile); // Leave unchanged if preceded by non-alphabetic
            }
        } else {
            fputc(ch, outputFile); // Leave non-alphabetic and non-numeric characters unchanged
        }
        prevChar = ch; // Update previous character
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

int main() {
    const char *inputFileName = "in.txt";
    const char *outputFileName = "out.txt";

    printf("Input file: %s\n", inputFileName);
    printf("Output file: %s\n", outputFileName);

    if (encoding(inputFileName, outputFileName) != 0) {
        fprintf(stderr, "Encoding failed. Check the file paths and permissions.\n");
        return 1;
    }

    printf("Encoding completed successfully.\n");
    return 0;
}
