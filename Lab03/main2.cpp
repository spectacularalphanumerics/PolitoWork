#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

const char* stateToString(int state) {
    switch(state) {
        case 0: return "START";
        case 1: return "AFTER_OPERAND";
        case 2: return "AFTER_OPERATOR";
        case 3: return "AFTER_OPEN_BRACKET";
        default: return "UNKNOWN";
    }
}

bool verifyExpression(const char *expr) {    //    test ing
    int bracketCount = 0;
    int state = 0; // 0=start, 1=after operand, 2=after operator, 3=after open bracket
    bool inNumber = false;

    printf("Verifying expression: '%s'\n", expr);

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        // Skip spaces (allowed except within numbers)
        if (c == ' ') {
            if (inNumber) {
                return false;
            }
            continue;
        }

        if (isdigit(c)) {
            if (state == 1 && !inNumber) {
                return false;
            }
            inNumber = true;
            state = 1;
            continue;
        } else {
            inNumber = false;
        }

        if (c == '(') {
            if (state == 1) {
                return false;
            }
            bracketCount++;
            state = 3;
            continue;
        }

        if (c == ')') {
            if (bracketCount <= 0) {
                return false;
            }
            if (state == 2 || state == 3) {
                return false;
            }
            bracketCount--;
            state = 1;
            continue;
        }

        if (isOperator(c)) {
            if (state != 1) {
                return false;
            }
            state = 2;
            continue;
        }
        return false;
    }



    if (bracketCount != 0) {
        return false;
    }
    if (state != 1) {
        return false;
    }

    printf("SUCCESS: Expression is valid\n");
    return true;
}

int main() {
    FILE *file = fopen("expr.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[256];
    int lineNum = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';

        printf("\n=== Processing line %d ===\n", lineNum);
        if (!verifyExpression(line)) {
            printf("Error in expression %d\n", lineNum);
        }
        lineNum++;
    }

    fclose(file);
    return 0;
}