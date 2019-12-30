#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void){
    float change = get_float("Change owed: ");
    while(!(change >= 0.00)) change = get_float("Change owed: ");
    
    int coins = round(change * 100);
    
    int count = 0;
    while(coins != 0){
        if(coins >= 25){
            int temp = coins/25;
            coins = coins - (temp * 25);
            count += temp;
        }
        if(coins >= 10){
            int temp = coins/10;
            coins = coins - (temp * 10);
            count += temp;
        }
        if(coins >= 5){
            int temp = coins/5;
            coins = coins - (temp * 5);
            count += temp;
        }
        count += coins;
        coins = 0;
    }
    
    printf("%i\n", count);
}
