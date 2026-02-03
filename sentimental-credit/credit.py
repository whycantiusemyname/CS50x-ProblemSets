while True:
    CardNumber = input("Number: ")
    ReversedCardNumber = CardNumber[::-1]
    NumberLength = len(CardNumber)
    if NumberLength == 13 or NumberLength == 15 or NumberLength == 16:
        break
    else:
        print("INVALID")
        break

Counter, CheckSum = 0, 0
VISALength = [13, 16]
MASTERCARDLength = 16
AMEXLength = 15
VISAStartDigit = "4"
MASTERCARDStartDigit = ["51", "52", "53", "54", "55"]
AMEXStartDigit = ["34", "37"]

for Num in ReversedCardNumber:
    # second-to-last product Sum
    if Counter % 2 != 0:
        Product = str(int(Num) * 2)
        for Ditgit in Product:
            CheckSum += int(Ditgit)
    else:
        CheckSum += int(Num)
    Counter -= 1
if CheckSum % 10 == 0:
    StartDigit = CardNumber[:2]
    if CardNumber[0] == VISAStartDigit and NumberLength in VISALength:
        print("VISA")
    elif StartDigit in MASTERCARDStartDigit and NumberLength == MASTERCARDLength:
        print("MASTERCARD")
    elif StartDigit in AMEXStartDigit and NumberLength == AMEXLength:
        print("AMEX")
    else:
        print("INVALID")
else:
    print("INVALID")
