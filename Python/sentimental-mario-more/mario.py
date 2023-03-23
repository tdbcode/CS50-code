import sys


def spaces(spaces, bricks):  # create procedure that passes in spaces and bricks
    for i in reversed(range(bricks, spaces)):  # run a for loop in reverse that outputs spaces to be run either side of bricks
        print(" ", end="")


def brick(bricks):  # create procedure that outputs bricks based on current depth
    for i in range(bricks):
        print("#", end="")


bricks = 0
height = 0

# validation to ensure height is not less than 1 or more than 8
while (height < 1 or height > 8):
    try:
        height = int(input("Height:"))
    except ValueError:  # when integer is not entered tell used to enter number
        print("You must enter a number")

# for the height entered
for x in range(height):
    bricks += 1  # add 1 to number of bricks
    spaces(height, bricks)  # draw spaces
    brick(bricks)  # draw bricks
    print("  ", end="")  # draw middle space
    brick(bricks)  # draw other side of bricks
    print("")  # make a new line
