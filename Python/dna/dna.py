import csv
import sys


def main():

    # Check for command-line usage
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
    clength = len(database.fieldnames)  # get length of a row in the database using the fieldnames
    keys = [""] * clength  # set up key list with placeholders of the length of database row
    for k in range (0, clength):  # loop through database and save fieldnames to keys
        keys[k] = database.fieldnames[k]
    keys.remove('name')  # remove name from keys as it isn't needed
    # print(keys)  # for testing purposes only
    longestmatch = [0] * int(clength - 1)  # create longest match list witj the length of the keys (minus names (so - 1))

    for i in range(0, clength - 1):  # loop through the keys
        tempkey = keys[i]  # assign current key to temp variable
        #print(tempkey)  # for testing purposes only
        longestmatch[i] = longest_match(DNA,tempkey)  # save in list the longest match for current key

    #print(longestmatch)  # for testing purposes only

    # Check database for matching profiles
    # pmatch = [[0] * int(clength - 1)] * rlength  # redundant, was going to build DNA list for all people but not needed
    for person in database:  # For each person in the database (Short Format: AGATC,AATG,TATC)
        matches = 0  # set current matches to 0
        if person['name'] != "name":  # if person name does not equal name (so ignore first row after seek used at top)
            for i in range (0, clength-1):  # repeat til end of keylist
                tempkey = keys[i]  # assign current key as  temporary key
                if int(person[tempkey]) == longestmatch[i]:  # see if person's key count matches the longest match count
                    matches += 1  # if so add 1 to matches
                    # print(matches)  # for testing purposes only

        if matches == len(longestmatch):  # if matches equals the length of longest match then it must be this person
            print(person["name"])  # print persons name
            return

    print("No match")  # else print no match

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
