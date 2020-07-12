#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user for a name
    string name = get_string("What is your name?\n");

    // Greet the user
    printf("hello, %s\n", name);
}