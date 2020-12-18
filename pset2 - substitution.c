#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void to_cipher(string plaintext, string key);

int main(int argc, string argv[])
{
    // if more or less than 1 command-line arg, print error and return 1
    if (argc != 2)
    {
        printf("Enter one command-line argument, no more, no less.\n");
        return 1;
    }

    // if command-line arg is not a string with only letters, remind key usage and return 1
    int length = strlen(argv[1]);
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Enter letters only\n");
            return 1;
        }
    }

    // if command-line arg doesn't contain 26 characters
    if (length != 26)
    {
        printf("The key should be 26 characters long.\n");
        return 1;
    }

    // check if the key is containing each letter exactly once
    for (int i = 0; i < length; i++)
    {
        // check if argv[1][i] is lowercase; if it is :
        if (!isupper(argv[1][i]))
        {
            for (int j = i + 1; j < length; j++)
            {
                if ((int) argv[1][i] == (int) argv[1][j] || (int) argv[1][i] == ((int) argv[1][j] + 32))
                {
                    printf("Each letter should be contained only once.\n");
                    return 1;
                }
            }
        }
        // else, if argv[1][i] is uppercase
        else
        {
            for (int j = i + 1; j < length; j++)
            {
                if ((int) argv[1][i] == (int) argv[1][j] || (int) argv[1][i] == ((int) argv[1][j] - 32))
                {
                    printf("Each letter should be contained only once.\n");
                    return 1;
                }
            }
        }
    }

    // get string to cipher
    string plaintext = get_string("plaintext: ");

    // call the to_cipher function to encrypt the text
    to_cipher(plaintext, argv[1]);

    return 0;
}

void to_cipher(string plaintext, string key)
{
    // get plaintext length
    int length = strlen(plaintext);

    // print ciphertext
    printf("ciphertext: ");

// TODO
// 5 -  Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, 
//      with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.
    
    // initialize a position viariable
    int position = 0;

    // go through plaintext
    for (int i = 0; i < length; i++)
    {
        // check if plaintext[i] is a-z A-Z
        if (isalpha(plaintext[i]))
        {
            // check if key[i] is lowercase; if it is :
            if (!isupper(plaintext[i]))
            {
                // get plaintext[i] letter's position in the alphabet
                position = ((int) plaintext[i] - 97);
                // if the key is also lowercase, print it
                if (!isupper(key[position]))
                {
                    printf("%c", key[position]);
                }
                // else, make it lowercase, then print it
                else
                {
                    //(int) key[position] + 32
                    printf("%c", (int) key[position] + 32);
                }
            }
            // else, if key[i] is uppercase
            else
            {
                // get plaintext[i] letter's position in the alphabet
                position = ((int) plaintext[i] - 65);
                // if the key is also uppercase, print it
                if (!islower(key[position]))
                {
                    printf("%c", key[position]);
                }
                // else, make it uppercase, then print it
                else
                {
                    //(int) key[position] - 32
                    printf("%c", (int) key[position] - 32);
                }
            }
        }
        else
        {
            // print plaintext[i]
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}