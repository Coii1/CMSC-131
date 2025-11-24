//#include "cdecl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ROWS 10
#define COLS 10
#define MAX_GEN 20

/* Declaration of the asm function using your cdecl macros if you have them.
   If you use Paul Carter's cdecl.h, replace these with PRE_CDECL / POST_CDECL macros.
   For clarity here, I'll declare the plain extern (C side) you can adapt: */

//int PRE_CDECL count_neighbors(int *grid, int rows, int cols, int r, int c) POST_CDECL;

/* Helpers */
#include <stdio.h>

int count_neighbors(int *grid, int rows, int cols, int r, int c) {
    int sum = 0;

    // Loop over all neighbor offsets: dr = -1..1, dc = -1..1
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {

            // Skip the cell itself
            if (dr == 0 && dc == 0) continue;

            int nr = r + dr; // neighbor row
            int nc = c + dc; // neighbor column

            // Skip out-of-bounds neighbors
            if (nr < 0 || nr >= rows) continue;
            if (nc < 0 || nc >= cols) continue;

            // Convert 2D coordinates to 1D index
            int index = nr * cols + nc;

            // Add neighbor value to sum
            sum += grid[index];
        }
    }

    return sum;
}


void print_grid(int *g, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            putchar(g[r * cols + c] ? '*' : '-');
            putchar(' ');
        }
        putchar('\n');
    }
}

/* Simple Conway rules performed in C using assembled neighbor counter */
void step_once(int *cur, int *next, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int alive = cur[r * cols + c] ? 1 : 0;
            int n = count_neighbors(cur, rows, cols, r, c); // ASM call
            int newcell = 0;
            if (alive) {
                if (n == 2 || n == 3) newcell = 1;
            } else {
                if (n == 3) newcell = 1;
            }
            next[r * cols + c] = newcell;
        }
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    // static int gridA[ROWS * COLS];
    // static int gridB[ROWS * COLS];

    int gridA[10][10] = {
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
    
	int gridB[10][10] = {0};

    int *cur; //= (int*)gridA;
    int *next; //= (int*)gridB;


    /* Initialize with a random sparse pattern */
    // for (int i = 0; i < ROWS * COLS; ++i) cur[i] = (rand() % 5 == 0) ? 1 : 0;

    for (int gen = 0; gen < MAX_GEN; ++gen) {
        //system("cls"); /* use "clear" on Unix; on Windows "cls" */
        printf("Generation %d\n", gen);
        // if (gen % 2 == 0) {
        //     cur = (int*)gridA;
        //     next = (int*)gridB;
        // } else {
        //     cur = (int*)gridB;
        //     next = (int*)gridA;
        // }
        print_grid(cur, ROWS, COLS);
        printf("\n-----------------------\n\n"); // separator
        step_once(cur, next, ROWS, COLS);
        /* swap */
        int *tmp = cur; cur = next; next = tmp;
        /* wait for key or small delay */
        /* Uncomment one of these depending on your preference: */
        //Sleep(1000); // Windows (include <windows.h>)
        //usleep(100000); // POSIX (include <unistd.h>)
        /* Or step on key press: */
        // getchar();
    }

    return 0;
}
