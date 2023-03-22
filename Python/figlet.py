from sys import argv
from pyfiglet import Figlet
import random
random.seed()
figlet = Figlet()

if len(argv) == 2:
    if (argv[1] != '-f' or argv[1] != '-font'):
        print("Enter -f or -font followed by font name")
        sys.exit(1)
    figlet.setFont(font=argv[3])
else:
    rand = random.randint(1,3)
    if (rand==1):
        
    figlet.setFont(font=rand)


s = input("Enter text:" )
print(figlet.renderText(s))