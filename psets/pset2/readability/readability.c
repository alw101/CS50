#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Get input
    string text = get_string("Text: ");
    
    //Calculate number of letters
    int letters = count_letters(text);
    
    //Calculate number of words
    int words = count_words(text);
    
    //Calculate number of sentences
    int sentences = count_sentences(text);
    
    //Calculate grade average
    int grade = round(0.0588 * ((float) letters / words * 100) - 0.296 * ((float) sentences / words * 100) - 15.8);
    
    //Print Grade Level
    if (grade > 1 && grade < 16)
    {
        //If 2 to 15
        printf("Grade %i\n", grade);
    }
    if (grade <= 1)
    {
        //If 1 or less
        printf("Before Grade 1\n");
    }
    if (grade >= 16)
    {
        //If 16 or
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32)
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            count++;
        }
    }
    return count;
}