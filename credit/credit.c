#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int Digits[16];
    int Digit = 0;
    int Length;
        //Length Check
        Digit = 0;
        long CardNumber = get_long("Number: ");
        long Cache = CardNumber;
        while (Cache>0)
        {
        Digits[Digit] = Cache%10;
        Cache = Cache / 10;
        Digit ++;
        }
    int FirstSum = 0 ;
    int SecondSum = 0 ;
    for (int i = 0; i<Digit; i++)
    {
        if (i%2!=0)
        {
            //second-to-last product Sum
            long Product = Digits[i]*2;
            while (Product>0)
            {
                FirstSum = FirstSum + (Product%10);
                Product = Product / 10;
            }
        }
        else
        {
            //product of other numbers
            SecondSum = SecondSum + Digits[i];
        }
    }
    if ((FirstSum + SecondSum) % 10 == 0)
    {
        int StartNum = Digits[Digit-1]*10 + Digits[Digit-2];
        if (Digits[Digit-1] == 4 && (Digit == 13 || Digit == 16))
        {
            printf("VISA\n");
        }
        else if ((StartNum == 51 ||StartNum == 52 ||StartNum == 53 ||StartNum == 54 ||StartNum == 55) && Digit == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((StartNum == 34 || StartNum == 37) && Digit == 15)
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

