
def main():
    Texts = input("Text: ")
    GradeIndex = CalculateGrade(Texts)
    if GradeIndex < 1:
        print("Before Grade 1")
    elif GradeIndex >= 16:
        print("Grade 16+")
    else:
        print("Grade",GradeIndex)


def CalculateGrade(Text):
    TotalWords = Text.count(" ") + 1
    TotalLetters = 0
    for Letter in Text:
        if Letter.isalpha():
            TotalLetters+=1
    TotalSentences = Text.count(".") + Text.count("!") + Text.count("?")
    AvgLetters = TotalLetters / (TotalWords / 100.0)
    AvgSentences = TotalSentences / (TotalWords / 100.0)
    GradeIndex = int(0.0588 * AvgLetters - 0.296 * AvgSentences - 15.8 + 0.5)
    return GradeIndex


main()
