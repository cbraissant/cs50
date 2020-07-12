#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

bool validate_key(string key);
void encode(string text, string key);
void to_uppercase(string text);

int main(int argc, string argv[])
{
    // check if only one argument is provided
    if (argc != 2)
    {
        printf("Wrong arguement. Please provide an encryption code, and only that.\n");
        return 1;
    }

    // save the key
    string key = argv[1];
    // printf("Key: %s\n", key);

    // convert the key to uppercase (change the key)
    to_uppercase(key);
    // printf("Key upper: %s\n", key);

    // check if the key is invalide
    if (validate_key(key) == false)
    {
        return 1;
    }
    // printf("Key is valid\n");

    // ask the user for an input
    string text = get_string("plaintext: ");

    // encode the text (modifiy the text argument)
    encode(text, key);
    printf("ciphertext: %s\n", text);
}


/*
Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.
Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.
*/

/*
 * ENCODE
 * Encode the text with the key given as arguments and return the cipher
 */
void encode(string text, string key)
{
    int text_length = strlen(text);
    char letter;

    for (int i = 0; i < text_length; i++)
    {
        // extract the character
        letter = text[i];

        // encode alphabetic character
        if (isalpha(letter))
        {
            if (isupper(letter))
            {
                text[i] = key[letter - 65];
            }
            else
            {
                text[i] = key[letter - 97] + 32;
            }
        }
    }
}






/*
 * TO_UPPERCASE
 * Convert a string to uppercase
 * WARNING: Mutate the original string
 */
void to_uppercase(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = toupper(text[i]);
    }
}






/*
 * VALIDATE_KEY
 * Check if the key given as an argument is valide following the program criterias
 */
bool validate_key(string key)
{
    // check the length
    int key_length = strlen(key);
    if (key_length != 26)
    {
        printf("The key doesn't have 26 characters\n");
        return false;
    }


    // check for non-alphabetic characters
    for (int i = 0; i < key_length; i++)
    {
        // check for alphabetic character
        if (isalpha(key[i]) == false)
        {
            printf("The key must only contain alphabetic characters\n");
            return false;
        }
    }


    // check if each character is only used once
    bool used_once[25];
    int j = 0;
    while (j <= 25)
    {
        used_once[j] = 0;
        j++;
    }

    int ascii = 0;
    for (int i = 0; i < key_length; i++)
    {
        // get the ascii code of the character
        ascii = key[i];

        // check if character already used
        if (used_once[ascii - 65])
        {
            printf("Same character used multiple times\n");
            return false;
        }
        else
        {
            used_once[ascii - 65] = true;
        }

    }

    return true;
}