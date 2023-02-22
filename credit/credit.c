#include <cs50.h>
#include <stdio.h>
#include <math.h>

int getLength(long n);

int main(void)
{
    long creditno = 1;
    long creditno2 = 0;
    int length = 0;
    int currentNo = 0;
    int product = 0;
    int checksum = 0;

    int ccno[16];

    creditno = get_long("Enter the credit card number: ");

    length = getLength(creditno);
    printf("Length: %i\n ", length);

    if (length < 13 || length > 16 || length == 14)
    {
        goto INVALID;
    }

    printf("Length: %i\n ", length);

    creditno2 = creditno;
    for (int c = length - 1; c > -1; c--)
    {
        currentNo = creditno2 % 10;
        creditno2 = creditno2 / 10;
        ccno[c] = currentNo;
    }

    for (int a = length - 1; a > 0 ; a = a - 2)
    {
        currentNo = ccno[a - 1] * 2;
        if (currentNo > 9)
        {
            product = (currentNo % 10) + (currentNo / 10);
            currentNo = product;
        }

        checksum += currentNo;
    }

    for (int a = length - 1; a > 0 ; a = a - 2)
    {
        currentNo = ccno[a];
        checksum += currentNo;
    }

    if ((checksum % 10) == 0)
    {
        if (((length == 13) || length == 16) && (ccno[0] == 4))
        {
            printf("VISA\n");
        }
        else if (((length == 16) && (ccno[0] == 5)) && ((ccno[0] == 5) && (ccno[1] > 0) && (ccno[1] < 6)))
        {
            printf("Mastercard\n");
        }
        else if ((length == 15) && ((ccno[0] == 3) && ((ccno[1] == 4) || (ccno[1] == 7))))
        {
            printf("AMEX\n");
        }
        else
        {
            goto INVALID;
        }
    }
    else
    {
INVALID:
        printf("INVALID\n");
    }

}

int getLength(long n)
{
    long number = n;
    int llength = 0;


    while (number > 0)
    {
        number = number / 10;
        llength++;
    }

    return llength;
}