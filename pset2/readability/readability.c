#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count(string text, int (*condition)(int c));

int is_end_char(int c);

int calculate_level(int num_letters, int num_words, int num_sentences);

int main(void)
{
    string text = get_string("Text: ");
    // Count the number of letters
    int num_letters = count(text, isalpha);
    // Count the number of spaces in the text
    int num_spaces = count(text, isspace);
    // There will always be one more word than the number of spaces
    int num_words = num_spaces + 1;
    // Count the number of sentences
    int num_sentences = count(text, is_end_char);

    int level = calculate_level(num_letters, num_words, num_sentences);
    if (level >= 16)
    {
        printf("Grade 16+");
    }
    else if (level < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", level);
    }
    printf("\n");
}

int count(string text, int (*condition)(int c))
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (condition(text[i]) != 0)
        {
            count++;
        }
    }
    return count;
}
int is_end_char(int c)
{
    if (c == '.' || c == '!' || c == '?')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int calculate_level(int num_letters, int num_words, int num_sentences)
{
    // Calculate the avg number of letters per 100 words
    float L = 100.0 * num_letters / num_words;
    // Calculate the avg number of sentences per 100 words
    float S = 100.0 * num_sentences / num_words;
    // Calculate the level
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return (int) round(index);
}