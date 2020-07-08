#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get the user's name
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}