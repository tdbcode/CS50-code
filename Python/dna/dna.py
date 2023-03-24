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
        rows = list(database)
        rlength = len(rows)
        file.seek(0)
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
    clength = len(database.fieldnames)  # get length of a row in the database using fieldnames
    keys = [""] * clength  # set up temporary key with length of database row
    for k in range (0, clength):  # loop through database and save fieldnames to keys
        keys[k] = database.fieldnames[k]
    keys.remove('name')
    # print(keys)  # for testing purposes only
    longestmatch = [0] * int(clength - 1)

    for i in range(0, clength - 1):
        tempkey = keys[i]
        #print(tempkey)  # for testing purposes only
        longestmatch[i] = longest_match(DNA,tempkey)

    #print(longestmatch)  # for testing purposes only

    # Check database for matching profiles
    pmatch = [[0] * int(clength - 1)] * rlength
    for person in database:  # Short Format: AGATC,AATG,TATC
        matches = 0
        if person['name'] != "name":
            for i in range (0,clength-1):
                tempkey = keys[i]
                if int(person[tempkey]) == longestmatch[i]:
                    matches += 1
                    # print(matches)  # for testing purposes only

        if matches == len(longestmatch):
            print(person["name"])
            break

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
