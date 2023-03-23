import sys

def spaces(spaces, bricks):
    for i in reversed(range(bricks, spaces)):
        print(" ", end="")


def brick(bricks):
    for i in range(bricks):
        print("#", end="")


bricks = 0
height = 0


while (height < 1 or height > 8):
    try:
        height = int(input("Height:"))
    except ValueError:
        print("You must enter a number")

for x in range(height):
    bricks += 1
    spaces(height, bricks)
    brick(bricks)
    print("  ", end="")
    brick(bricks)
    print("")
