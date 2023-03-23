# Simulate a sports tournament

# Sources used for reading files: https://www.geeksforgeeks.org/how-to-read-text-file-into-list-in-python/
# Used seven-day-average and other practice tasks code as examples and reference


import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # TODO: Read teams into memory from file
    teams = []
    file = open(sys.argv[1], "r")
    data = csv.DictReader(file)
    # data = file.read().split("\n") # use DictReader instead
    for row in data:
        row['rating'] = int(row['rating'])  # replace string with int for each team's rating in dictionary
        # team = row['team']  # for testing
        # rating = row['rating']  # for testing
        # print(rating) # for testing
        teams.append(row)  # Add team's row to teams list
    # print(teams)  # for testing

    # TODO: Simulate N tournaments and keep track of win counts
    counts = {}
    # run simulation to number of simulations value (N)
    for t in range(N):
        # collect winners in winner list after running simulation of tournament
        winner = simulate_tournament(teams)  # this runs up to 1000 times inside loop so needs to pass back a single winner not whole list
        # print(winner)  # for testing purposes only
        if winner['team'] in counts:
            counts[winner['team']] += 1
        else:
            counts[winner['team']] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


# comments for tracing how it works to solve simulate_tournaments
def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]  # gets passed in team1 rating
    rating2 = team2["rating"]  # gets passed in team2 rating
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))  # calculates probability of winning
    return random.random() < probability  # returns which team wins


# comments for tracing how it works to solve simulate_tournaments
def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):  # for each adjacent team in list, call simulate game to get winner
            winners.append(teams[i])  # if returns true, add team 1 to winners array
        else:
            winners.append(teams[i + 1])  # if returns false, add team 2 to winners array

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    results = []
    # length = len(teams)  # get length of teams array
    while len(teams) > 1:  # while there is more than 1 team in the passed in list
        if len(teams) % 2 == 0:  # if the number of teams is a power of two
            teams = simulate_round(teams)
            # results.append(simulate_round(teams))  # add simulate round result to results list
            # length -= 2
        else:
            print("Not enough teams")
            sys.exit(1)
        # print(length) # for testing only

    print(teams)
    return teams[0]  # has to return 1 winner not whole list


if __name__ == "__main__":
    main()
