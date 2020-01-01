#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *encipher(char *t, char *argv[]);
bool validate_key(char *argv[]);

int main(int argc, char *argv[]){

    //Get key O
    //validate key O
        //check key length O
        //chekc for non-alphabetic characters O
        //check for repeated characters(case-insensitive) O
    //get plaintext O
    //encipher
        //for each alphabetic character, determine what letter it maps to
        //preserve case
        //leave non-alphabetic characters as-is
    //print ciphertext

    //validates key's length and invalid keys
    if(!(argc > 1 && argc < 3)){
        printf("Usage: ./substitution key");
        return 1;
    } else if(!(validate_key(argv))) return 1;

    char *t = get_string("plaintext: ");
    /*if(t[0] >= 'A' && t[0] <= 'Z'){
        printf("ciphertext: %s\n", plain_number(t, argv));
        return 0;
    } else {
        char *ciphertext = plain_number(t, argv);
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }*/


}

bool validate_key(char *argv[]){
    //validate key
        //check key length
        //check for non-alphabetic characters
        //check for repeated characters(case-insensitive)
    char alphabet[] = {'A','B','C','D','E','F','G','H',
                    'I','J','K','L','M','N','O','P',
                     'Q','R','S','T','U','V','W','X','Y','Z'};

    bool checkRepeat[strlen(argv[1])];
    if(strlen(argv[1]) != 26){
        printf("Key must contain 26 characters.\n");
        return 0;
    }

    for(int i = 0, n = strlen(argv[1]); i < n; i++){
        if((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z')){
            for(int j = 0, m = strlen(alphabet); j < m; j++){
                if(argv[1][i] == alphabet[j] || argv[1][i] - ('a' - 'A') == alphabet[j]){

                    if(!checkRepeat[j]) checkRepeat[j] = true;
                    else if (checkRepeat[j]){
                        printf("Key must not contain repeated characters.\n");
                        return 0;
                    }
                }
            }
        } else {
            printf("Key must only contain alphabetic characters.\n");
            return 0;
        }
    }

    return 1;

}

char *plain_number(char *t, char *argv[]){
    //encipher
        //for each alphabetic character, determine what letter it maps to
        //preserve case
        //leave non-alphabetic characters as-is

    //stores inputted letter placement from the alphabet
    int a = strlen(t);
    int numbers[a];

    //alphabet array to find out letter placement
    char alphabet[] = {'A','B','C','D','E','F','G','H',
                        'I','J','K','L','M','N','O','P',
                         'Q','R','S','T','U','V','W','X','Y','Z'};

    //stores letter placement into numbers array
    for(int i = 0; i < a; i++){
        for(int j = 0, z = strlen(alphabet); j < z; j++){
            if(t[i] == alphabet[j]) numbers[i] = j;
        }
    }

    //ciphertext
    char *ciphertext = malloc((strlen(t)) * sizeof(char));

    //stores ciphertext values for argv placement of a numbers
    for(int i = 0; i < a; i++){
        ciphertext[i] = argv[1][numbers[i]];
    }
    return ciphertext;
}
