#include <stdlib.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int count_key_character = 0; // chech all letters
    int count_repeated_character = 0; // no repeated chars

    if (argc == 2) // 1 cmd line arg
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++) // must be all letters
        {
            if (isalpha(argv[1][i]))
            {
                count_key_character += 1;
            }
        }
        for (int j = 0, n = strlen(argv[1]); j < n; j++) // must not contain repeated chars
        {
            for (int k = j + 1; k < n; k++)
            {
                if (tolower(argv[1][j]) == tolower(argv[1][k]))
                {
                    count_repeated_character++;
                }
            }
        }
        if (strlen(argv[1]) != 26) // must be 26 characters
        {
            printf("Key must contain 26 chars.\n");
            return 1;
        }
        else if (count_key_character != strlen(argv[1])) // must be all chars
        {
            printf("Key must only contain alphabets.\n");
            return 1;
        }
        else if (count_repeated_character != 0) // must not contain repeated chars
        {
            printf("Key must not contain repeated chars.\n");
            return 1;
        }
        else
        {
            string plain = get_string("plaintext: "); // get plaintext from user
            printf("ciphertext: ");
            for (int w = 0, x = strlen(plain); w < x; w++)
            {
                if (isalpha(plain[w]) && isupper(plain[w])) // if chars are letters & uppercase
                {
                    int upper = (plain[w] - 65);
                    printf("%c", toupper(argv[1][upper]));
                }
                else if (isalpha(plain[w]) && islower(plain[w])) // if chars are letters & lower
                {
                    int lower = (plain[w] - 97);
                    printf("%c", tolower(argv[1][lower]));
                }
                else
                {
                    printf("%c", plain[w]); // print as is, if chars are not letter
                }
            }
            printf("\n"); // print ciphertext with newline
            return 0;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

