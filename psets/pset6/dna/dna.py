import sys
import csv

# Determine files to open
if len(sys.argv) != 3:
    print("Usage: dna.py [database.csv] [sequences.txt]")
    sys.exit(0)

# Read database to memory
with open(sys.argv[1]) as csvfile:
    reader = csv.DictReader(csvfile)
    database = []
    for row in reader:
        database.append(row)
headers = list(database[0].keys())
# To get specific value, dict(database[rownum][headers[columnnum]])

# Read sequence into memory
with open(sys.argv[2]) as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        sequence = row[0]
        

# Derermine occurances in a row of STR with sequence
matches = []
for i in range(len(headers)):
    count = []
    biggest = 0
    for j in range(len(sequence)):
        if sequence[j:j+len(headers[i])] == headers[i]:
            count.append(1)
            if j >= len(headers[i]):
                if count[j-len(headers[i])] > 0:
                    count[j] += count[j-len(headers[i])]
        elif j >= len(headers[i]):
            if count[j-len(headers[i])] > biggest:
                biggest = count[j-len(headers[i])]
            count.append(0)
        else:
            count.append(0)
    matches.append(biggest)


# Dermine matches with database
for row in range(len(database)):
    count = 0
    for i in range(1, len(headers), 1):
        if int(database[row][headers[i]]) == int(matches[i]):
            count += 1
    if count == len(headers)-1:
        print(database[row]['name'])
        sys.exit(0)
        
print("No match")