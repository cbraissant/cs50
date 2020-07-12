#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Get the sentence from the user
    string text = get_string("Text: ");

    // Get the length of the string
    int length = strlen(text);

    // initialise the variables
    int letter_count = 0;
    int word_count = 1;
    int sentence_count = 0;

    for (int i = 0; i < length; i++)
    {
        // get the ascii code of the character
        int ascii_code = (int)text[i];

        //increase letter count if character is a uppercase letter
        if (ascii_code >= 65)
        {
            if (ascii_code <= 90)
            {
                letter_count++;
            }
        }

        //increase letter count if character is a lowercase letter
        if (ascii_code >= 97)
        {
            if (ascii_code <= 122)
            {
                letter_count++;
            }
        }

        //increase word count if character is a space
        if (ascii_code == 32)
        {
            word_count++;

        }

        //increase sentence count if ".", "!" or "?" ,
        if (ascii_code == 46)
        {
            sentence_count++;

        }

        if (ascii_code == 33)
        {
            sentence_count++;

        }

        if (ascii_code == 63)
        {
            sentence_count++;

        }


    }

    // debug
    // printf("%d letter(s)\n", letter_count);
    // printf("%d word(s)\n", word_count);
    // printf("%d sentence(s)\n", sentence_count);


    // average number of letters per 100 words
    float L = letter_count  * 100.0 / word_count;

    // average number of sentences per 100 words
    float S = sentence_count * 100.0 / word_count ;


    // Coleman-Liau number
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);


    // printf("L: %f\n", L);
    // printf("S: %f\n", S);
    // printf("index: %f\n", index);

    // Display the grade
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

}