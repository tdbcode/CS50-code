import sys


# twotimed = 0
# regular = 0
checksum = 0
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
        sys.exit(1)  # exit program with error code 1

ccno = [0] * clength  # make list with 0s as placeholders at the length of credit card number

for c in range(0, clength):  # run loop to add each digit to list as integers
    ccno[c] = int(creditno[c])
    # creditno2 = creditno2 / 10  # remove last number
    # ccno[c] = int(currentNo)  # add last number back in it's possition in the array

locator = clength - 2  # set up locator variable which will track back of list for doubling algorithm
# print(clength)  # for testing purposes only

for a in range(0, clength, 2):  # run loop skipping every other number
    if (locator < 0):  # if locator is less than 0 (off the front of the list)
        currentNo = 0  # set currentNo to 0 to avoid error in calculation of checksum
    else:
        currentNo = int(creditno[locator]) * 2  # else double the current number in the array

    while (currentNo > 9):  # while current number as more than 1 digit
        product = int(currentNo % 10) + int(currentNo / 10)  # if so then add them together
        currentNo = product  # set new number to current number
    checksum += currentNo  # add current number to check sum
    checksum += int(creditno[locator + 1])  # add adjecent number to check sum
    # print("Position ", locator, " : ", currentNo, ", Position ", locator+1, ": ", ccno[locator + 1], ". Checksum:", checksum) # for testing purposes only
    locator -= 2  # mins 2 from locator to shift to next position in the array

# checksum = sum(twotimed) + sum(regular)  # add current number to checksum - redundant

if (checksum % 10) == 0:  # if checksum is divisible by 10
    # check if the length is 13 or 16 and the first number is a 4 - if so, it's a VISA
    if (clength == 13 or clength == 16) and ccno[0] == 4:
        print("VISA")
    # check if the length is 16 the first two numbers are a 5 and then 1-6. If so, it's a Mastercard
    elif clength == 16 and (ccno[0] == 5 and ccno[1] > 0 and ccno[1] < 6):
        print("MASTERCARD")
    # check if the length is 15 the first two numbers are a 3 and a 4 or 7. If so, it's an AMEX
    elif clength == 15 and (ccno[0] == 3 and (ccno[1] == 4 or ccno[1] == 7)):
        print("AMEX")
    else:
        print("INVALID")  # Else it's invalid
else:
    print("INVALID")  # Else it didn't pass the checksum and is invalid