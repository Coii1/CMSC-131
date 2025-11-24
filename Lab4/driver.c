#include "cdecl.h"
#include <stdio.h>
#include <windows.h>
#define SIZE 10 // assuming square grid
#define MAX_GEN 20

int PRE_CDECL count_neighbors(int *grid, int size, int r, int c) POST_CDECL;
int PRE_CDECL copy_grid(int *dest, int *src, int size) POST_CDECL;

void print_grid(int *g, int size) {
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            putchar(g[r * size + c] ? '#' : '-');
            putchar(' ');
        }
        putchar('\n');
    }
}

// void copy_grid(int *dest, int *src, int size) {
//     for (int i = 0; i < size*size; i++)
//         dest[i] = src[i];
// }

// how do I implement this in assembly?
void next_gen(int *main_grid, int *buffer, int size)
{
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            int alive = main_grid[r * size + c] ? 1 : 0;
            int n = count_neighbors(main_grid, size, r, c); // ASM call
            int newcell = 0;
			
            if (alive) {
				if (n == 2 || n == 3) newcell = 1;
            } else {
				if (n == 3) newcell = 1;
            }
			
            buffer[r * size + c] = newcell;
        }
    }
    //copy buffer to main_grid
    copy_grid(main_grid, buffer, size);
}

int main(){
	int grid_A[SIZE][SIZE] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int grid_B[SIZE][SIZE] = {0}; 			//same sa taas
    int buffer_grid[SIZE][SIZE] = {0};

    //copy tort to hare

	int *tort = (int*)grid_A; // cast (2D &arr)        int (*)[size] into int*
	int *hare = (int*)grid_B;
    int *buffer = (int*)buffer_grid;


	//game loop
	for (int gen = 0; gen < MAX_GEN; ++gen) {
		//system("cls");
		printf("Generation %d\n", gen);

		print_grid(tort, SIZE);
		printf("\n-----------------------\n\n"); // separator

		next_gen(tort, buffer, SIZE);
        // next_gen(hare, buffer, SIZE);
        // next_gen(hare, buffer, SIZE);    // hare moves twice
		Sleep(500);
	}
}






















// int count_neighbors(int *grid, int size, int r, int c){
// 	int sum = 0;

// 	// Loop over all neighbor offsets: dr = -1..1, dc = -1..1
// 	for (int dr = -1; dr <= 1; dr++) {
// 		for (int dc = -1; dc <= 1; dc++) {

// 			// Skip the cell itself
// 			if (dr == 0 && dc == 0) continue;

// 			int nr = r + dr; // neighbor row
// 			int nc = c + dc; // neighbor column

// 			// Skip out-of-bounds neighbors
// 			if (nr < 0 || nr >= size) continue;
// 			if (nc < 0 || nc >= size) continue;
			

// 			// Convert 2D coordinates to 1D index
// 			int index = nr * size + nc;

// 			// Add neighbor value to sum
// 			sum += grid[index];
// 		}
// 	}

// 	return sum;
// }

	