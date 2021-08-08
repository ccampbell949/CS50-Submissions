from cs50 import get_string

text = get_string("Enter Text: ")  # input text from user

words = 0  # set counters to 0
sentences = 0
letters = 0
i = 0
length = len(text)

while i < length:
    
    if text[i].isalpha():  # count letters. if character in array is alphabetical
        letters += 1  # add 1
    
    if (i == 0 and text[i] != " ") or (i != length and text[i] == " " and text[i + 1] != " "):  # spaces between words
        words += 1  # add 1
        
    if text[i] == "." or text[i] == "?" or text[i] == "!":  # punctuation at the end of sentences
        sentences += 1  # add 1
    
    i += 1
    
# Calculate using formula
L = (letters / words) * 100
S = (sentences / words) * 100
grade = round((0.0588 * L) - (0.296 * S) - 15.8)

if grade < 1:
    print("Before Grade 1")
    
elif grade >= 16:
    print("Grade 16+")
    
else:
    print(f"Grade {grade}")
