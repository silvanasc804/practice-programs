#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int letters_number(string s);
int words_number(string s);
int sentences_number(string s);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");
    // Count the number of letters, words, and sentences in the text
    int text_letters = letters_number(text);
    int text_words = words_number(text);
    int text_sentences = sentences_number(text);
    // Compute the Coleman-Liau index
    float L = 100.0 * (float) text_letters / (float) text_words;
    float S = 100.0 * (float) text_sentences / (float) text_words;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // Print the grade level
    if (index <= 16 && index >= 1)
    {
        printf("Grade %i\n", index);
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}

int letters_number(string s)
{
    // Keep track of letters
    int letters = 0;

    // Compute nnumber of letters
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (isalnum(s[i]))
        {
            letters++;
        }
    }
    return letters;
}

int words_number(string s)
{
    // Keep track of words
    int words = 1;

    // Compute number of letters
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (isspace(s[i]))
        {
            words++;
        }
    }
    return words;
}

int sentences_number(string s)
{
    // Keep track of sentences
    int sentences = 0;

    // Compute number of sentences
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}
