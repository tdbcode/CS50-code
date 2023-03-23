import sys


creditno = 0
creditno2 = 0
clength = 0
currentNo = 0
product =  0
checksum = 0

ccno = [0] * 16
valid = False

while valid != True:
    try:
        creditno = input("Enter the credit card number: ")
        clength = int(len(creditno))
        print(clength)

        if clength < 13 or clength > 16 or clength == 14:
            raise ValueError
        else:
            valid = True
    except ValueError:
        print("INVALID")
        sys.exit(1)

creditno2 = creditno

for c in reversed(range(0,clength)):
    currentNo = int(creditno2) % 10
    creditno2 = int(creditno2) / 10
    ccno[c] = currentNo

for a in reversed(range(0,clength,-2)):
    currentNo = ccno[a -1] * 2
    if (currentNo > 9):
        product = (currentNo % 10) + (currentNo / 10)
        currentNo = product

    checksum += currentNo

    creditno2 = creditno

for b in reversed(range(0,clength,-2)):
    currentNo = ccno[b]
    checksum += currentNo

if (checksum % 10) == 0:
    if (clength == 13 or clength == 16) and ccno[0] == 4:
        print("VISA")
    elif clength == 16 and (ccno[0] == 5 and (ccno[1] > 0 and ccno[1] <6)):
        print("MASTERCARD")
    elif clength == 15 and (ccno[0] == 3 and (ccno[1] == 4 or ccno[1] == 7)):
        print("AMEX")
    else:
        print("INVALID")