#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int const NUM_LETTERS = 26;
int const LOWER_TO_IDX = 97;

bool is_valid(string key);
string make_lower(string key);
bool all_alpha(string key);
bool each_letter_once(string key);
string substitute(string plaintext, string key);

int main(int argc, string argv[])
{
    // Check for the correct number of args
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check whether the key is 26 chars long
    string key = make_lower(argv[1]);
    if (!is_valid(key))
    {
        printf("Invalid key.\n");
        return 1;
    }
    string plaintext = get_string("plaintext: ");
    string ciphertext = substitute(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);
    return 0;

}
string make_lower(string key)
{
    string lower = key;
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        lower[i] = tolower(key[i]);
    }
    return lower;
}
bool all_alpha(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {

        if (isalpha(key[i]) == 0)
        {
            return false;
        }
    }
    return true;
}
bool each_letter_once(string key)
{
    int counts[NUM_LETTERS];
    // initialize all the counts to be zero
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        counts[i] = 0;
    }
    for (int j = 0; j < NUM_LETTERS; j++)
    {
        // Every letter is lowercase, so we can subtract 97
        // from the ASCII to get the index of the char
        int letter = (int) key[j] - LOWER_TO_IDX;
        if (counts[letter] > 0)
        {
            return false;
        }
        counts[letter] = 1;
    }
    return true;
}
bool is_valid(string key)
{
    /** Test whether the given key is valid **/
    // Does it have 26 chars?
    if (strlen(key) != 26)
    {
        return false;
    }
    // Are all the chars alphabetical?
    else if (!all_alpha(key))
    {
        return false;
    }
    // Is each letter used only once?
    else if (!each_letter_once(key))
    {
        return false;
    }
    // If so, the key is valid
    return true;
}
string substitute(string plaintext, string key)
{
    /** Substitute and return the encoded plaintext using the given key **/
    string ciphertext = plaintext;
    strcpy(ciphertext, plaintext);
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char old = plaintext[i];
        char new_;
        if (isalpha(old) == 0)
        {
            ciphertext[i] = old;
            continue;
        }
        // store whether the character was upper
        bool is_upper = false;
        if (isupper(old) != 0)
        {
            is_upper = true;
            old = tolower(old);
        }
        // get the index of the character to substitute
        int idx = (int) old - LOWER_TO_IDX;
        // if the char was originally uppercase, make the new char upper
        if (is_upper)
        {
            new_ = toupper(key[idx]);
        }
        // otherwise, just get the lowercase version
        else
        {
            new_ = key[idx];
        }
        ciphertext[i] = new_;
    }
    return ciphertext;
}