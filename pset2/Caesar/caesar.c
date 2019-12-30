#import <cs50.h>
#import <stdio.h>
#import <string.h>
#import <stdlib.h>

int main(int argc, char *argv[]){
    int z;

    if(argc <= 1 || argc >= 3){
        printf("Usage: ./caesar key\n");
        return 1;
    } else if((z = atoi(argv[1])) == 0 ){
        printf("Usage: ./caesar key\n");
        return 1;
    }
    z = atoi(argv[1]);
    char *plaintext = get_string("plaintext: ");

    for(int i = 0, n = strlen(plaintext); i < n; i++){
        char letter = plaintext[i];
        //this prevents converting spaces and commas
        if(letter >= 'A'){
            int temp = z;
            //prevents inputs higher than 26
            while(temp > 26){
                    temp -= 26;
            }
            //for lower case that exceeds z
            if(letter + z > 'z'){
                if(letter + temp > 'z') {
                    temp -= ('z' - letter);
                    plaintext[i] = 'a' - 1 + temp;
                } else {
                    plaintext[i] += temp;
                }
            //for capital letters that exceeds z
            } else if (letter + z > 'Z' && letter < 'a'){
                if(letter + temp > 'Z') {
                    temp -= ('Z' - letter);
                    plaintext[i] = 'A' - 1 + temp;
                } else {
                    plaintext[i] += temp;
                }
            //if it is normal, just convert
            } else {
                plaintext[i] += z;
            }
        }

    }
    //print vowalla
    printf("ciphertext: %s\n", plaintext);
}
