#include <stdio.h>
#include <string.h>

typedef struct ModalCharacter {
    char character;
    int times;
} modal_character;

void remove_spaces(char *str) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char input[100];
    int unique = 0;
    int chars = 0;


    printf("Enter a sentence: ");
    fgets(input, sizeof(input), stdin);             // reads until newline
    input[strcspn(input, "\n")] = '\0';             // remove newline character
    //printf("before removing space: %s\n", input);
    remove_spaces(input);
    //printf("Result: %s\n", input);

    modal_character map[100] = {0};                      // map to 0-93; every character to '\0' and every times to 0
    // printf("char is: %c", map[0].character);
    // printf("times is: %d", map[0].times);


    
    //ibutang ang characters sa map and gina count at the same time

    for (int i = 0; input[i] != '\0'; i++){
        char current_char = input[i];
        int hash_index = (int) current_char - 33;   //33-126 ang ascii sng symbols
        if(map[hash_index].times == 0){
            map[hash_index].character = input[i];
            map[hash_index].times++;
            unique++;
            chars++;
        }else{
            map[hash_index].times++;
            chars++;
        }
    }

    char modal_chars[100];
    int modal_freq = 0;     // frequency sng mode
    int modal_count = 0;    // pila kabilog ang mode
    
    //count dnay ang freq sng mode
    for (int i = 0; i < 94; i++){                              // map to 0-93;
        if(map[i].times > modal_freq){
            modal_freq = map[i].times;
        }
    }
    //store characters nga ang times == modal_freq
    for (int i = 0; i < 94; i++) {
        if (map[i].times == modal_freq && modal_freq > 0) {
            modal_chars[modal_count++] = map[i].character;
        }
    }

    printf("Modal character(s): ");
    for (int i = 0; i < modal_count; i++) {
        printf("%c ", modal_chars[i]);
    }
    printf("\nHighest frequency: %d\n", modal_freq);




    for (int i = 0; i < 94; i++){                              // map to 0-93;
        if(map[i].times > 0){
            printf("Character: %c appeared %d times\n", map[i].character, map[i].times);
        }
    }

    printf("Total unique characters analyzed: %d\n", unique);
    printf("Total characters analyzed: %d", chars);

    
    return 0;
}


 















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


