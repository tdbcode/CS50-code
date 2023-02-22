#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long creditno = 0;
    long creditno2 = 0;
    int counter = 0;

    do
    {
        creditno = get_long("Enter the credit card number: ");
        creditno2 = creditno;

        while (creditno2 > 0)
        {
            creditno2 = creditno2/10;
            counter++;
        }
    } while ((counter > 16) && (counter < 13) && (counter == 14));

    printf("%i\n", counter);

   // while(counter>16)

   // int creditNos[counter];

}