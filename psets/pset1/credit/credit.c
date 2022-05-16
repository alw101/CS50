#include <stdio.h>
#include <cs50.h>

int main(void)
{


    long card = get_long("Number: ");

    //find card length
    int length = 0;
    if (card >= 1000000000000 && card < 10000000000000)
    {
        length = 13;
    }
    if (card >= 100000000000000 && card < 1000000000000000)
    {
        length = 15;
    }
    if (card >= 1000000000000000 && card < 10000000000000000)
    {
        length = 16;
    }
    
    //stop if length wrong
    if (length == 0)
    {
        printf("INVALID\n");
    }
    else
    {
        //Find checksum
        int sum = 0;
        
        //Multiply by 2 and add every other digit starting from the second last
        for (int i = 1; i < (length / 2 + 1); i++)
        {
            //find digit
            long div = 100;
            for (int s = 1; s < i; s++)
            {
                div = div * 100;
            }
            int a = (card % div) / (div / 10);
                
            //multiply digit by 2
            a = a * 2;
               
            //add to others, digit by digit
            if (a > 9)
            {
                sum = sum + (a % 10);
                sum = sum + (a / 10);
            }
            else
            {
                sum = sum + a;
            }
        }
    
        //add remaining digits
        for (int i = 1; i < (length / 2 + 2); i++)
        {
            //find digit
            long div = 10;
            for (int s = 1; s < i; s++)
            {
                div = div * 100;
            }
            int a = (card % div) / (div / 10);
               
            //Add digit
            sum = sum + a;
        }
        
        //Check if card is valid based on checksum 
        if ((sum % 10) == 0)
        {
            //Find first number
            long div = 10;
            for (int s = 1; s < (length - 1); s++)
            {
                div = div * 10;
            }
            int firstNum = card / div;
    
            //If American Express
            if (firstNum == 3)
            {
                //find first 2 numbers
                div = 10;
                for (int s = 1; s < (length - 2); s++)
                {
                    div = div * 10;
                }
                int secondNum = card / div;
                   
                //Check if first 2 numbers are 34 or 37
                if (secondNum == 34 || secondNum == 37)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
               
            //If Mastercard
            if (firstNum == 5)
            {
                //find first 2 numbers
                div = 10;
                for (int s = 1; s < (length - 2); s++)
                {
                    div = div * 10;
                }
                int secondNum = card / div;
                   
                //See if numbers are valid for mastercard
                if (secondNum > 50 && secondNum < 56)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
               
            //If visa
            if (firstNum == 4)
            {
                printf("VISA\n");
            }
        }
            
        //If not valid acourding to checksum
        else
        {
            printf("INVALID\n");
        }
    }
}