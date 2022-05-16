from cs50 import get_string

# input
text = get_string("Text: ")

# calculate # or letters 
letters = 0
words = 1
sentences = 0
for char in text:
    if char == " ":
        words += 1
    elif char == "." or char == "!" or char == "?":
        sentences += 1
    elif (ord(char) >= 65 and ord(char) <= 90) or (ord(char) >= 97 and ord(char) <= 122):
        letters += 1
        
# calculate level
L = letters/words * 100
S = sentences/words * 100
grade = round(0.0588 * L - 0.296 * S - 15.8)

# print level
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print("Grade " + str(grade))
