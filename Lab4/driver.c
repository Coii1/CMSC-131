#include "cdecl.h"
#include <stdio.h>
#include <windows.h>
#define SIZE 10 // assuming square grid
#define MAX_GEN 20

int PRE_CDECL count_neighbors(int *grid, int size, int r, int c) POST_CDECL;

void print_grid(int *g, int size) {
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            putchar(g[r * size + c] ? '#' : '-');
            putchar(' ');
        }
        putchar('\n');
    }
}
// how do I implement this in assembly?
void next_gen(int *cur, int *next, int size)
{
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            int alive = cur[r * size + c] ? 1 : 0;
            int n = count_neighbors(cur, size, r, c); // ASM call
            int newcell = 0;
			
            if (alive) {
				if (n == 2 || n == 3) newcell = 1;
            } else {
				if (n == 3) newcell = 1;
            }
			
            next[r * size + c] = newcell;
        }
    }
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

	int *cur; //= (int*)grid_A; // cast (2D &arr)        int (*)[size] into int*
	int *next; //= (int*)grid_B;

	//game loop
	for (int gen = 0; gen < MAX_GEN; ++gen) {
		//system("cls");
		printf("Generation %d\n", gen);

		if (gen % 2 == 0) {					// para indi nako mag swap
            cur = (int*)grid_A; 
            next = (int*)grid_B;
        } else {
            cur = (int*)grid_B;
            next = (int*)grid_A;
        }
		
		print_grid(cur, SIZE);
		printf("\n-----------------------\n\n"); // separator
		next_gen(cur, next, SIZE);
		//Sleep(500);
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

	