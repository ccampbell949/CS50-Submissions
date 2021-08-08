from csv import reader, DictReader
from sys import argv, exit

if len(argv) != 3:  # command line arguments must equal 3. If not, display error
    print("usage error, dna.py sequence.txt database.csv")
    exit()
    
# read the file dna sequence file
with open(argv[2]) as dna_sequence:
    dna_read = reader(dna_sequence)
    for row in dna_read:
        dnalist = row

# store row from dna file as a string
dnastring = dnalist[0]
# create dictionary to contain the different dna sequences
sequencedict = {}

# extract the sequences from the database into a list
with open(argv[1]) as data_sequence:
    people = reader(data_sequence)
    for row in people:
        dnaSequences = row
        dnaSequences.pop(0)
        break

# copy the list into a dictionary where the genes are the keys
for item in dnaSequences:
    sequencedict[item] = 1

# iterate through dna sequence. Count any repetitions
for key in sequencedict:
    l = len(key)
    Max = 0
    temp = 0
    for i in range(len(dnastring)):
        # skips to end of counted sequence
        while temp > 0:
            temp -= 1
            continue

        # if dna segment matches the key & repetition, start counting
        if dnastring[i: i + l] == key:
            while dnastring[i - l: i] == dnastring[i: i + l]:
                temp += 1
                i += l

            # compare values to the previous longest sequence. If longer, write over
            if temp > Max:
                Max = temp

    # store the longest sequences from the file in the dictionary using the matching key
    sequencedict[key] += Max

# loop through the database of people. Each one to be treated as a dictionary to compare to sequences
with open(argv[1], newline='') as people_data:
    people = DictReader(people_data)
    for person in people:
        match = 0
        # compare the sequences all people in dictionary and print name if there's a match
        for dnastring in sequencedict:
            if sequencedict[dnastring] == int(person[dnastring]):
                match += 1
        if match == len(sequencedict):
            print(person['name'])
            exit()

    print("No match")
