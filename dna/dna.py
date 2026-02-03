import csv
import sys


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        print("Usage: ./dna.py .csv .txt")
        sys.exit(0)
    # TODO: Read database file into a variable
    rows = []
    susDict = {}
    with open(sys.argv[1]) as database:
        reader = csv.DictReader(database)
        # TODO: Read DNA sequence file into a variable
        strs = reader.fieldnames[1:]
        for row in reader:
            rows.append(row)
        with open(sys.argv[2]) as DnaData:
            DnaSequence = DnaData.read()
            for strsequence in strs:
                susDict[strsequence] = longest_match(DnaSequence, strsequence)
            CheckFlag = 0
            FoundFlag = 0
            for row in rows:
                for strsequence in strs:
                    if susDict[strsequence] != int(row[strsequence]):
                        CheckFlag = 1
                        break
                if CheckFlag == 1:
                    CheckFlag = 0
                else:
                    FoundFlag = 1
                    print(row["name"])
    if FoundFlag == 0:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
