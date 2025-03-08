#include <stdio.h>
#include <math.h>

// Function to compute the area of a square given its side
float square_area_side(int side) {
    return (float)(side * side);
}

// Function to compute the area of a square given its diagonal
float square_area_diagonal(int diagonal) {
    return (float)((diagonal * diagonal) / 2.0);
}

// Function to compute the area of a circle given its radius
float circle_area_radius(int radius) {
    return (float)(M_PI * radius * radius);
}

// Function to compute the area of a circle given its diameter
float circle_area_diameter(int diameter) {
    return (float)(M_PI * (diameter / 2.0) * (diameter / 2.0));
}

int main() {
    char shape, type;
    int value;
    float area;

    // Prompt the user for input
    printf("Enter the shape and type of input (e.g., Q D10, I R5): ");
    scanf(" %c %c%d", &shape, &type, &value);

    // Check if the shape is a square (Q) or a circle (I)
    if (shape == 'Q' || shape == 'q') {
        // Compute the area of the square
        if (type == 'S' || type == 's') {
            area = square_area_side(value);
            printf("The area of the square with side %d is %.1f\n", value, area);
        } else if (type == 'D' || type == 'd') {
            area = square_area_diagonal(value);
            printf("The area of the square with diagonal %d is %.1f\n", value, area);
        } else {
            printf("Invalid input for square. Use S for side or D for diagonal.\n");
        }
    } else if (shape == 'I' || shape == 'i') {
        // Compute the area of the circle
        if (type == 'R' || type == 'r') {
            area = circle_area_radius(value);
            printf("The area of the circle with radius %d is %.1f\n", value, area);
        } else if (type == 'D' || type == 'd') {
            area = circle_area_diameter(value);
            printf("The area of the circle with diameter %d is %.1f\n", value, area);
        } else {
            printf("Invalid input for circle. Use R for radius or D for diameter.\n");
        }
    } else {
        printf("Invalid shape. Use Q for square or I for circle.\n");
    }

    return 0;
}