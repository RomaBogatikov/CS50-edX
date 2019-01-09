#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image");
        return 1;
    }

    //remember filename
    char *infile = argv[1];

    //open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //create a buffer to read 512 bytes from input file into
    unsigned char buffer[512];

    //initialize a flag to show that we have already found a new JPEG and set it to 0 (false)
    int flag = 0;
    int counter = 0;

    //make a new JPEG (format '002.jpg', put n instead of 2)
    char filename[8];
    sprintf(filename, "%03i.jpg", counter);

    //open a new file to write an image into
    FILE *img = fopen(filename, "w");

    //read 512 bytes from input file into a buffer
    //repeat until end of file
    while (fread(buffer, 512, 1, inptr))
    {
        //start of a new JPEG?
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            //if we are at the start of a new JPEG
            //check if we have already found a new JPEG
            //if yes
            if (flag)
            {
                counter++;
                //close the previous file
                fclose(img);

                //make a new JPEG (format '002.jpg', put n instead of 2)
                sprintf(filename, "%03i.jpg", counter);

                //open new file
                img = fopen(filename, "w");
            }
            //if no, start a very first JPEG
            else
            {
                flag = 1;
            }
        }
        //if we are not at a start of a new JPEG


        //have we already found a JPEG or not
        //if yes
        if (flag)
        {
            //those 512 bytes belong to the currently opened file
            //write a found image into a file img
            fwrite(buffer, 1, 512, img);
        }
        //if not
        //discard 512 bytes and go to the start of our loop

    };

    fclose(inptr);
    fclose(img);
    return 0;

}
