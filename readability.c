#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calc(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");

    // Call func to count letters
    int letters = count_letters(text);

    // Call func to count words
    int words = count_words(text);

    // Call func to count sentences
    int sentences = count_sentences(text);

    // calculate the grade
    int c = calc(letters, words, sentences);

    // if grade is between 1 and 15
    if (c >= 1 && c <= 15)
    {
        printf("Grade %i\n", c);
    }
    else if (c < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }

}


int count_letters(string text)
{
    int letters = 0;
    // Loop through string until null character
    for (int i = 0; text[i] != '\0' ; i++)
    {
        // if current c is an alphabet
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }
    }
    return letters;
}


int count_words(string text)
{
    int words = 0;
    // Loop through string until null character
    for (int i = 0; text[i] != '\0'; i++)
    {
        // reach space = mark a word
        if (text[i] == ' ')
        {
            words++;
        }
    }
    return ++words;
}


int count_sentences(string text)
{
    int sentences = 0;
    // Loop through string until null character
    for (int i = 0 ; text[i] != '\0' ; i++)
    {
        // if '.', '!' or '?' so end of a sentence
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

int calc(int letters, int words, int sentences)
{
    float l = letters / (float)words * 100;
    float s = sentences / (float)words * 100;

    int c = round(0.0588 * l - 0.296 * s - 15.8);
    return c;
}