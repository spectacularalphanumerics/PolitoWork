#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    int swaps;
    int outer_loops;
    int inner_loops[MAX_LEN];
    int total_iterations;
} SortStats;

void resetStats(SortStats *stats) {
    stats->swaps = 0;
    stats->outer_loops = 0;
    stats->total_iterations = 0;
    memset(stats->inner_loops, 0, sizeof(stats->inner_loops));
}

void printStats(const char *sort_name, SortStats stats, int length) {
    printf("\n=== %s ===\n", sort_name);
    printf("Swaps: %d\n", stats.swaps);
    printf("Outer loop iterations: %d\n", stats.outer_loops);
    printf("Inner loop iterations per outer loop:\n");
    for (int i = 0; i < stats.outer_loops; ++i) {
        printf("  Outer loop %d: %d inner iterations\n", i + 1, stats.inner_loops[i]);
    }
    printf("Total iterations: %d\n", stats.total_iterations);
}

void selectionSort(int arr[], int len, SortStats *stats) {
    resetStats(stats);
    for (int i = 0; i < len - 1; i++) {
        stats->outer_loops++;
        int min_idx = i;
        int inner_iterations = 0;
        for (int j = i + 1; j < len; j++) {
            inner_iterations++;
            stats->total_iterations++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        stats->inner_loops[i] = inner_iterations;
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            stats->swaps++;
        }
    }
}

void insertionSort(int arr[], int len, SortStats *stats) {
    resetStats(stats);
    for (int i = 1; i < len; i++) {
        stats->outer_loops++;
        int key = arr[i];
        int j = i - 1;
        int inner_iterations = 0;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            inner_iterations++;
            stats->swaps++;
            stats->total_iterations++;
        }
        stats->total_iterations++; // For the failed comparison
        stats->inner_loops[i - 1] = inner_iterations;
        arr[j + 1] = key;
    }
}

void shellSort(int arr[], int len, SortStats *stats) {
    resetStats(stats);
    int gap, i, j;
    for (gap = len / 2; gap > 0; gap /= 2) {
        stats->outer_loops++;
        int inner_iterations = 0;
        for (i = gap; i < len; i++) {
            int temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                inner_iterations++;
                stats->swaps++;
                stats->total_iterations++;
            }
            arr[j] = temp;
            stats->total_iterations++;
        }
        stats->inner_loops[stats->outer_loops - 1] = inner_iterations;
    }
}

void copyArray(int *dest, int *src, int len) {
    for (int i = 0; i < len; ++i)
        dest[i] = src[i];
}

int main() {
    FILE *file = fopen("sort.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int S;
    fscanf(file, "%d", &S);

    for (int s = 0; s < S; ++s) {
        int length;
        fscanf(file, "%d", &length);
        int original[MAX_LEN];
        for (int i = 0; i < length; ++i)
            fscanf(file, "%d", &original[i]);

        printf("\nSequence %d: ", s + 1);
        for (int i = 0; i < length; ++i)
            printf("%d ", original[i]);
        printf("\n");

        int arr[MAX_LEN];
        SortStats stats;

        copyArray(arr, original, length);
        selectionSort(arr, length, &stats);
        printStats("Selection Sort", stats, length);

        copyArray(arr, original, length);
        insertionSort(arr, length, &stats);
        printStats("Insertion Sort", stats, length);

        copyArray(arr, original, length);
        shellSort(arr, length, &stats);
        printStats("Shell Sort", stats, length);
    }

    fclose(file);
    return 0;
}
