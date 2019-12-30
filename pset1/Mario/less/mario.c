#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int stairs = get_int("Height: ");
    while(!(stairs >= 1 && stairs <= 8)) stairs = get_int("Height: ");
    for(int i = 0; i < stairs; i++){
        for(int j = stairs; j > i + 1; j--){
            printf(" ");
        }
        
        for(int j = 0; j <= i; j++){
            printf("#");
        }
        printf("\n");
    }
}
