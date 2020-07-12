#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // variable declaration
    int height;

    do
    {
        // ask the user for the height
        height = get_int("Height: ");
    }
    while ((height < 1) || (height > 8));


    // display each line
    for (int line = 0; line < height; line++)
    {

        // display the first pyramid
        for (int j = 1; j <= height; j++)
        {
            // check which character to display
            if (j < (height - line))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        // display the space in between
        printf("  ");

        for (int k = 0; k <= line; k++)
        {
            printf("#");
        }

        // end of line
        printf("\n");
    }
}