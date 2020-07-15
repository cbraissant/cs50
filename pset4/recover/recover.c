#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define FAT_B 512

int main(int argc, char *argv[])
{
    /*
            1. Open file
            2. Look for beginning of JPEG
            3. Open new JPEG file
            4. Write 512 bytes until a new JPEG is found
            5. Stop at the end of the file
    */


    /*
            fread(data, size, number, inptr);

            - data: pointer to where to store data (buffer)
            - size: size of each element to read
            - number: number of elements to read
            - inptr: FILE * to read from

            - returns number of items of size 'size' that were read
            - end of file when number returns is less than number input

    */

    /*
            fwrite(data, size, number, outptr);

            - data: pointer to bytes that will be written
            - size: size of each element to write
            - number: number of elements to write
            - outptr: FILE * to write to
    */


    // Check for invalid usage
    if (argc != 2)
    {
        printf("\033[1;31m");   // set the text to red
        printf("Usage: ./recover filename\n");
        printf("\033[0m"); // reset the color
        return 1;
    }




    // Open the file and check for error
    FILE *ptr_file = fopen(argv[1], "r");
    if (ptr_file == NULL)
    {
        printf("\033[1;31m");   // set the text to red
        printf("\u2715 Error opening the file\n");
        printf("\033[0m"); // reset the color
        exit(1);
    }
    else
    {
        printf("\033[0;32m");   // set the text to green
        printf("\u2713 File opened successfully\n");
        printf("\033[0m"); // reset the color
    }




    // allocate memory to hold a block of 512B
    BYTE buffer[FAT_B];

    // Create variables
    FILE *jpeg_file;
    int is_writing = 0;
    int img_counter = 0;

    // string for the name of the files
    // 8 characters: "123.jpg" and the end character "\0"
    char jpeg_name[8];

    // read the file until the end of the file
    while (fread(buffer, sizeof(buffer), 1, ptr_file) == 1)
    {

        // check for the JPEG header
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {

            // check if the file is already in write mode
            if (is_writing)
            {
                // close the file
                fclose(jpeg_file);

                // increment counter
                img_counter++;
            }



            // create a new jpeg file
            sprintf(jpeg_name, "%03d.jpg", img_counter);
            printf("file %s created\n", jpeg_name);

            // open the jpeg file for writing
            jpeg_file = fopen(jpeg_name, "w");

            // write to the file
            fwrite(buffer, sizeof(buffer), 1, jpeg_file);

            // set the writing flag
            is_writing = 1;

        }
        else
        {
            // continue writing
            if (is_writing == 1)
            {
                // write to the file
                fwrite(buffer, sizeof(buffer), 1, jpeg_file);
            }
        }



    }

    // close all the files
    fclose(jpeg_file);
    fclose(ptr_file);

    return 0;
}
