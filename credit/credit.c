#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long creditno = get_long("Enter the credit card number: ");
    long creditno2 = creditno;
    int counter = 0;

    while (creditno2 > 0)
    {
        creditno2 = creditno2/10;
        counter++;
    }

    int creditNos[counter];



}