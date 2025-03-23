#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_LINE_LENGTH 25

char isPunc(char c) {
    const char *punc = ",.?:;'";
    for (int i = 0; punc[i] != '\0'; i++) {
        if (c == punc[i]) {
            return 1;
        }
    }
    return 0;
}
void capitalizeAfterSentenceEnd(char *str) {
    int capitalizeNext = 0;
    for (int i= 0; str[i]!='\0' ; i++) {
        if (capitalizeNext && isalpha(str[i])) {
            str[i] = toupper(str[i]);
            capitalizeNext = 0;
        }
        if (str[i] == '.' || str[i] == '?' || str[i] == '!') {
            capitalizeNext = 1;
        }
    }
}

//      processing function, its misspelt but just noticed and can't be asked to change name
void procesFile() {
    FILE *input = fopen(INPUT_FILE, "r");
    FILE *output = fopen(OUTPUT_FILE, "w");
    if (!input || !output) {
        printf("Error opening file\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), input)) {
        for (int i = 0 ; line[i] != '\0' ; i++) {
            if (isdigit(line[i])) {
                line[i] = '*';
            }
        }

        for (int i = 0 ; line[i] != '\0' ; i++) {
            if (ispunct(line[i])) {
                char next = line[i+1];
                if (next != ' ' && next != '\n' && !isPunc(next)) {
                    memmove(&line[i + 2], &line[i + 1], strlen(&line[i + 1]) + 1);
                    line[i + 1] = ' ';
                }
            }
        }
        capitalizeAfterSentenceEnd(line);

        //      Process line to ensure length
        int originalLength = strlen(line);
        if (line[originalLength - 1] == '\n') {
            line[originalLength - 1] = '\0';
            originalLength--;       //      exclude newwling char from count
        }

        //      chop sentence up
        int start = 0;
        while (start < originalLength) {
            char chunk[MAX_LINE_LENGTH + 1]; // +1 for null terminator
            int chunkLength = (originalLength - start > MAX_LINE_LENGTH) ? MAX_LINE_LENGTH : (originalLength - start);

            // Copy the chunk
            strncpy(chunk, line + start, chunkLength);
            chunk[chunkLength] = '\0'; // Null-terminate the chunk

            // Append spaces for alignment if the chunk is shorter than MAX_LINE_LENGTH
            while (strlen(chunk) < MAX_LINE_LENGTH) {
                strcat(chunk, " ");
            }

            // Format the output line
            char formattedLine[256];
            snprintf(formattedLine, sizeof(formattedLine), "%s | c:%d\n", chunk, chunkLength);

            // Write the formatted line to the output file
            fputs(formattedLine, output);

            // Move to the next chunk
            start += chunkLength;
        }
    }
    fclose(input);
    fclose(output);
}

int main () {
    procesFile();
    printf("Processing complete, check %s for output.\n", OUTPUT_FILE);

    return 0;
}

