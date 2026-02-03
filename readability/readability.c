#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int CalculateGrade(string Text);
int CountLetters(string Text);
int CountWords(string Text);
int CountSentences(string Text);

int main(void)
{
    string Texts = get_string("Text: ");
    int GradeIndex = CalculateGrade(Texts);
    if (GradeIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (GradeIndex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", GradeIndex);
    }
}

int CalculateGrade(string Text)
{
    int TotalWords = CountWords(Text);
    int TotalLetters = CountLetters(Text);
    int TotalSentences = CountSentences(Text);
    float AvgLetters = TotalLetters / (TotalWords / 100.0);
    float AvgSentences = TotalSentences / (TotalWords / 100.0);
    int GradeIndex = round(0.0588 * AvgLetters - 0.296 * AvgSentences - 15.8);
    return GradeIndex;
}

int CountLetters(string Text)
{
    int Counter = 0;
    int TextLength = strlen(Text);
    for (int i = 0; i < TextLength; i++)
    {
        if (isalpha(Text[i]))
        {
            Counter++;
        }
    }
    return Counter;
}
int CountWords(string Text)
{
    int Counter = 0;
    int TextLength = strlen(Text);
    for (int i = 0; i < TextLength; i++)
    {
        if (isspace(Text[i]))
        {
            Counter++;
        }
    }
    return Counter + 1;
}
int CountSentences(string Text)
{
    int Counter = 0;
    int TextLength = strlen(Text);
    for (int i = 0; i < TextLength; i++)
    {
        if (Text[i] == '.' || Text[i] == '!' || Text[i] == '?')
        {
            Counter++;
        }
    }
    return Counter;
}
