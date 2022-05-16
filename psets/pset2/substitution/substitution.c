#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int validate(int length, string key);
int encrypt(string input, string key);

int main(int argc, string argv[])
{
    //Validate
    int end = validate(argc, argv[1]);
    if (end == 1)
    {
        return 1;
    }

    //Get text to be encrypted
    string plaintext = get_string("plaintext: ");

    //Encrypt text and print it
    encrypt(plaintext, argv[1]);
    return 0;
}

int validate(int length, string key)
{
    //Check one key is present
    if (length != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        int sum = 0;
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            //Check all characters are letters
            if ((key[i] >= 65 && key[i] <= 90) || (key[i] >= 97 && key[i] <= 122))
            {
                //Check no letter is repeated
                if ((key[i] >= 65 && key[i] <= 90))
                {
                    sum = sum + (key[i] - 64);
                }
                else
                {
                    sum = sum + (key[i] - 96);
                }
            }
            else
            {
                printf("Only letters in key\n");
                return 1;
            }
        }

        //Outcome
        if (sum != 351 || 0 == strcmp("BBCCEFGHIJKLMNOPQRSTUVWXYZ", key))
        {
            printf("Key must contain 26 letters that don't repeat themselves\n");
            return 1;
        }
        else
        {
            return 0;
        }
        printf("Sum: %i", sum);
    }
}

int encrypt(string input, string key)
{
    printf("ciphertext: ");

    //change each char of input to encrypted output
    char output[strlen(input) - 1];
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        //Check to see if a letter
        if ((input[i] >= 65 && input[i] <= 90) || (input[i] >= 97 && input[i] <= 122))
        {
            //Encrypt correctly if upper or lower case
            if (input[i] >= 65 && input[i] <= 90)
            {
                output[i] = toupper(key[(int)input[i] - 65]);
            }
            else
            {
                output[i] = tolower(key[(int)input[i] - 97]);
            }
        }
        else
        {
            output[i] = input[i];
        }

        printf("%c", output[i]);
    }
    printf("\n");
    return 0;
}

