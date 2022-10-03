#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    int sums = 0;
    long creditno = 0;
    int length = 0;
    long copy;
    int firstdigit;
    int lastdigit;
    int seconddig;
    long copy2;


    do
    {
        creditno = get_long("Number: ");
        copy = creditno;
        copy2 = creditno;
    }

    while (creditno < 0);


    // Length of the numbers for validation
    while (copy != 0)
    {

        firstdigit = copy % 10;
        copy /= 10; // First digit of the cc number
        length++;
    }


    // Checksum of the credit Card
    for (int i = 0 ; creditno != 0; i++, creditno /= 10)
    {

        if (i % 2 == 0)
        {
            sums = sums + creditno % 10;
        }

        else
        {
            int digit = (creditno % 10) * 2;
            sums += (digit % 10) + (digit / 10);
        }
    }


    lastdigit = sums % 10;

    // Second digit of any number where length = number's length
    for (int i = 1; i < length ; i++)
    {
        seconddig = copy2 % 10;
        copy2 /= 10;
    }

    if (lastdigit == 0)
    {

        if ((length == 16 || length == 13) && firstdigit == 4)
        {
            printf("VISA\n");
        }

        else if (length == 16 && (seconddig == 1 || seconddig == 2 || seconddig == 3 || seconddig == 4 || seconddig == 5))
        {
            printf("MASTERCARD\n");
        }

        else if (length == 15 && (seconddig == 4 || seconddig == 7))
        {
            printf("AMEX\n");
        }

        else
        {
            printf("INVALID\n");
        }

    }

    else
    {
        printf("INVALID\n");
    }
}