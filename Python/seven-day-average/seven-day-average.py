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
    states = []
    i = 0
    for row in reader:
        if (i < 49):
            states[i] = row['state']
        date = row["date"]
        states[] = row['state']
        fibs = row['fips']
        cases = row['cases']
        death = row['deaths']
        print(state, ": ", cases)


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    ...


main()
