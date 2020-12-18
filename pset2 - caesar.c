#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void to_cipher(string plaintext, int k);

int main(int argc, string argv[])
{
    // if more or less than 1 command-line arg, print error and return 1
    if (argc != 2)
    {
        printf("Enter one command-line argument, no more, no less.\n");
        return 1;
    }

    // if command-line arg is not a positive integer, remind key usage and return 1
    int length = strlen(argv[1]);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // get command-line arg and make it an int
    int k = atoi(argv[1]);

    // get string to cipher
    string plaintext = get_string("plaintext: ");
    //printf("%s\n", plaintext);

    // call the to_cipher function to encrypt the text
    to_cipher(plaintext, k);

    //printf("ciphertext: %s\n", ciphertext);
    return 0;
}

void to_cipher(string plaintext, int k)
{
    // get plaintext length
    int length = strlen(plaintext);

    // print ciphertext
    printf("ciphertext: ");

    // go through plaintext
    for (int i = 0; i < length; i++)
    {
        // check if plaintext[i] is a-z A-Z
        if (isalpha(plaintext[i]) != 0)
        {
            // check if plaintext[i] is uppercase or lowercase
            if (isupper(plaintext[i]) == 0)
            {
                // encript plaintext[i] if plaintext[i] is lowercase
                //plaintext[i] = ((plaintext[i] + k) % 122);
                plaintext[i] = ((plaintext[i] - 97 + k) % 26) + 97;
            }
            else
            {
                // encript plaintext[i] if plaintext[i] is uppercase
                plaintext[i] = ((plaintext[i] - 65 + k) % 26) + 65;
            }
            // print ciphered plaintext[i]
            printf("%c", (char) plaintext[i]);
        }
        else
        {
            // print plaintext[i]
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}