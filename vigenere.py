

import cs50
import sys
# check there is only one argv and it is alphabetic
if len(sys.argv) != 2 or not sys.argv[1].isalpha():
    print("Usage: python vigenere.py k")
    sys.exit(1)
# prompt the user for a plaintext
p = cs50.get_string("plaintext: ")
# save the key user inputted
k = sys.argv[1]
# set counter to iterate over the key
j = 0
# prepare to print output
print("ciphertext: ", end="")
# iterate over each character from input p and over each character in key (using j)
for char in p:
    # check if each character in input is alphabetic
    if char.isalpha():
        # check if it is an uppercase char and shift it by corresponding key
        if char.isupper():
            key = k[j].upper()
            char = chr((ord(char) + (ord(key))) % 26 + ord('A'))
            j = (j + 1) % len(k)
            # print char without \n
            print(char, end="")
        # check if it is a lowercase char and shift it by corresponding key
        if char.islower():
            key = k[j].lower()
            char = chr((ord(char) - ord('a') + (ord(key) - ord('a'))) % 26 + ord('a'))
            j = (j + 1) % len(k)
            # print char without \n
            print(char, end="")
    # otherwise, print char
    else:
        print(char, end="")
# print \n
print("", end="\n")

