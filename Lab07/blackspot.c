#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50
#define FILE_NAME "input.txt"

typedef struct {
    int row;
    int col;
    int height;
    int width;
    int area;
} Rectangle;

void findBlackRectangles(int matrix[MAX_SIZE][MAX_SIZE], int nr, int nc);
void exploreRectangle(int matrix[MAX_SIZE][MAX_SIZE], int nr, int nc, int row, int col, bool visited[MAX_SIZE][MAX_SIZE], Rectangle *rect);


int main() {
    FILE *file;
    char fileName[100];
    int nr, nc;
    int matrix[MAX_SIZE][MAX_SIZE];

    file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("File could not be opened\n");
        return 1;
    }

    fscanf(file, "%d %d", &nr, &nc);

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);

    findBlackRectangles(matrix, nr, nc);

    return 0;
}

void findBlackRectangles(int matrix[MAX_SIZE][MAX_SIZE], int nr, int nc) {
    bool visited[MAX_SIZE][MAX_SIZE] = {false};
    Rectangle max_height = {0, 0, 0, 0, 0};
    Rectangle max_width = {0, 0, 0, 0, 0,};
    Rectangle max_area = {0, 0, 0, 0, 0};

    for (int i = 0; i<nr; i++) {
        for (int j = 0; j<nc; j++) {
            if (matrix[i][j] == 1 && !visited[i][j]) {
                Rectangle current = {i,j,0,0,0};
                exploreRectangle(matrix,nr,nc,i,j,visited,&current);

                if (current.height > max_area.height) {
                    max_height = current;
                }

                if (current.area > max_area.area) {
                    max_area = current;
                }

                if (current.width > max_width.width) {
                    max_width = current;
                }
            }
        }
    }

    printf("Max-height region: upper left corner=(%d%d), height=%d, area=%d \n", max_height.row, max_height.col, max_height.height, max_height.area);
    printf("Max-width region: upper left corner=(%d%d), height=%d. width=%d area=%d \n",max_width.row, max_width.col, max_width.height, max_width.width, max_width.area);
    printf("Max-area region: upper left corner=(%d%d), height=%d, width=%d, area=%d \n", max_area.row, max_area.col, max_area.height, max_area.width, max_area.area);
}

void exploreRectangle(int matrix[MAX_SIZE][MAX_SIZE], int nr, int nc, int row, int col, bool visited[MAX_SIZE][MAX_SIZE], Rectangle *rect) {
    if (row < 0 || row >= nr || col < 0 || col >= nc || matrix[row][col] == 0) {
        return;
    }
    visited[row][col] = true;
    int top = row, bottom = row;
    int left = col, right = col;

    while (top >= 0 && matrix[top][col] == 1 && !visited[top][col]) {
        visited[top][col] = true;
        top--;
    }
    top++;

    while (bottom < nr && matrix[bottom][col] == 1 && !visited[bottom][col]) {
        visited[bottom][col] = true;
        bottom++;
    }
    bottom--;

    while (left >= 0 && matrix[row][left] == 1 && !visited[row][left]) {
        visited[row][left] = true;
        left--;
    }
    left++;

    while (right < nc && matrix[row][right] == 1 && !visited[row][right]) {
        visited[row][right] = true;
        right++;
    }
    right--;

    bool isRectangle = true;
    for (int i = top; i <= bottom && isRectangle; i++) {
        for (int j = left; j <= right && isRectangle; j++) {
            if (matrix[i][j] !=1) {
                isRectangle = false;
            }
        }
    }

    if (isRectangle) {
        for (int i = top; i <= bottom; i++) {
            for (int j = left; j <= right; j++) {
                visited[i][j] = true;
            }
        }
        rect->row = row;
        rect->col = col;
        rect->height = bottom - top + 1;
        rect->width = right - left + 1;
        rect->area = rect->height * rect->width;
    }
}
