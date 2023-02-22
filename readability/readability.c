#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_letters(string text);

int main(void)
{
    string sentence = get_string("Text: ");
    int letters = 0;
    printf("%s\n", sentence);

    letters = count_letters(sentence);
    printf("%i letters\n", letters);

}

int count_letters(string text)
{
    int letters = 0;
    char temp;

    for (int c = 0; c < strlen(text); c++)
    {
        temp = text[c];

        if(ispunct(temp) || isblack(ispunct) || )
    }

    return letters;

}