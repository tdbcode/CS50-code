from sys import argv
import sys
from pyfiglet import Figlet
import random
random.seed()
figlet = Figlet()
fonts = figlet.getFonts()
arglength = int(len(argv))

if arglength == 3 or arglength > 1 and <3::
    if (argv[1] != "-f" and argv[1] != "-font"):
        print("Enter -f or -font followed by font name")
        sys.exit(1)
    elif argv[2] in fonts:
        figlet.setFont(font=argv[2])
    else:
        print("Invalid font")
        sys.exit(1)
else:
    rand = random.randint(1,len(fonts)) - 1
    figlet.setFont(font=fonts[rand])

print(figlet.font)
s = input("Enter text:" )
print(figlet.renderText(s))