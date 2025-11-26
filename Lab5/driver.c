#include "cdecl.h"
#include <stdio.h>
#include <string.h>

typedef struct ModalCharacter {
    char character;
    int times;
} modal_character;

void PRE_CDECL map_chars(char *input, modal_character *map, int *unique, int *chars) POST_CDECL;
//int PRE_CDECL get_modal_frequency(modal_character *map) POST_CDECL;
void PRE_CDECL get_modal_chars(modal_character *map, int modal_freq, char *modal_chars, int *modal_count) POST_CDECL;

void remove_spaces(char *str) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void get_input(char *buffer, int size) {
    printf("\n\nInput a string: ");
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    remove_spaces(buffer);
}

//count dnay ang freq sng mode
int get_modal_frequency(modal_character *map) {
    int modal_freq = 0;
    for (int i = 0; i < 94; i++){                                   // map to 0-93;
        if(map[i].times > modal_freq){
            modal_freq = map[i].times;
        }
    }
    return modal_freq;
}

//  //store characters nga ang times == modal_freq
// void get_modal_chars(modal_character *map, int modal_freq, char *modal_chars, int *modal_count){
    
//     *modal_count = 0;                                               // reset count
    
//     for (int i = 0; i < 94; i++) {
//         if (map[i].times == modal_freq && modal_freq > 0) {
//             modal_chars[(*modal_count)++] = map[i].character;
//         }
//     }
// }

void print_frequencies(modal_character *map){
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
    int unique = 0;
    int chars = 0;
    map_chars(input, map, &unique, &chars);                     //ibutang ang characters sa map and gina count at the same time

    int modal_freq = get_modal_frequency(map);                  // frequency sng mode
    char modal_chars[100];
    int modal_count = 0;                                        // pila kabilog ang mode
    get_modal_chars(map, modal_freq, modal_chars, &modal_count);

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





// void map_chars(char *input, modal_character *map, int *unique, int *chars){
//     for (int i = 0; input[i] != '\0'; i++){
//         char current_char = input[i];
//         int hash_index = (int) current_char - 33;                   //33-126 ang ascii sng symbols
        
//         if (hash_index < 0 || hash_index >= 94) {                   //0-94 lang ang valid range
//             continue;                                               // ignore characters outside the expected range
//         }
        
//         if(map[hash_index].times == 0){
//             map[hash_index].character = input[i];
//             (*unique)++;
            
//         }

//         map[hash_index].times++;
//         (*chars)++;
        
//     }
// }


 















    // modal_character modal_chars[100];
    // modal_chars[0].character = 'A';
    // modal_chars[0].times = 1;
    // modal_chars[1].character = 'A'+1;
    // modal_chars[1].times = 1;

    // printf("Character: %c appeared %d times\n", modal_chars[0].character, modal_chars[0].times);
    // printf("Character: %c appeared %d times\n", modal_chars[1].character, modal_chars[1].times);
   
   

    // char letter = 'a';
    // int value = (int) letter;
    // printf("Character: %c has ASCII value: %d\n", letter, value);

    // for (int i = 0; i < 256; i++) {
    //     printf("ASCII %3d : %c\n", i, (unsigned char)i);
    // }
    //33-126



//woudl it be better to pass pointers instead of initializing arrays in assembly?