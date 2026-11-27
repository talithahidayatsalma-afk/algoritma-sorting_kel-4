#include <stdio.h>

int main() {
    int my_array[] = {25, 10, 31, 14, 22, 17, 80, 3};
    int n = sizeof(my_array) / sizeof(my_array[0]);
    int temp;

    // process of bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (my_array[j] > my_array[j + 1]) {
                // Swap the elements
                temp = my_array[j];
                my_array[j] = my_array[j + 1];
                my_array[j + 1] = temp;
            }
        }
    }

    // print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");
    return 0;
}