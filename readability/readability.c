#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string sentence = get_string("Text: ");
    int letters = 0;
    int words = 0;
    int sentences = 0;
    long index = 0;
    printf("%s\n", sentence);

    letters = count_letters(sentence);
    printf("%i letters\n", letters);

    words = count_words(sentence);
    printf("%i words\n", words);

    sentences = count_sentences(sentence);
    printf("%i sentences\n", sentences);

    index = 0.0588 * (words/100) - 0.296 * (sentences/100) - 15.8;
    printf("%ld index\n", index);

}

int count_letters(string text)
{
    char temp;
    int letters = 0;

    for (int c = 0; c < strlen(text); c++)
    {
        temp = text[c];

        if(!(ispunct(temp) || isblank(temp)))
        {
            letters++;
        }
    }

    return letters;
}

int count_words(string text)
{
    char temp;
    int words = 0;

    for (int c = 0; c < strlen(text); c++)
    {
        temp = text[c];

        if (isblank(temp) && temp != 45)
        {
            words++;
        }
    }

    words++;
    return words;
}

int count_sentences(string text)
{
    char temp;
    int sentences = 0;

    for (int c = 0; c < strlen(text); c++)
    {
        temp = text[c];

        if (temp == 21 || temp == 46 || temp == 63)
        {
            sentences++;
        }
    }

    return sentences;
}