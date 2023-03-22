# Averages three numbers using a list and a loop

# Get scores
scores = []
for i in range(3):
    score = int(input("Score: "))
    scores.append(score)

# Print average
average = sum(scores) / len(scores)
print(f"Average: {average:.2f}")