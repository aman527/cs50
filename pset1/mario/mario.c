#include <stdio.h>
#include <cs50.h>

// Print out the spaces required to create the pyramid,
// given the height of the pyramid and the current level
void print_spaces(int height, int current_level)
{
    int num_spaces = height - 1 - current_level;
    for (int j = 0; j < num_spaces; j++)
    {
        printf(" ");
    }
}
// Print out the actual hash(es) of the pyramid,
// given the current level
void print_hashes(int current_level)
{
    int num_hashes = current_level + 1;
    for (int j = 0; j < num_hashes; j++)
    {
        printf("#");
    }
}
int main(void)
{
    int height = get_int("Height: ");
    // Check to see if the height is allowed
    if (height < 1 || height > 8)
    {
        main();
    }
    else
    {
        // Build the pyramid
        for (int i = 0; i < height; i++)
        {
            print_spaces(height, i);
            print_hashes(i);
            printf("  ");
            print_hashes(i);
            printf("\n");
        }
    }
}