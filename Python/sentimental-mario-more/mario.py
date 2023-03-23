def spaces(spaces, bricks):
    print(" ", end="")


def brick(bricks):
    for i in range(bricks):
        print("#",end="")

bricks = 0
height = 0


while (height < 1 or height > 8):
    height = int(input("Height:"))

    for x in range(height):
        bricks += 1
        spaces(height, bricks)
        brick(bricks)
        print(" ", end="")
        brick(bricks)
        print("")

