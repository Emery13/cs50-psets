#include <stdio.h>
#include <cs50.h>

// This program dislpays a custom-sized pyramid on your screen

int main(void)
{
    // Prompt user for pyramid size
    int pyramidHeight = get_int("Height: ");
    // If size inferior to 1 or superior to 8, prompt user for another size
    if (pyramidHeight < 1 || pyramidHeight > 8)
    {
        // Keep prompting user if entered size is less than 1 or more than 8
        do
        {
            pyramidHeight = get_int("Height: ");
        }
        while (pyramidHeight < 1 || pyramidHeight > 8);
    }
    // Initialize a counter that will define the number of blocks per line; set to 1 since the first line should display at lease one block
    int counter = 1;
    while (pyramidHeight > 0)
    {
        // For-loop to define the number of space to display per line
        for (int i = pyramidHeight - 1; i > 0; i--)
        {
            printf(" ");
        }
        // For-loop to define the number of block to display per row, using the counter variable as upper limit
        for (int j = 0; j < counter; j++)
        {
            printf("#");
        }
        // Display the two spaces
        printf("  ");
        // Same for-loop as the previous one, to display the next column of blocks
        for (int k = 0; k < counter; k++)
        {
            printf("#");
        }
        // Go to next line once the row is finished
        printf("\n");
        // Increment counter variable by 1 to display 1 more # on the next line
        counter++;
        // Decrease pyramidHeight variable by 1 to update the number of remaining rows to display
        pyramidHeight--;
    }
}