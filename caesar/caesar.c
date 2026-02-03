#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isint(string a);
string CaesarEncrypt(string PlainText, int Key);

int main(int argc, string argv[])
{
    int Key = 0;
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        if (isint(argv[1]))
        {
            // ensure the value stays in the right range
            Key = (atoi(argv[1]) % 26);
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    string PlainText = get_string("plaintext:  ");
    string CipherText = CaesarEncrypt(PlainText, Key);
    printf("ciphertext: %s\n", CipherText);
    return 0;
}

bool isint(string a)
{
    int Length = strlen(a);
    for (int i = 0; i < Length; i++)
    {
        if (!(isdigit(a[i])))
        {
            return false;
        }
    }
    return true;
}

string CaesarEncrypt(string PlainText, int Key)
{
    int UpperCaseOffset = 65;
    int LowerCaseOffset = 97;
    int TextLength = strlen(PlainText);
    string CipherText = PlainText;
    for (int i = 0; i < TextLength; i++)
    {
        if (isalpha(PlainText[i]))
        {
            if (isupper(CipherText[i]))
            {
                CipherText[i] = ((CipherText[i] - UpperCaseOffset + Key) % 26) + UpperCaseOffset;
            }
            else
            {
                CipherText[i] = ((CipherText[i] - LowerCaseOffset + Key) % 26) + LowerCaseOffset;
            }
        }
    }
    return CipherText;
}
