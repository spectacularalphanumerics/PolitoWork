#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Maximum number of sequences to process
#define MAX_SEQUENCES 20
// Maximum length of each sequence (+1 for null terminator)
#define MAX_SEQ_LEN 5
// Maximum number of words to extract from text
#define MAX_WORDS 1000
// Maximum length of each word (+1 for null terminator)
#define MAX_WORD_LEN 25
// Maximum length of each line in input files
#define MAX_LINE_LEN 200

/**
 * Converts a string to lowercase in place
 * @param str The string to convert
 */
void to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

/**
 * Checks if a character is valid for a word (alphanumeric)
 * @param c The character to check
 * @return 1 if alphanumeric, 0 otherwise
 */
int is_word_char(char c) {
    return isalnum(c);
}

int main() {
    /* ==================== SEQUENCES PROCESSING ==================== */

    // Open the sequences file
    FILE *seq_file = fopen("sequences.txt", "r");
    if (seq_file == NULL) {
        perror("Error opening sequences.txt");
        return 1;
    }

    // Read number of sequences from first line
    int num_sequences;
    fscanf(seq_file, "%d", &num_sequences);
    fgetc(seq_file); // consume newline after the number

    // Enforce maximum sequences limit
    if (num_sequences > MAX_SEQUENCES) {
        num_sequences = MAX_SEQUENCES;
    }

    // Array to store all sequences in lowercase
    char sequences[MAX_SEQUENCES][MAX_SEQ_LEN + 1];

    // Read each sequence line by line
    for (int i = 0; i < num_sequences; i++) {
        fgets(sequences[i], MAX_SEQ_LEN + 1, seq_file);
        // Remove newline if present
        char *newline = strchr(sequences[i], '\n');
        if (newline) *newline = '\0';
        // Convert sequence to lowercase for case-insensitive comparison
        to_lower_case(sequences[i]);
    }
    fclose(seq_file);

    /* ==================== TEXT PROCESSING ==================== */

    // Open the text file to search through
    FILE *text_file = fopen("text.txt", "r");
    if (text_file == NULL) {
        perror("Error opening text.txt");
        return 1;
    }

    // Array to store all words found in the text (in lowercase)
    char words[MAX_WORDS][MAX_WORD_LEN + 1];
    int word_count = 0;
    char line[MAX_LINE_LEN + 1];

    // Read text file line by line until EOF or word limit reached
    while (fgets(line, MAX_LINE_LEN + 1, text_file) && word_count < MAX_WORDS) {
        int i = 0;
        // Process each character in the line
        while (line[i] != '\0' && word_count < MAX_WORDS) {
            // Skip any non-word characters (punctuation, spaces etc.)
            while (line[i] != '\0' && !is_word_char(line[i])) {
                i++;
            }

            if (line[i] == '\0') break;

            // Found start of a word - extract it
            int j = 0;
            while (is_word_char(line[i]) && j < MAX_WORD_LEN) {
                // Store word in lowercase for case-insensitive comparison
                words[word_count][j] = tolower(line[i]);
                i++;
                j++;
            }
            // Null-terminate the word
            words[word_count][j] = '\0';
            word_count++;
        }
    }
    fclose(text_file);

    /* ==================== SEQUENCE MATCHING ==================== */

    // For each sequence, search through all words for matches
    for (int s = 0; s < num_sequences; s++) {
        printf("Sequence %s is contained in:\n", sequences[s]);
        int matches_found = 0;

        // Check each word (up to 10 matches per sequence)
        for (int w = 0; w < word_count && matches_found < 10; w++) {
            // Check if current word contains the sequence
            if (strstr(words[w], sequences[s]) != NULL) {
                /*
                 * We found a match in lowercase words, but need to display
                 * the original case. This requires re-reading the file to
                 * find the original word at position w.
                 * Note: This is inefficient but meets requirements.
                 */
                FILE *text_file_again = fopen("text.txt", "r");
                if (text_file_again == NULL) {
                    perror("Error reopening text.txt");
                    return 1;
                }

                int current_word_pos = 0;
                char original_word[MAX_WORD_LEN + 1];
                int found = 0;

                // Scan through file again to find the original word
                while (fgets(line, MAX_LINE_LEN + 1, text_file_again) && !found) {
                    int i = 0;
                    while (line[i] != '\0' && !found) {
                        // Skip non-word characters
                        while (line[i] != '\0' && !is_word_char(line[i])) {
                            i++;
                        }

                        if (line[i] == '\0') break;

                        // Extract the next word
                        int j = 0;
                        char temp_word[MAX_WORD_LEN + 1];
                        while (is_word_char(line[i]) && j < MAX_WORD_LEN) {
                            temp_word[j] = line[i]; // Keep original case
                            i++;
                            j++;
                        }
                        temp_word[j] = '\0';

                        current_word_pos++;
                        // Check if this is the word we're looking for
                        if (current_word_pos == w + 1) {
                            strcpy(original_word, temp_word);
                            found = 1;
                        }
                    }
                }
                fclose(text_file_again);

                // Print the match with original case and position
                printf("%s (position %d)\n", original_word, w + 1);
                matches_found++;
            }
        }

        // If no matches found for this sequence
        if (matches_found == 0) {
            printf("No words found\n");
        }
    }

    return 0;
}
