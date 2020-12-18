#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int letter_count(string);   // Letter-counting function
int word_count(string);     // Word-counting function
int sentence_count(string); // Sentence-counting function

int main(void)
{
    string text = get_string("Text : ");
    // Compute the average number of letters per 100 words
    float average_letters = (letter_count(text) / (float) word_count(text)) * 100;
    // Compute the average number of sentences per 100 words
    float average_sentences = (sentence_count(text) / (float) word_count(text)) * 100;
    // Compute the Coleman-Liau index
    float index = (0.0588 * average_letters) - (0.296 * average_sentences) - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int letter_count(string text)
{
    int count = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        // Get both lowercases and uppercases
        if (((int) text[i] >= 65 && (int) text[i] <= 90) || ((int) text[i] >= 97 && (int) text[i] <= 122))
        {
            count++;   
        }
    }
    return count;
}

int word_count(string text)
{
    int count = 1;  // Spaces are in between words, meaning there is always 1 more word than there are spaces
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if ((int) text[i] == 32)
        {
            count++;
        }
    }
    return count;
}

int sentence_count(string text)
{
    int count = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if ((int) text[i] == 33 || (int) text[i] == 46 || (int) text[i] == 63)  // Get '.', '?' and '!'
        {
            count++;
        }
    }
    return count;
}