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

    creditno = get_long("Enter the credit card number: ");
    creditno2 = creditno;

        while (creditno2 > 0)
        {
            creditno2 = creditno2/10;
            currentNo = (creditno2 % 10)*2;
            printf("Credit Left: %ld\n", creditno2);

            if (currentNo>9){
                product = (currentNo % 10) + (currentNo / 10);
                currentNo = product;
                printf("Product: %i\n", product);
            }

            checksum += currentNo;

            creditno2 = creditno2/10;
            counter=counter+2;
            printf("Current No: %i\n", currentNo);
            printf("Checksum: %i\n", checksum);


}