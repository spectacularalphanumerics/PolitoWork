//    THIS CODE IS BROKEN AND DOES NOT WORK, GIVING UP FOR NOW

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH 25
#define MAX_SEQUENCE_LENGTH 5
#define MAX_WORDS_TO_PRINT 10

// Function to check if a word contains the sequence (case insensitive)
int contains_sequence(const char *word, const char *sequence) {
    char word_lower[MAX_WORD_LENGTH + 1], sequence_lower[MAX_SEQUENCE_LENGTH + 1];

    // Convert word to lowercase
    for (int i = 0; word[i] != '\0'; i++) {
        word_lower[i] = tolower(word[i]);
    }
    word_lower[strlen(word)] = '\0';

    // Convert sequence to lowercase
    for (int i = 0; sequence[i] != '\0'; i++) {
        sequence_lower[i] = tolower(sequence[i]);
    }
    sequence_lower[strlen(sequence)] = '\0';

    // Check if sequence exists in the word
    if (strstr(word_lower, sequence_lower) != NULL) {
        return 1;
    }
    return 0;
}

// Function to extract words from a line and check for sequences
void process_line(char *line, const char **sequences, int num_sequences, int *word_count) {
    char word[MAX_WORD_LENGTH + 1];
    int word_len = 0;
    int sequence_found[MAX_SEQUENCE_LENGTH] = {0};

    // Debugging: Print the entire line being processed
    printf("Processing line: '%s'\n", line);

    // Iterate through the line to extract words
    for (int i = 0; line[i] != '\0'; i++) {
        if (isalnum(line[i])) {
            // Add alphanumeric characters to the word
            if (word_len < MAX_WORD_LENGTH) {
                word[word_len++] = line[i];
            }
        } else {
            if (word_len > 0) {
                word[word_len] = '\0'; // Null-terminate the word
                word_len = 0;  // Reset for the next word

                // Debugging: Print word being checked
                printf("Checking word: '%s'\n", word);

                // Check each sequence
                for (int j = 0; j < num_sequences; j++) {
                    if (contains_sequence(word, sequences[j])) {
                        // Print the sequence and word info (up to 10 occurrences per sequence)
                        printf("Sequence '%s' found in word: '%s' (Position: %d)\n", sequences[j], word, *word_count);
                    }
                }

                (*word_count)++; // Increment the word count
            }
        }
    }
}

// Function to count words in a line (helps with positioning words)
int count_words_in_line(char *line) {
    int count = 0;
    int in_word = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (isalnum(line[i])) {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }

    return count;
}

// Main function to read files and execute the search
int main() {
    FILE *sequences_file = fopen("sequences.txt", "r");
    FILE *text_file = fopen("text.txt", "r");

    if (!sequences_file || !text_file) {
        printf("Error opening file(s).\n");
        return 1;
    }

    int num_sequences;
    fscanf(sequences_file, "%d\n", &num_sequences);

    // Read all sequences from the sequences.txt file
    char sequences[MAX_SEQUENCE_LENGTH][MAX_SEQUENCE_LENGTH + 1];
    for (int i = 0; i < num_sequences; i++) {
        fgets(sequences[i], MAX_SEQUENCE_LENGTH + 1, sequences_file);
        sequences[i][strcspn(sequences[i], "\n")] = '\0'; // Remove newline
    }

    // Debugging: Print the sequences that were read
    printf("Sequences to search for:\n");
    for (int i = 0; i < num_sequences; i++) {
        printf("'%s'\n", sequences[i]);
    }

    // Process the text file line by line
    int word_count = 1; // Word count starting at 1
    char line[201];
    while (fgets(line, sizeof(line), text_file)) {
        process_line(line, (const char **)sequences, num_sequences, &word_count);
    }

    fclose(sequences_file);
    fclose(text_file);

    return 0;
}
