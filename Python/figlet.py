from sys import argv
from pyfiglet import Figlet
import random
random.seed()
figlet = Figlet()

if len(argv) == 2:
    figlet.setFont(font=argv[3])
elif len(argv) == 1:
    rand = random.randint(1,20)
    figlet.setFont(font=rand)
else:
    print("Enter -f -fontnamehere")

s = input("Enter text:" )
print(figlet.renderText(s))