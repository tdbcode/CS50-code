def count_letters(text):
    letters = 0

    # Iterate through each character in the sentence
    for c in range(len(text)):
        temp = text[c]  # Set the current character to a temp variable

        # Check if current character is either not a space or a puncuation and add 1 to letters
        if temp.isalnum():
            letters += 1

    return letters


def count_words(text):
    words = 0

    # Iterate through each character in the sentence
    for c in range(len(text)):
        temp = text[c]  # Set the current character to a temp variable

        # Check if current character is either a space or and not a hypen (-) and add 1 to words
        if temp.isspace() and temp != "-":
            words += 1

    words += 1  # Add one word to include end of sentence (which isn't counter otherwise)
    return words


def count_sentences(text):
    sentences = 0

    # Iterate through each character in the sentence
    for c in range(len(text)):
        temp = text[c]  # Set the current character to a temp variable

        # Check if current character is either an explanation mark, aperiod or a question mark and add 1 to sentences
        if (temp == "!" or temp == "." or temp == "?"):
            sentences += 1
    return sentences


sentence = input("Text: ")

letter = 0
words = 0
sentences = 0
index = 0
grade = 0

letters = count_letters(sentence)  # Save number of letters using count letters function
words = count_words(sentence)  # Save number of words using count words function
sentences = count_sentences(sentence)  # Save number of sentences using count sentences function

index = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8  # Perform readability calculation
grade = round(index)  # Round the readability

# Output grade based on requirements
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print("Grade ", grade)