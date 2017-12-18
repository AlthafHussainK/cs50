/*
* Recovers deleted JPG files from a memory card
*/

#include<stdio.h>
#include<stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usae: ./recover infile\n");
        return 1;
    }

    //remember filename
    char *infile = argv[1];

    //open the card
    FILE *image = fopen(infile, "r");

    if(image == NULL)
    {
        fprintf(stderr, "File could not open! %s", infile);
        return 2;
    }

    //char array to store the filenames
    char filename[8];
    BYTE buffer[512];

    //create a NULL file, ie. no JPG is found
    FILE *outfile = NULL;

    //no. of JPG files
    int count = 0;

    int flag = 1;
    //repeat until the end of the card
    while(flag == 1)
    {
        //check for the first 4 bytes to check JPEG sign
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //close the previous files, if any
            if(outfile != NULL)
            {
                fclose(outfile);
            }

            //making a new jpg
            sprintf(filename, "%03i.jpg", count);

            outfile = fopen(filename, "w");

            //error check
            if(outfile == NULL)
            {
                fprintf(stderr, "Error!\n");
                return 3;
            }

            //writing files
            fwrite(buffer, 512, 1, outfile);
            count++;
        }
        else if(outfile != NULL)
        {
            fwrite(buffer, 512, 1, outfile);
        }

        //check for EOF
        flag = fread(buffer, 512, 1, image);
    }

//close the remaining files
if(outfile != NULL)
    fclose(outfile);

fclose(image);

return 0;

}
