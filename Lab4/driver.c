#include "cdecl.h"
#include <stdio.h>
#include <windows.h>
#define HEIGHT 10
#define WIDTH 10
#define MAX_GEN 20

int PRE_CDECL count_neighbors(int *grid, int height, int width, int r, int c) POST_CDECL;
int PRE_CDECL copy_grid(int *dest, int *src, int height, int width) POST_CDECL;
int PRE_CDECL check_stability(int *tort, int *hare, int height, int width) POST_CDECL;

void print_grid(int *g, int height, int width) {
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            putchar(g[r * width + c] ? '#' : '-');
            putchar(' ');
        }
        putchar('\n');
    }
}

// how do I implement this in assembly?
void next_gen(int *main_grid, int height, int width)
{
    int buffer_grid[HEIGHT][WIDTH] = {0};
    int *buffer = (int*)buffer_grid;
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            int alive = main_grid[r * width + c] ? 1 : 0;
            int n = count_neighbors(main_grid, height, width, r, c); // ASM call
            int newcell = 0;
			
            if (alive) {
				if (n == 2 || n == 3) newcell = 1;
            } else {
				if (n == 3) newcell = 1;
            }
			
            buffer[r * width + c] = newcell;
        }
    }
    //copy buffer to main_grid
    copy_grid(main_grid, buffer, height, width);
}


// Returns: 0 = not homogeneous, 1 = all dead, 2 = all alive
int check_homogeneity(int *grid, int height, int width) {
    int first = grid[0];
    for(int i = 1; i < height*width; i++) {
        if(grid[i] != first) {
            return 0;  // not homogeneous
        }
    }
    // All cells same as first
    return (first == 0) ? 1 : 2;  // 1=all dead, 2=all alive
}

void print_cycle(int *tort, int *hare, int height, int width, int *gen){
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
    int grid_A[HEIGHT][WIDTH] = {
        //Cross - Box
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


    };
    int grid_B[HEIGHT][WIDTH] = {0}; 			//same sa taas
    

    //copy tort to hare
    
	int *tort = (int*)grid_A; // cast (2D &arr)        int (*)[width] into int*
	int *hare = (int*)grid_B;
    
    copy_grid(hare, tort, HEIGHT, WIDTH); // hare starts same as tort

    int stable = 0;
    int gen = 1;
    int homogenous = 0;
    //print_grid(tort, HEIGHT, WIDTH);
    int *g = &gen;
    
	//game loop
	while(!stable) {
        //system("cls");
        printf("Generation %d\n", gen);
		print_grid(tort, HEIGHT, WIDTH);
		printf("\n-----------------------\n\n"); // separator
        
		next_gen(tort, HEIGHT, WIDTH);
        next_gen(hare, HEIGHT, WIDTH);
        next_gen(hare, HEIGHT, WIDTH);    // hare moves twice
        stable = check_stability(tort, hare, HEIGHT, WIDTH);
        homogenous = check_homogeneity(tort, HEIGHT, WIDTH);
		Sleep(300);
        gen++;
        
        
        if(stable) {
            printf("Pattern stabilized or entered a cycle at generation %d\n\n", gen);
            print_cycle(tort, hare, HEIGHT, WIDTH, g);
            print_cycle(tort, hare, HEIGHT, WIDTH, g);
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



















// int check_stability(int *tort,int *hare, int height, int width){
//     int stable = 1;
//     for(int i = 0; i < height*width; i++){
//         if(tort[i] != hare[i]){
//             stable = 0;
//             break;
//         }
//     }
//     return stable;
// }



// int count_neighbors(int *grid, int height, int width, int r, int c){
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
			

// 			// Convert 2D coordinates to 1D index
// 			int index = nr * width + nc;

// 			// Add neighbor value to sum
// 			sum += grid[index];
// 		}
// 	}

// 	return sum;
// }


// void copy_grid(int *dest, int *src, int height, int width) {
//     for (int i = 0; i < height*width; i++)
//         dest[i] = src[i];
// }
















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