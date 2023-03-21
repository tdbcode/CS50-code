# Prints a row of 4 question marks with a loop

for i in range(4):
    print("?", end="") #end replaces new line with blank line
print()

print("?" * 4)

for i in range(3):
    for j in range(3):
        print("#", end="")
    print()