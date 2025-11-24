#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 12
#define COLS 24

/* Declaration of the asm function using your cdecl macros if you have them.
   If you use Paul Carter's cdecl.h, replace these with PRE_CDECL / POST_CDECL macros.
   For clarity here, I'll declare the plain extern (C side) you can adapt: */

int PRE_CDECL count_neighbors(int *grid, int rows, int cols, int r, int c) POST_CDECL;

/* Helpers */
void print_grid(int *g, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            putchar(g[r * cols + c] ? 'O' : '.');
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

    static int gridA[ROWS * COLS];
    static int gridB[ROWS * COLS];
    //buffer grid     

    int *cur = gridA;
    int *next = gridB;
    buffer 

    /* Initialize with a random sparse pattern */
    for (int i = 0; i < ROWS * COLS; ++i) cur[i] = (rand() % 5 == 0) ? 1 : 0;
    copy grid A to grid b

    for (int gen = 0; gen < 200; ++gen) {
        system("cls"); /* use "clear" on Unix; on Windows "cls" */
        printf("Generation %d\n", gen);
        print_grid(cur, ROWS, COLS);
        step_once(cur, next, ROWS, COLS);
        /* swap */
        int *tmp = cur; cur = next; next = tmp;
        /* wait for key or small delay */
        /* Uncomment one of these depending on your preference: */
        // Sleep(100); // Windows (include <windows.h>)
        // usleep(100000); // POSIX (include <unistd.h>)
        /* Or step on key press: */
        // getchar();
    }

    return 0;
}
