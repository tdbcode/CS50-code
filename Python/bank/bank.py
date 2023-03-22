import re # Import regular expression library

greeting = str(input("What was the greeting?"))

words = greeting.split()
first = words[0]
# use re.sub|() function
first = re.sub(",", "", first) # remove commas from string

if (first.lower() == 'hello'):
    amount = 0
elif (first[0].lower() == 'h'):
    amount = 20
else:
    amount = 100

print(f"${amount}",end="")