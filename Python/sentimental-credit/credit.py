import sys


creditno = 0
creditno2 = 0
clength = 0
currentNo = 0
product =  0
checksum = 0

ccno = [0] * 16
valid = False

while valid == False:  # while an invalid number has been entered
    try:
        creditno = input("Enter the credit card number: ")  # ask the user to enter credit card number
        clength = int(len(creditno))  # get length of credit card number
        # print(clength)  # for testing only

        if clength < 13 or clength > 16 or clength == 14:  # if credit card length is less than 13, more than 16 or 14
            raise ValueError  # then throw a Value Error
        else:
            valid = True  # if no error, exit loop
    except ValueError:
        print("INVALID")  # if a value error, output INVALID and exit
        sys.exit(1)

creditno2 = creditno  # copy credit card number to temp varible for analysis

for c in reversed(range(1,clength)):  # run loop in reverse to go from back of credit card number
    currentNo = int(creditno2) % 10  # take the end number to add to new array
    creditno2 = int(int(creditno2) / 10)  # remove last number
    ccno[c] = currentNo  # add last number back in it's possition in the array

for a in reversed(range(2,clength,-2)):  # run loop in reverse skipping every other number
    currentNo = ccno[a] * 2  # double the current number in the array
    if (currentNo > 9):  # check if current number as more than 1 digit
        product = (currentNo % 10) + (currentNo / 10)  # if so then add them together
        currentNo = product  # set new number to current number

    checksum += currentNo  # add current number to checksum

for b in reversed(range(1,clength,-2)):  # run loop in reverse skipping every other number
    currentNo = ccno[b-1]
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
else:
    print("INVALID")