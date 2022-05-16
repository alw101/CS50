#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask for Name
    string name = get_string("What's your name?\n");
    //Printout Hello, <name>
    printf("Hello, %s\n", name);
}