#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(char *text);
int count_words(char *text);
int count_sentences(char *text);
void grade(int index);

int main(void){
    char *text = get_string("Text: ");
    int l = count_letters(text);
    int s = count_sentences(text);
    int w = count_words(text);
    float letteravg = ((float)l/w * 100);
    float sentenceavg = ((float)s/w * 100);
    int index = round(0.0588 * letteravg  - 0.296 * sentenceavg - 15.8);

    grade(index);

}

int count_letters(char *text){
    int count = 0;
    for(int i = 0, n = strlen(text); i < n; i++){
        if(text[i] >= 'A' && text[i] <= 'z') count++;
    }
    return count;
}

int count_words(char *text){
    int count = 1;
    for(int i = 0, n = strlen(text); i < n; i++){
        if(text[i] == ' ' && text[i + 1] != ' ') count++;
    }
    return count;
}

int count_sentences(char *text){
    int count = 0;
    for(int i = 0, n = strlen(text); i < n; i++){
        if(text[i] == '.' || text[i] == '?' ||text[i] == '!'){
            count++;
        }
    }
    return count;
}

void grade(int index){
    if(index >= 1 && index <= 16) printf("Grade %i\n", index);
    else if(index > 16) printf("Grade 16+\n");
    else printf("Before Grade 1\n");
}
