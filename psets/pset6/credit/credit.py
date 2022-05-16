from cs50 import get_int
import sys

card = get_int("Number: ")

# Check Length
length = len(str(card))
if length < 13 or length > 16:
    print("INVALID")
    quit()

# Checksum
card = str(card)
sum = 0
for i in range(length):
    a = int(card[i])
    if (i % 2 and length % 2) or (not(i % 2) and not(length % 2)):
        a = a * 2
    if a > 9:
        sum += int(str(a)[0]) + int(str(a)[1])
    else:
        sum += a
if (sum % 10) != 0:
    print("INVALID")
    quit()

# Determine Card Type
if card[0] == "3" and length == 15:
    print("AMEX")
elif card[0] == "5" and length == 16:
    print("MASTERCARD")
elif card[0] == "4":
    print("VISA")
else:
    print("INVALID")
    quit()
