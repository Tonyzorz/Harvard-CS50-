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
    //encipher O
        //for each alphabetic character, determine what letter it maps to O
        //preserve case O
        //leave non-alphabetic characters as-is O
    //print ciphertext O

    //validates key's length and invalid keys
    if(!(argc > 1 && argc < 3)){
        printf("Usage: ./substitution key\n");
        return 1;
    } else if(!(validate_key(argv))) return 1;

    //get plaintext
    char *t = get_string("plaintext: ");

    //encipher & print ciphertext
    printf("ciphertext: %s\n", encipher(t, argv));
}

bool validate_key(char *argv[]){
    //validate key
        //check key length
        //check for non-alphabetic characters
        //check for repeated characters(case-insensitive)
    char alphabet[] = {'A','B','C','D','E','F','G','H',
                    'I','J','K','L','M','N','O','P',
                     'Q','R','S','T','U','V','W','X','Y','Z'};

    //sets checkRepeat to all false;
    bool checkRepeat[strlen(argv[1])];
    for(int i = 0, n = strlen(argv[1]); i < n; i++){
        checkRepeat[i] = false;
    }

    //checks for key's length
    if(strlen(argv[1]) != 26){
        printf("Key must contain 26 characters.\n");
        return 0;
    }

    //checks for repeated value or incorrect value
    for(int i = 0, n = strlen(argv[1]); i < n; i++){
        if((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z')){
            for(int j = 0, m = strlen(alphabet); j < m; j++){
                if(argv[1][i] == alphabet[j] || argv[1][i] - ('a' - 'A') == alphabet[j]){

                    if(!checkRepeat[j]) {
                        checkRepeat[j] = true;
                        printf("it entered here on %i\n", j);
                        break;
                    }else if (checkRepeat[j]){
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

    //converts all lower case to upper case
    for(int i = 0, n = strlen(argv[1]); i < n; i++){
        if(argv[1][i] >= 'a') argv[1][i] -= ('a' - 'A');
    }

    return 1;

}

char *encipher(char *t, char *argv[]){
    //encipher
        //for each alphabetic character, determine what letter it maps to
        //preserve case
        //leave non-alphabetic characters as-is

    //stores inputted letter placement from the alphabet
    int a = strlen(t);
    int numbers[a];
    int upperLowerDifference = 'a' - 'A';

    //alphabet array to find out letter placement
    char alphabet[] = {'A','B','C','D','E','F','G','H',
                        'I','J','K','L','M','N','O','P',
                         'Q','R','S','T','U','V','W','X','Y','Z'};

    //stores letter placement into numbers array
    for(int i = 0; i < a; i++){
        for(int j = 0, z = strlen(alphabet); j < z; j++){
            if(t[i] == alphabet[j]) {
                numbers[i] = j;
                break;
            }else if(t[i] == alphabet[j] + upperLowerDifference){
                numbers[i] = j + upperLowerDifference;
                break;
            }
        }
    }

    //replaces plaintext into enciphered text
    for(int i = 0; i < a; i++){
        if((t[i] >= 'a' && t[i] <= 'z') || (t[i] >= 'A' && t[i] <= 'Z')){
            if(numbers[i] >= upperLowerDifference ) t[i] = argv[1][numbers[i] - upperLowerDifference] + upperLowerDifference;
            else t[i] = argv[1][numbers[i]];
        }
    }

    return t;
}