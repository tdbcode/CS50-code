import csv
import sys


def main():

    # TODO: Check for command-line usage
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py databases/filename.csv sequences/filename.txt")


    # Read database file into a variable
    try:
        file = open(sys.argv[1], "r")
        database = csv.DictReader(file)
    except FileNotFoundError:
        sys.exit("Usage: python dna.py databases/filename.csv sequences/filename.txt")


    # Read DNA sequence file into a variable
    try:
        file = open(sys.argv[2], "r")
        DNA = file.read()
    except FileNotFoundError:
        sys.exit("Usage: python dna.py databases/filename.csv sequences/filename.txt")
    # print(DNA) # for testing only


    # Find longest match of each STR in DNA sequence
    rlength = len(database.fieldnames)  # get length of a row in the database using fieldnames
    keys = [""] * rlength  # set up temporary key with length of database row
    for k in range (1, rlength):  # loop through database and save fieldnames to keys
        keys[k] = database.fieldnames[k]
    # print(keys) # for testing purposes only
    longestmatches = [0] * rlength

    for i in range(1, rlength):
        tempkey = keys[i]
        for row in database:  # Format: name,AGATC,AATG,TATC
            longestmatches[i] = longest_match(DNA,row[tempkey])

    print(longestmatches)

            # replace string with int for each team's rating in dictionary
            # temp = row[keys[i]]
            # TATC = row['TATC']



    # TODO: Check database for matching profiles

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
