#include <stdio.h>
#include <stdlib.h>

void print_submatrix(int matrix[20][20], int n, int dim, int row, int col) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf("%d ", matrix[row + i][col + j]);
        }
        printf("\n");
    }
}

int calculate_sum(int matrix[20][20], int n, int dim, int row, int col) {
    int sum = 0;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            sum += matrix[row + i][col + j];
        }
    }
    return sum;
}

int main() {
    FILE *file;
    char filename[21];
    int nr, nc;
    int matrix[20][20];

    // Get the filename
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Read the dimensions of the matrix
    fscanf(file, "%d %d", &nr, &nc);

    // Read the matrix
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);

    while (1) {
        int dim;

        // Ask user for the dimension of the submatrix
        printf("Enter the dimension (1 to %d) or a number out of range to exit: ", (nr < nc) ? nr : nc);
        scanf("%d", &dim);

        // Exit condition if the input dimension is out of range
        if (dim < 1 || dim > (nr < nc ? nr : nc)) {
            printf("Invalid dimension, exiting...\n");
            break;
        }

        // Print all square sub-matrices of size 'dim'
        printf("The square sub-matrices of dimension %d are:\n", dim);
        int max_sum = -1;
        int max_row = -1, max_col = -1;

        for (int i = 0; i <= nr - dim; i++) {
            for (int j = 0; j <= nc - dim; j++) {
                print_submatrix(matrix, nr, dim, i, j);

                // Calculate the sum of the current sub-matrix
                int sum = calculate_sum(matrix, nr, dim, i, j);

                // Check if this sum is the maximum encountered
                if (sum > max_sum) {
                    max_sum = sum;
                    max_row = i;
                    max_col = j;
                }
            }
        }

        // Print the sub-matrix with the maximum sum
        if (max_row != -1 && max_col != -1) {
            printf("The submatrix with maximum sum of elements (%d) is:\n", max_sum);
            print_submatrix(matrix, nr, dim, max_row, max_col);
        }
    }

    return 0;
}
