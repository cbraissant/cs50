#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    /*
    AMERICAN EXPRESS:
        starts with:    34 or 37
        length:         15 digits

    MASTER CARD:
        starts with:    51 to 55
        length:         16 digits

    VISA:
        starts with:    4
        length:         13 or 16 digits

    CHECKSUM:
        multiply every other digit starting from the second-to-last
        add the products' digits together (ex: 2*6 = 12 -> 1+2 = 3)
        add those numbers
        add to remaining numbers
        if last digit is 0, the number is valid
    */

    // ask for a credit card number
    long  card = get_long("Number: ");


    // Check Luhn's Algorithm
    long card_num = card;
    int sum = 0;
    int product = 0;
    int digit = 0;
    bool valid = true;

    for (int j = 0; j < 16; j++)
    {
        // get the lowest digit
        digit = card_num % 10;

        // check if digit need to be double
        if (j % 2)
        {
            product = digit * 2;

            // add the products' digits
            if (product >= 10)
            {
                sum += 1;
            }
            sum += product % 10;
        }
        else
        {
            sum += digit;
        }

        // get the next digit
        card_num /= 10;
    }

    // check if valid or not
    if (sum % 10 != 0)
    {
        valid = false;
        printf("INVALID\n");
    }



    // check the type of card
    if (valid)
    {
        // MASTER CARD
        if ((card >= 5100000000000000) && (card <= 5599999999999999))
        {
            printf("MASTERCARD\n");
        }
        // AMERICAN EXPRESS
        else if ((card >= 340000000000000) && (card <= 349999999999999))
        {
            printf("AMEX\n");
        }
        else if ((card >= 370000000000000) && (card <= 379999999999999))
        {
            printf("AMEX\n");
        }
        // VISA
        else if ((card >= 4000000000000) && (card <= 4999999999999))
        {
            printf("VISA\n");
        }
        else if ((card >= 4000000000000000) && (card <= 4999999999999999))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

}
