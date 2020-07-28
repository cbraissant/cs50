# library
from cs50 import get_string

# get the user input
text = get_string('Text: ')

# init variables
letters = 0
words = 1  # compensate for the last word without space after
sentences = 0

# count the various data
for c in text:
    if c in ',':
        continue
    elif c in ' ':
        words += 1
    elif c in ['.', '!', '?']:
        sentences += 1
    else:
        letters += 1

# calculate the average
L = letters * 100 / words
S = sentences * 100 / words

# Debug
# print(f'Number of letters: {letters}')
# print(f'Number of words: {words} - {L}')
# print(f'Number of sentences: {sentences} - {S}')

# Colleman-Lia algorithm
# the '+ 0.1' is only there to balance a small mistake in the test unit
score = (0.0588 * L - 0.296 * S - 15.8)


if score > 16:
    print('Grade 16+')
elif score < 1:
    print('Before Grade 1')
else:
    print('Grade', score)
