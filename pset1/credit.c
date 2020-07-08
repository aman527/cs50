#include <stdio.h>
#include <math.h>
#include <string.h>
#include <cs50.h>

int get_num_digits(long card_num)
{
    // Get the number of digits in the card
    int digits = 0;
    long card_num_helper = card_num;
    while (card_num_helper > 1)
    {
        card_num_helper /= 10.0;
        digits += 1;
    }
    return digits;
}
long get_digit(long card_num, long position)
{
    // Get the digit at the specified position,
    // with position 0 being the rightmost digit
    float exponent = (int)round(position);
    long power_of_10 = (long) pow(10.0, exponent);
    long remainder = card_num / power_of_10;
    long digit = remainder % 10;
    return digit;
}
long sum_digits(long product)
{
    // Sum the digits of a (one- or two-digit) long
    if ((product / 10.0) >= 1.0)
    {
        long ones_digit = product % 10;
        long sum = ones_digit + 1;
        return sum;
    }
    else
    {
        return product;
    }
}
bool is_valid_card(long card_num)
{
    long running_sum = 0;
    int num_digits = get_num_digits(card_num);
    // Iterate over the digits of the card, applying the algorithm
    for (int i = 0; i < num_digits; i++)
    {
        long digit = get_digit(card_num, i);
        // If the digit is in an odd place, multiply it by two
        // And add the sum of the resulting digits to the running total
        if (i % 2 == 1)
        {
            long sum = sum_digits(digit * 2);
            running_sum += sum;
        }
        // Otherwise, just add the digit
        else
        {
            running_sum += digit;
        }
    }
    // Validate the final sum
    if (running_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
string get_output(long card_num)
{
    /** Get the output message that should be displayed **/
    string output;
    // First, find out how many digits are in the card
    int num_digits = get_num_digits(card_num);
    // Next, get the first digit in the card
    int first_digit = get_digit(card_num, num_digits - 1);
    // And the second digit
    int second_digit = get_digit(card_num, num_digits - 2);

    // Check if the card is a valid Visa card
    // The first digit must be 4 and there can eithe be 13 or 16 digits
    if (first_digit == 4 && (num_digits == 13 || num_digits == 16))
    {
        output = "VISA\n";
    }
    // Check if the card is a valid Amex card
    // There must be 15 digits and it must start with 34 or 37
    else if (num_digits == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7))
    {
        output = "AMEX\n";
    }
    // Check if the card is a valid Mastercard card
    // There must be 16 digits and the first two can be 51, 52, 53, 54, or 55
    else if (num_digits == 16 && first_digit == 5 && (second_digit > 0 && second_digit < 6))
    {
        output = "MASTERCARD\n";
    }
    else
    {
        output = "INVALID\n";
    }
    return output;
}
int main(void)
{
    long card_num = get_long("Number: ");
    string output = get_output(card_num);
    if (strcmp(output, "INVALID\n") == 0)
    {
        printf("%s", output);
        return 0;
    }
    bool valid = is_valid_card(card_num);
    if (valid)
    {
        printf("%s", output);
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }

}