

sentence = input("Text: ")




int main(void)
{
    string sentence = get_string("Text: ");     // Ask the user for the text passage
    int letters = 0;
    int words = 0;
    int sentences = 0;
    float index = 0;
    int grade = 0;

    letters = count_letters(sentence);       // Save number of letters using count letters function

    words = count_words(sentence);          // Save number of words using count words function

    sentences = count_sentences(sentence); // Save number of sentences using count sentences function

    index = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8; // Perform readability calculation

    grade = round(index); // Round the readability

    // Output grade based on requirements
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

int count_letters(string text)
{
    char temp;
    int letters = 0;

    //Iterate through each character in the sentence
    for (int c = 0; c < strlen(text); c++)
    {
        temp = text[c]; // Set the current character to a temp variable

        // Check if current character is either not a space or a puncuation and add 1 to letters
        if (isalnum(temp))
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

    //Iterate through each character in the sentence
    for (int c = 0; c < strlen(text); c++)
    {
        temp = text[c]; // Set the current character to a temp variable

        // Check if current character is either a space or and not a hypen (-) and add 1 to words
        if (isblank(temp) && temp != 45)
        {
            words++;
        }
    }

    words++; // Add one word to include end of sentence (which isn't counter otherwise)
    return words;
}

int count_sentences(string text)
{
    char temp;
    int sentences = 0;

    //Iterate through each character in the sentence
    for (int c = 0; c < strlen(text); c++)
    {
        temp = text[c]; // Set the current character to a temp variable

        // Check if current character is either an explanation mark, aperiod or a question mark and add 1 to sentences
        if (temp == 33 || temp == 46 || temp == 63)
        {
            sentences++;
        }
    }

    return sentences;
}