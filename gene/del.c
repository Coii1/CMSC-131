void simulate_game_of_life(void) {
    int generation = 0;
    initialize_grid();
    
    // Display initial generation (generation 0)
    int live_count = count_live_cells();
    display_grid(generation, live_count);
    
    // Sleep for 1 second before starting simulation
    sleep_ms(1000);
    
    // Copy initial grid to prev_grid 
    copy_to_prev();
    // Buffer to hold generation n-2 for period-2 detection
    char prev2[GRID_SIZE];
    // Initialize prev2 with contents of prev_grid so first comparison is meaningful
    copy_buffer(prev2, prev_grid, GRID_SIZE);
    
    // Main simulation loop
    while (1) {
        // Check if generation limit reached
        if (generation >= GEN_LIMIT) {
            break;
        }
        
        // Increment generation counter
        generation++;

        calculate_next_gen();
            
        // Copy next_grid to grid
        copy_next_to_current();
        
        // Count live cells in current generation
        live_count = count_live_cells();
        
        // Display current generation
        display_grid(generation, live_count);
        
        // Sleep between generations for visibility
        sleep_ms(500);
        
        // Check if grid is stable (calls assembly function)
        if (check_stability()) {
            print_stable_message(generation);
            break;
        }
        // Check for period-2 oscillation: current equals generation n-2
        if (buffers_equal(grid, prev2, GRID_SIZE)) {
            print_oscillation_message(generation);
            break;
        }
        
        // Check if grid is homogeneous (calls assembly function)
        if (check_homogeneity()) {
            print_homogeneous_message(generation);
            break;
        }
        
        // Save previous generation into prev2, then copy current to prev_grid
        // Save previous generation into prev2 using helper, then copy current to prev_grid
        copy_buffer(prev2, prev_grid, GRID_SIZE);
        // Copy current grid to prev_grid for next iteration (calls assembly)
        copy_to_prev();
    }
    
    // Display final statistics
    live_count = count_live_cells();
    print_final_stats(generation, live_count);
}