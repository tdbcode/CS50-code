from sys import argv
from pyfiglet import Figlet
import random
random.seed()
figlet = Figlet()
fonts = figlet.getFonts()

print(int(len(argv)))

if int(len(argv)) == 3:
    if (argv[1] != "-f"):
        print("Enter -f or -font followed by font name")
        sys.exit(1)
    figlet.setFont(font=argv[3])
else:
    rand = random.randint(1,len(fonts)) - 1
    figlet.setFont(font=fonts[rand])

print(figlet.font)
s = input("Enter text:" )
print(figlet.renderText(s))