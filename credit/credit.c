#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long creditno = 0;
    long creditno2 = 0;
    int counter = 0;
    int currentNo = 0;
    int product = 0;
    int checksum = 0;

   // do
    //{
        creditno = get_long("Enter the credit card number: ");
        creditno2 = creditno;

        while (creditno2 > 0)
        {
            creditno2 = creditno2/10;
            currentNo = (creditno2 % 10)*2;

            if (currentNo>9){
                product = (currentNo % 10) + (currentNo % 100);
                printf("%i\n", product);
            }

            creditno2 = creditno2/10;
            counter=counter+2;
            printf("%i\n", currentNo);
        }
 //   } while ((counter > 16) && (counter < 13) && (counter == 14));

   // printf("%i\n", counter);

}