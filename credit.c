#include <stdio.h>
#include <cs50.h>
#include <math.h>

// This is the program for the credit card number cheking algorithm 

int main(void)
{
    // Prompt user for a credit card number
    long cardNumber = get_long("Number: ");
    
    // Copy that value into another variable to start the while loop
    long whileLoopIteration = cardNumber;

    // Initialize two variables, one for the sum of digits that will be
    // multiplied by two and the other for the sum of other digits
    int sumDigitsX2 = 0, sumOtherDigits = 0;

    // Initalize a boolean variable that will determine to which of the 
    // above variable should the digit be dispatched.
    // If the value is 'true', it should go to sumDigitsX2,
    // else, to sumOtherDigits;
    bool multipliedBy2 = false;

    // Initalize a remainder variable to stock the cardNumber % 10 remainder 
    int remains = 0;

    // Initalize a buffer variable
    int buffer = 0;
    
    // Initialize a counter to count the number of iteration of the while loop,
    // to get the number of digits in the card number
    int count = 0;
    
    // Dispatch each digit to be added in two different variables
    while (whileLoopIteration > 0)
    {
        if (multipliedBy2 == false)
        {
            remains = whileLoopIteration % 10;
            sumOtherDigits += (remains);
            multipliedBy2 = !multipliedBy2;
        }
        else
        {
            remains = (whileLoopIteration % 10) * 2;

            // Check whether remains > 9, to make sure digits are added.
            // If remains > 9, use buffer variable to add both digits together
            if (remains > 9)
            {
                remains = floor(remains / 10) + remains % 10;
                //remains = buffer;
            }

            sumDigitsX2 += remains;
            multipliedBy2 = !multipliedBy2;
        }

        whileLoopIteration = floor(whileLoopIteration / 10);
        count++;
    }
    
    if ((sumOtherDigits + sumDigitsX2) % 10 == 0)
    {
        // Initialize a variable to get the first two digits and a second one to 
        // get the first digit to check the type of credit card (American Express, 
        // MasterCard, Visa).
        int firstTwoDigits = 0;
        int firstDigit = 0;

        // Get the first two digits
        long multiplier = 1;
        for (int i = count - 2; i > 0; i--)
        {
            multiplier *= 10;
        }
        firstTwoDigits = floor(cardNumber / multiplier);

        // Get the first digit
        firstDigit = floor(firstTwoDigits / 10);

        // Check if card is American Express (count = 15, starts with 34 or 37)
        if (count == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
        {
            printf("AMEX\n");   
        }

        // Check if card is Master Card (count = 16, starts with 51, 52, 53, 54 or 55)
        else if (count == 16 && (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 ||
                                 firstTwoDigits == 54 || firstTwoDigits == 55))
        {
            printf("MASTERCARD\n");   
        }

        // Check if card is Visa (count = 13 OR 16, starts with 4)
        else if ((count == 13 || count == 16) && firstDigit == 4)
        {
            printf("VISA\n");   
        }
        
        // If valid number but doesn't correspond to any of the three types
        else
        {
            printf("INVALID\n");
        }
        
    }
    else
    {
        printf("INVALID\n");
    }
}