#include <stdio.h>
#include <cs50.h>

int height;

int main(void)
{
    //Get the height value
    do
    {
    height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //make the pyramid
    for (int i = 1; i < height + 1; i++)
    {
        //The following is repeated for each line:
        
        //print spaces on left half
        for (int c = 0; c < height - i; c++)
        {
            printf(" ");
        }
        
        //print # on left half
        for (int c = 0; c < i; c++)
        {
            printf("#");
        }
        
        //print middle space
        printf("  ");

        //print # on right half
        for (int c = 0; c < i; c++)
        {
            printf("#");
        }
        
        //move to a new line
        printf("\n");

    }

}