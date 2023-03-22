#include <cs50.h>
#include <stdio.h>
#include <math.h>

int getLength(long n); // Method to get the length of the credit card number entered

int main(void)
{
    long creditno = 1;
    long creditno2 = 0;
    int length = 0;
    int currentNo = 0;
    int product = 0;
    int checksum = 0;

    int ccno[16]; // Creates array for individual credit card digits

    // User enters credit card
    creditno = get_long("Enter the credit card number: ");
    // Get credit card number length
    length = getLength(creditno);

    // Check if length is a valid entry, if not send to INVALID and end program
    if (length < 13 || length > 16 || length == 14)
    {
        goto INVALID;
    }


    creditno2 = creditno; // Set temp variable for credit card processing into the carry

    // Run a loop backwards to start of array to add numbers in correct order
    for (int c = length - 1; c >= 0; c--)
    {

        currentNo = creditno2 % 10; // Get individual digit (currentNo) to add to array,
        creditno2 = creditno2 / 10; // Remove a single number from the end of temo variable
        ccno[c] = currentNo;        // Add number to array
    }

    // Run a loop to backwards skipping every other number in array for processing
    for (int a = length - 1; a > 0 ; a = a - 2)
    {
        currentNo = ccno[a - 1] * 2;  // Double the current selected number as per the algorithm from second to last digit
        // Check if current number has more than 1 digit, if so then add them together
        if (currentNo > 9)
        {
            product = (currentNo % 10) + (currentNo / 10);
            currentNo = product;
        }

        checksum += currentNo;  // Add updated number to checksum
    }

    // Run a loop to backwards skipping every other number in array for processing
    for (int a = length - 1; a >= 0; a = a - 2)
    {
        currentNo = ccno[a]; // Select the current selected number as per the algorithm from last digit
        checksum += currentNo; // Add number to checksum
    }

    // Check if checksum is valid
    if ((checksum % 10) == 0)
    {
        // If length is 13 or 16 and starting number is 4, then select visa
        if ((length == 13 | length == 16) && (ccno[0] == 4))
        {
            printf("VISA\n");
        }
        // If length is 16 and starting number is 5, with second number between 1-5 then select mastercard
        else if (length == 16 && (ccno[0] == 5 && (ccno[1] > 0 && ccno[1] < 6)))
        {
            printf("MASTERCARD\n");
        }
        // If length is 15 and starting number is 3, with second number as either 4 or 7 then select AMEX
        else if ((length == 15) && ((ccno[0] == 3) && ((ccno[1] == 4) || (ccno[1] == 7))))
        {
            printf("AMEX\n");
        }
        // All other options are invalid
        else
        {
            goto INVALID;
        }
    }
    // Failed checksum, so invalid
    else
    {
INVALID:
        printf("INVALID\n");
    }
}

// Method to get the length of the credit card number entered, passing in credit card number
int getLength(long n)
{
    long number = n;
    int llength = 0;

    // While number is more than 0
    while (number > 0)
    {
        number = number / 10; //Remove a digit
        llength++; // Add one to length
    }

    return llength; // Return length to method call
}