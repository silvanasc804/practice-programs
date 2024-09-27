#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string substitute(string word, string k);
int not_alphabetic(string key);
int not_each_letter(string key);

int main(int argc, string argv[])
{
    string k;
    // The user should provide a single argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        k = argv[1];
    }

    if (strlen(k) != 26)
    {
        // not containing 26 characters
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (not_alphabetic(k) == 1)
    {
        // containing any character that is not an alphabetic character
        printf("Key must contain only alphabetic characters.\n");
        return 1;
    }
    else if (not_each_letter(k) == 1)
    {
        // not containing each letter exactly once
        printf("Key must contain each letter once.\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: %s\n", substitute(text, k));
    return 0;
}

string substitute(string word, string k)
{
    // Substitute each letter by its encryption
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isupper(word[i]))
        {
            word[i] = toupper(k[word[i] - 'A']);
        }
        else if (islower(word[i]))
        {
            word[i] = tolower(k[word[i] - 'a']);
        }
    }
    return word;
}

int not_alphabetic(string key)
{
    // if any character is not alphabetic return 1
    for (int i = 0, l = strlen(key); i < l; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int not_each_letter(string key)
{
    // to know how many letters are different
    char letters[26];
    for (int i = 0; i < 27; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (key[i] == letters[j])
            {
                return 1;
            }
        }
        letters[i] = key[i];
    }
    return 0;
}
