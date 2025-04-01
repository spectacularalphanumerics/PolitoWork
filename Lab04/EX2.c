#include <stdio.h>

#define maxN 100 // Adjust maxN as needed

void rotate(int v[], int n, int p, int dir) {
    if (n <= 0) return; // If the array is empty or invalid, do nothing

    // Normalize p to be within bounds (0 <= p < n)
    p = p % n;
    
    // If the direction is left (-1), we can treat it as a right rotation by adjusting p.
    if (dir == -1) {
        p = n - p;
    }
    
    // We need to reverse parts of the array to perform the rotation
    // Step 1: Reverse the whole array
    for (int i = 0; i < n / 2; i++) {
        int temp = v[i];
        v[i] = v[n - i - 1];
        v[n - i - 1] = temp;
    }
    
    // Step 2: Reverse the first p elements
    for (int i = 0; i < p / 2; i++) {
        int temp = v[i];
        v[i] = v[p - i - 1];
        v[p - i - 1] = temp;
    }
    
    // Step 3: Reverse the rest (n - p) elements
    for (int i = p; i < (n + p) / 2; i++) {
        int temp = v[i];
        v[i] = v[n - (i - p) - 1];
        v[n - (i - p) - 1] = temp;
    }
}

// Helper function to print an array (for testing purposes)
void print_array(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    int p = 2;
    int dir = 1;  // Rotate right

    printf("Original array:\n");
    print_array(arr, n);

    rotate(arr, n, p, dir);
    
    printf("Array after rotation:\n");
    print_array(arr, n);

    return 0;
}
