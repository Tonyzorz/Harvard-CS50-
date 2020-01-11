#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 512

int main(int argc, char *argv[])
{
    //open memory card
    //look for beginning of a jpeg
    //open a new jpeg file
    //write 512 bytes until a new jpeg found
    //repeat until reaching the end of the file
    if(argc != 2){
        printf("Usage ./recover image\n");
        return 1;
    }

    //open memory card
    char *memory = argv[1];
    FILE *file = fopen(memory, "r");
    if(file == NULL){
        printf("Could not open file %s\n", memory);
        return 2;
    }

    unsigned char *buffer = malloc(SIZE);
    int jpgNum = 0;
    FILE *img;

    while(fread(buffer, SIZE, 1, file)){


        //if it is jpg
        if(buffer[0] == 0xff && buffer[1]  == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){

            //close previous jpg file if it exists
            if(jpgNum > 0) fclose(img);

            //create filename
            char filename[7];
            sprintf(filename, "%03i.jpg", jpgNum);

            //open new image file
            img = fopen(filename, "w");
            jpgNum ++;
        }

        if(img ) {
            fwrite(buffer, SIZE, 1, img);
        }

    }

    fclose(img);
    fclose(file);

    free(buffer);

}
