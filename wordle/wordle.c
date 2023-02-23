#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    int wordsize = 0;

    // Make sure there is an argument, if there is convert it to an integer and store in wordsize
    if (argc != 2)
    {
        printf("Missing argument.\n");
        return 1;
    }
    else
    {
        wordsize = atoi(argv[1]);
        // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
        if (wordsize < 5 || wordsize > 8)
        {
            printf("Wordsize must be 5, 6, 7 or 8.\n");
            return 1;
        }
    }

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        for (int x = 0; x < wordsize; x++)
        {
            status[x] = 0;
        }

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    // TODO #7

    // that's all folks!
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";
    char temp;
    bool validchar = false;
    // ensure users actually provide a guess that is the correct length
    do
    {
        guess = get_string("Input a %i-letter word: ", wordsize);

        // Run through every character in guess
        for (int c = 0; c < wordsize; c++)
        {
            temp = guess[c]; // Set temp variable to current character

            // If current character is an alphabetic character (and not a punctuation mark or number)
            if (isalpha(temp))
            {
                guess[c] = tolower(temp);    // Convert current character to lower case
                validchar = true;            // Set that it is a valid char to true
            }
            else
            {
                validchar = false;          // Else, if it is not a alphabetic character, then set valid char to false
                break;                     // Exit for loop
            }
        }
    } while(strlen(guess) != wordsize || validchar == false); // Repeat until the guess entered is exactly the worldsize and it is all valid characters

    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;
    char currentGuess;
    char currentChoice;

    // compare guess to choice and score points as appropriate, storing points in status
     for (int g = 0; g < wordsize; g++)
     {
        currentGuess = guess[g];
         for (int c = 0; c < wordsize; c++)
         {
            currentChoice = choice[c];
            if (currentGuess == currentChoice)
            {
                if (g == c)
                {
                status[g] = 2;
                score += 2;
                break;
                }
                else
                {
                    status[g] = 1;
                    score += 1;
                }
            }
        }

       printf("%i\n", status[g]);

     }

    // HINTS
    // iterate over each letter of the guess
        // iterate over each letter of the choice
            // compare the current guess letter to the current choice letter
                // if they're the same position in the word, score EXACT points (green) and break so you don't compare that letter further
                // if it's in the word, but not the right spot, score CLOSE point (yellow)
        // keep track of the total score by adding each individual letter's score from above

    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6

    printf("\n");
    return;
}
