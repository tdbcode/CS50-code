import csv
import requests

# Source used to help : https://courses.cs.washington.edu/courses/cse140/13wi/csv-parsing.html


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()  # New dictionary for new cases

    for row in reader:  # for each row in the dictionary file
        state = row['state']    # Assign state to variable
        cases = int(row['cases'])  # Assign number of cases to variable

        if state not in new_cases:  # if state doesn't exist in new case
            new_cases[state] = []  # add state to dictionary
        if len(new_cases[state]) >= 14:  # check if the current state data is at 14 days
            new_cases[state].pop(0)  # If so remove an item from current state
        new_cases[state].append(cases)  # Add todays case to current stack
    # print(new_cases) # for testing purposes
    return new_cases


def comparative_averages(new_cases, states):
    firstlist = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    firstavg = 0
    i = 1
    for state in states:
        firstlist[i] = sum(new_cases[row][1:8])
        firstavg = firstlist[i] / 7
        print(firstavg)


main()