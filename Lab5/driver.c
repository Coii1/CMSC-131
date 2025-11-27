#include "cdecl.h"
#include <stdio.h>
#include <string.h>

typedef struct ModalCharacter {
    char character;
    int times;
} modal_character;

void PRE_CDECL map_chars(char input[], modal_character map[]) POST_CDECL;
int PRE_CDECL get_unique_count(modal_character map[]) POST_CDECL;
int PRE_CDECL get_total_chars(modal_character map[]) POST_CDECL;
int PRE_CDECL get_modal_chars(modal_character map[], int modal_freq, char modal_chars[]) POST_CDECL;

void get_input(char buffer[], int size) {
    printf("\n\nInput a string: ");
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

//count dnay ang freq sng mode
int get_modal_frequency(modal_character map[]) {
    int modal_freq = 0;
    for (int i = 0; i < 94; i++){                                   // map to 0-93;
        if(map[i].times > modal_freq){
            modal_freq = map[i].times;
        }
    }
    return modal_freq;
}

void print_frequencies(modal_character map[]){
    printf("Character Frequencies:\n");
    for (int i = 0; i < 94; i++){                              // map to 0-93;
        if(map[i].times > 0){
            printf("%c : %d \n", map[i].character, map[i].times);
        }
    }
}

int main() {
    
    char input[100];
    get_input(input, sizeof(input));

    
    modal_character map[100] = {0};                             // map to 0-93; every character to '\0' and every times to 0
    
    map_chars(input, map);                                      // put characters in map (skips spaces)
    int unique = get_unique_count(map);                         // count unique characters
    int chars = get_total_chars(map);                           // count total characters

    int modal_freq = get_modal_frequency(map);                  // frequency sng mode
    char modal_chars[100];
    int modal_count = get_modal_chars(map, modal_freq, modal_chars);

    print_frequencies(map);

    printf("Modal character(s) with frequency %d: \n", modal_freq);
    for (int i = 0; i < modal_count; i++) {
        printf("%c : %d\n", modal_chars[i], modal_freq);
    }
    
    printf("Total unique characters analyzed: %d\n", unique);
    printf("Total characters analyzed: %d\n", chars);
    printf("\nHighest frequency: %d\n", modal_freq);
    
    return 0;
}


// void map_chars(char input[], modal_character map[]){
//     for (int i = 0; input[i] != '\0'; i++){
//         char current_char = input[i];
        
//         // Skip spaces
//         if (current_char == ' ') {
//             continue;
//         }
        
//         int hash_index = (int) current_char - 33;                   //33-126 ang ascii sng symbols

//         if (hash_index < 0 || hash_index >= 94) {                   //0-94 lang ang valid range
//             continue;                                               // ignore characters outside the expected range
//         }
        
//         if(map[hash_index].times == 0){
//             map[hash_index].character = current_char;
//         }

//         map[hash_index].times++;
//     }
// }


// int get_unique_count(modal_character map[]) {
//     int unique = 0;
//     for (int i = 0; i < 94; i++) {
//         if (map[i].times > 0) {
//             unique++;
//         }
//     }
//     return unique;
// }


// int get_total_chars(modal_character map[]) {
//     int total = 0;
//     for (int i = 0; i < 94; i++) {
//         total += map[i].times;
//     }
//     return total;
// }


// int get_modal_chars(modal_character map[], int modal_freq, char modal_chars[]){
//     int modal_count = 0;
//     for (int i = 0; i < 94; i++) {
//         if (map[i].times == modal_freq && modal_freq > 0) {
//             modal_chars[modal_count++] = map[i].character;
//         }
//     }
//     return modal_count;
// }