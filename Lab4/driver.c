#include "cdecl.h"
#include <stdio.h>
#include <time.h>
#include <windows.h>
#define HEIGHT 10
#define WIDTH 10
#define SIZE HEIGHT*WIDTH
#define MAX_GEN 20

extern int count_neighbors(int grid[HEIGHT][WIDTH], int height, int width, int r, int c);
extern int copy_grid(int dest[HEIGHT][WIDTH], int src[HEIGHT][WIDTH], int height, int width);
extern int check_stability(int tort[HEIGHT][WIDTH], int hare[HEIGHT][WIDTH], int height, int width);

void print_grid(int g[HEIGHT][WIDTH], int height, int width) {
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            putchar(g[r][c] ? '#' : '-');
            putchar(' ');
        }
        putchar('\n');
    }
}

// how do I implement this in assembly?
void next_gen(int main_grid[HEIGHT][WIDTH], int height, int width)
{
    int buffer_grid[HEIGHT][WIDTH] = {0};
    
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            int alive = main_grid[r][c] ? 1 : 0;
            int n = count_neighbors(main_grid, height, width, r, c); // ASM call
            int newcell = 0;
			
            if (alive) {
				if (n == 2 || n == 3) newcell = 1;
            } else {
				if (n == 3) newcell = 1;
            }
			
            buffer_grid[r][c] = newcell;
        }
    }
    //copy buffer to main_grid
    copy_grid(main_grid, buffer_grid, height, width);
}


// Returns: 0 = not homogeneous, 1 = all dead, 2 = all alive
int check_homogeneity(int grid[HEIGHT][WIDTH], int height, int width) {
    int first = grid[0][0];
    for(int r = 0; r < height; r++) {
        for(int c = 0; c < width; c++) {
            if(grid[r][c] != first) {
                return 0;  // not homogeneous
            }
        }
    }
    // All cells same as first
    return (first == 0) ? 1 : 2;  // 1=all dead, 2=all alive
}

void print_cycle(int tort[HEIGHT][WIDTH], int hare[HEIGHT][WIDTH], int height, int width, int *gen){
    do {
        printf("Generation %d\n", *gen);
		print_grid(tort, height, width);
		printf("\n-----------------------\n\n"); // separator
        next_gen(tort, height, width);
        Sleep(300);
        (*gen)++;
    }while (!check_stability(tort, hare, height, width));  
    
}

int main(){
    srand((unsigned)time(NULL));
    int grid_A[HEIGHT][WIDTH] ; 			//initial grid
    int grid_B[HEIGHT][WIDTH] ; 			//same sa taas

    /* Initialize with a random sparse pattern */
    for (int r = 0; r < HEIGHT; ++r) {
        for (int c = 0; c < WIDTH; ++c) {
            grid_A[r][c] = (rand() % 5 == 0) ? 1 : 0;
        }
    }

    
    copy_grid(grid_B, grid_A, HEIGHT, WIDTH); // hare starts same as tort

    int stable = 0;
    int gen = 1;
    int homogenous = 0;
    //print_grid(grid_A, HEIGHT, WIDTH);
    int *g = &gen;
    
	//game loop
	while(!stable) {
        //system("cls");
        printf("Generation %d\n", gen);
		print_grid(grid_A, HEIGHT, WIDTH);
		printf("\n-----------------------\n\n"); // separator
        
		next_gen(grid_A, HEIGHT, WIDTH);
        next_gen(grid_B, HEIGHT, WIDTH);
        next_gen(grid_B, HEIGHT, WIDTH);    // hare moves twice
        stable = check_stability(grid_A, grid_B, HEIGHT, WIDTH);
        homogenous = check_homogeneity(grid_A, HEIGHT, WIDTH);
		Sleep(300);
        gen++;
        
        
        if(stable) {
            printf("Pattern stabilized or entered a cycle at generation %d\n\n", gen);
            print_cycle(grid_A, grid_B, HEIGHT, WIDTH, g);
            print_cycle(grid_A, grid_B, HEIGHT, WIDTH, g);
            printf("----Cycle Continues----\n");
            printf("\n-----------------------\n\n"); // separator
            
            
        }
        if(homogenous == 1){
            printf("All cells are dead at generation %d\n", gen);
        }else if(homogenous == 2){
            printf("All cells are alive at generation %d\n", gen);
        }
        
	}
}



















// int check_stability(int tort[HEIGHT][WIDTH], int hare[HEIGHT][WIDTH], int height, int width){
//     int stable = 1;
//     for(int r = 0; r < height; r++){
//         for(int c = 0; c < width; c++){
//             if(tort[r][c] != hare[r][c]){
//                 stable = 0;
//                 break;
//             }
//         }
//         if(!stable) break;
//     }
//     return stable;
// }



// int count_neighbors(int grid[HEIGHT][WIDTH], int height, int width, int r, int c){
    // 	int sum = 0;
    
    // 	// Loop over all neighbor offsets: dr = -1..1, dc = -1..1
    // 	for (int dr = -1; dr <= 1; dr++) {
        // 		for (int dc = -1; dc <= 1; dc++) {
            
// 			// Skip the cell itself
// 			if (dr == 0 && dc == 0) continue;

// 			int nr = r + dr; // neighbor row
// 			int nc = c + dc; // neighbor column

// 			// Skip out-of-bounds neighbors
// 			if (nr < 0 || nr >= height) continue;
// 			if (nc < 0 || nc >= width) continue;
			

// 			// Access grid using 2D notation
// 			sum += grid[nr][nc];
// 		}
// 	}

// 	return sum;
// }


// void copy_grid(int dest[HEIGHT][WIDTH], int src[HEIGHT][WIDTH], int height, int width) {
//     for (int r = 0; r < height; r++)
//         for (int c = 0; c < width; c++)
//             dest[r][c] = src[r][c];
// }







 // //Cross - Box
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

        // //  1-2-3
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        // {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}








    // cross box
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    //glider
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    // {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}


    // blinker
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}


    // stable at gen 37
    // {0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
    // {1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    // {1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
    // {0, 1, 0, 1, 0, 0, 1, 0, 0, 0},
    // {0, 1, 0, 0, 0, 0, 1, 0, 1, 1},
    // {0, 0, 1, 1, 1, 0, 1, 0, 1, 1},
    // {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}


    // 1-2-3
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    // {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}


        // {0,0,1,1,0,0,0,0,0,0},
        // {0,1,0,0,1,0,0,0,0,0},
        // {0,1,0,0,0,1,0,0,0,0},
        // {0,1,0,1,1,0,0,0,0,0},
        // {0,0,0,0,1,0,0,0,0,0},
        // {0,0,0,0,1,0,1,1,1,0},
        // {0,0,0,0,0,0,0,0,1,0},
        // {0,0,0,0,0,0,0,0,0,0},
        // {0,0,0,0,0,0,0,1,0,0},
        // {0,0,0,0,0,0,0,0,0,0}