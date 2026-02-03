#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define N 7

int CalculateScore(string Answer, string ScoreList[], int Points[]);
int main(void)
{
    string LetterList[N] = {"AEILNORSTU", "DG", "BCMP", "FHVWY", "K", "JX", "QZ"};
    int LetterPoints[N] = {1, 2, 3, 4, 5, 8, 10};
    string Answer1 = get_string("Player 1: ");
    string Answer2 = get_string("Player 2: ");
    int AnswerScore1 = CalculateScore(Answer1, LetterList, LetterPoints);
    int AnswerScore2 = CalculateScore(Answer2, LetterList, LetterPoints);
    if (AnswerScore1 > AnswerScore2)
    {
        printf("Player 1 wins!");
    }
    else if (AnswerScore1 == AnswerScore2)
    {
        printf("Tie!");
    }
    else
    {
        printf("Player 2 wins!");
    }
}

int CalculateScore(string Answer, string ScoreList[], int Points[])
{
    int FinalScore = 0;
    int AnswerLength = strlen(Answer);
    // Choose a String
    for (int ScoreString = 0; ScoreString < N; ScoreString++)
    {
        int ScoreStringLength = strlen(ScoreList[ScoreString]);
        // Choose a Letter
        for (int ScoreLetter = 0; ScoreLetter < ScoreStringLength; ScoreLetter++)
        {
            // Find the letter in answer one by one
            for (int AnswerLetter = 0; AnswerLetter < AnswerLength; AnswerLetter++)
            {
                if (toupper(Answer[AnswerLetter]) == ScoreList[ScoreString][ScoreLetter])
                {
                    FinalScore += Points[ScoreString];
                }
            }
        }
    }
    return FinalScore;
}
