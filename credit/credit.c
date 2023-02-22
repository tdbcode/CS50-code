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
//
    while ((getLength(creditno) < 13) || (getLength(creditno) > 16) || (getLength(creditno) == 14))
    {
        creditno = get_long("Enter the credit card number: ");
    }

    length = getLength(creditno);

    creditno2 = creditno;
    for (int c = 0; c < length; c++)
    {
        currentNo = creditno2 % 10;
        creditno2 = creditno2 / 10;
        ccno[c] = currentNo;
    }

    for (int a = length-1; a > 0 ; a=a-2)
    {
        printf("a: %i\n", a);
        currentNo = ccno[a];
        printf("CurrentNo: %i\n", currentNo);
        if (currentNo > 9)
        {
            product = (currentNo % 10) + (currentNo / 10);
            currentNo = product;
            printf("Product: %i\n", currentNo);
        }
        checksum += currentNo;
        printf("First: %i\n", checksum);

        currentNo = ccno[a-1];
        checksum += currentNo;
       // printf("Second: %i\n", checksum);

    }



    /*




        checksum += currentNo;
        creditno2 = creditno2 / 10;
        counter = counter + 1;
    }

    creditno2 = creditno;

    while (creditno2 > 0)
    {
        currentNo = (creditno2 % 10);
        checksum += currentNo;
        creditno2 = creditno2 / 10;
    }

    if ((checksum % 10) == 0)
    {
        if (counter > 15)
        {
            printf("VISA");
        }
    }
    else
    {
        printf("INVALID\n");
    }*/

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