#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long creditno = 0;
    long creditno2 = 0;
    int counter = 0;
    int currentNo = 0;
    int product = 0;
    int checksum = 0;

    creditno = get_long("Enter the credit card number: ");
    creditno2 = creditno;

    int index = floor(log10(creditno)) + 1;
    printf("%d\n", index);
    int creditnos[index];
    for (int i = index; i > 0; i--)
    {
        creditnos[index-i] = (int)(creditno/pow(10,i-1)) % 10;
        printf("%i : %i\n", index-i, creditnos[index-i]);
    }



  /*  while (creditno2 > 0)
    {
        creditno2 = creditno2 / 10;
        counter = counter + 1;
        currentNo = (creditno2 % 10) * 2;

        if (currentNo > 9)
        {
            product = (currentNo % 10) + (currentNo / 10);
            currentNo = product;
        }

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