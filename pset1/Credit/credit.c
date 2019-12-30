#include <cs50.h>
#include <stdio.h>

int main(void){
    long number = get_long("Number: ");
    char *answer = NULL;
    
    if((number/1000000000000 > 1 && (number/1000000000000) % 10 == 4) ||
      (number/1000000000000000 > 1 && (number/1000000000000000) % 10 == 4)) {
        
        answer = malloc(5 * sizeof(char));
        answer = "VISA";
    }
    else if((number/100000000000000) > 1 && 
            ((number/10000000000000) % 100 == 34 || (number/10000000000000) % 100 == 37)){
       
        answer = malloc(5 * sizeof(char));
        answer = "AMEX";
    } 
    else if((number/100000000000000) > 1 && 
            ((number/100000000000000) % 100 >= 51 && (number/100000000000000) % 100 <= 55)) {
        
        answer = malloc(10 * sizeof(char));
        answer = "MASTERCARD";
        printf("master?\n");
    } else {
        printf("INVALID\n");
        return 0;
    }
    
    int forSum = 0;
    for(long i = 10; i <= number; i *= 100){
        int divNum = ((number % (i * 10))/i) * 2;
        if(divNum >= 10){
            int temp = divNum % 10;
            divNum /= 10;
            forSum += temp + divNum;
        } else {
            forSum += divNum;
        }
        //printf("%i, %ld forSum, %i\n", forSum, i, divNum);
    }
    
    int restSum = 0;
    for(long i = 10; i <= number * 10; i *= 100){
        int restNum = (number % (i))/(i/10);
        restSum += restNum;
        //printf("%i, %ld restSum, %i\n", restSum, i, restNum);
    }
    if((forSum + restSum) % 10 == 0){
        printf("%s\n", answer);
    } else {
        printf("INVALID\n");
    }
    
    
    
    
}
