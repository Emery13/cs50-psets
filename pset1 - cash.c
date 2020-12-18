#include <stdio.h>
#include <cs50.h>
#include <math.h>

// This is the program for a greedy algorithm 

int main(void)
{
    // Prompt user for an amout of change
    float change = get_float("Change owed: ");
    // If the amount entered is inferior to 0, keeping prompting the user
    if (change < 0)
    {
        do
        {
            change = get_float("Change owed: ");
        }
        while (change < 0);
    }

    // Convert the sum to cents
    int cents = round(change * 100);
    // Create one variable for each coin
    int twentyFiveCents = 25, tenCents = 10, fiveCents = 5, oneCent = 1;
    // Initialize a couter to count the number of coins
    int counter = 0;
    // Initialize a buffer variable to keep intermediate counts in memory
    int buffer = 0;

    // Check how many coins of 25 cents are needed when cents > 25 cents
    if (cents >= twentyFiveCents)
    {
        counter += floor(cents / twentyFiveCents);
        cents = cents - (twentyFiveCents * counter);
    }

    // Check how many coins of 10 cents are needed when cents > 10 cents
    if (cents >= tenCents)
    {
        buffer = floor(cents / tenCents);
        counter += buffer;
        cents = cents - (tenCents * buffer);
    }

    // Check how many coins of 5 cents are needed when cents > 5 cents
    if (cents >= fiveCents)
    {
        buffer = floor(cents / fiveCents);
        counter += buffer;
        cents = cents - (fiveCents * buffer);
    }

    // Check how many coins of 1 cents are needed when cents > 1 cents
    if (cents >= oneCent)
    {
        buffer = floor(cents / oneCent);
        counter += buffer;
        cents = cents - (oneCent * buffer);
    }
    
    // Display counter
    printf("%i\n", counter);
}