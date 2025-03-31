#include <stdio.h>

void subSequences(int v[], int n) {
    int start = -1, end = -1;
    int max_length = 0, curr_length = 0;

    for (int i = 0; i < n; i++) {
        // If we encounter a non-zero element, continue the current subarray
        if (v[i] != 0) {
            if (start == -1) {
                start = i;  // Starting point of the new subarray
            }
            curr_length++;
        }
        else {
            // When we encounter zero or the end of a subarray, check if it's the longest
            if (curr_length > max_length) {
                max_length = curr_length;
                end = i - 1;
            }
            // Reset for the next possible subarray
            start = -1;
            curr_length = 0;
        }
    }

    // Final check after the loop in case the longest subarray ends at the last element
    if (curr_length > max_length) {
        max_length = curr_length;
        end = n - 1;
    }

    // Now print all subarrays of maximum length
    curr_length = 0;
    start = -1;
    for (int i = 0; i < n; i++) {
        if (v[i] != 0) {
            if (start == -1) {
                start = i;  // Starting point of the new subarray
            }
            curr_length++;
        } else {
            if (curr_length == max_length) {
                // Print the subarray if it's the longest
                for (int j = start; j < start + max_length; j++) {
                    printf("%d ", v[j]);
                }
                printf("\n");
            }
            // Reset for the next possible subarray
            start = -1;
            curr_length = 0;
        }
    }

    // Check the last subarray if it's of maximum length
    if (curr_length == max_length) {
        for (int i = start; i < start + max_length; i++) {
            printf("%d ", v[i]);
        }
        printf("\n");
    }
}

int main() {
    int n;

    // Input the size of the array
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int v[n];

    // Input the array elements
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    // Call the function to print the sub-vectors
    subSequences(v, n);

    return 0;
}
