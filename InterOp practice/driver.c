#include "cdecl.h"
#include <stdio.h> //Do is still need this?

// Tell C: this function exists in assembly
int PRE_CDECL add_two_numbers(int a, int b) POST_CDECL;
//exppands to -> extern int _add_two_numbers(int a, int b);
int PRE_CDECL subtract_two_numbers(int a, int b) POST_CDECL;
int PRE_CDECL sum_array(int *arr, int len) POST_CDECL;
//PASSING A 2D GRID (int rows, int cols, int *grid)
int PRE_CDECL sum_grid(int *grid, int rows, int cols) POST_CDECL;
// type int* points to the first element of the 2D array and treats it as a 1D array




int main() {
    int x = 7;
    int y = 35; //does this push the values to the stack?,
    // YES it does this: 
    // push 35   ; second argument (b)
    // push 7    ; first argument (a)
    // call _add_two_numbers

    int result = add_two_numbers(x, y); // Inside your function, C expects the return value in EAX
    printf("Result from assembly add: %d\n", result);
    int sub_result = subtract_two_numbers(x, y); // Inside your function, C expects the return value in EAX
    printf("Result from assembly subtract: %d\n", sub_result);


    int nums[] = {10, 20, 30, 40};

    int sum_arr_result = sum_array(nums, 4);
    // push 4              ; length
    // push &nums[0]       ; pointer to first element
    // call _sum_array
    printf("Sum = %d\n", sum_arr_result);



    int grid[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int total = sum_grid((int*)grid, 3, 3);
    // We cast grid to (int*) because the assembly function expects a pointer to the first integer.
    // C passes:
    // pointer → [ebp + 8]
    // rows → [ebp + 12]
    // cols → [ebp + 16]

    printf("Sum of grid = %d\n", total);


    return 0;
}

