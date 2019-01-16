from cs50 import get_string
import sys

# variable to save dictionary from the command-line
words = set()


def main():

    # check there is only one argv and it is alphabetic
    if len(sys.argv) != 2:
        print("Usage: python bleep.py dictionary")
        sys.exit(1)

    # save name(path) of a dictionary from command-line and load it
    dictionary = sys.argv[1]

    # load dictionary
    load(dictionary)

    # get input from the user
    message = get_string("What message would you like to censor? ")

    # split user input into separate words and make them lowercase
    splitMessage = message.split(' ')

    # set a counter to 0 (we need a counter to print end of line after the last word)
    counter = 0

    # for every element in splitMessage
    for element in splitMessage:
        # if element is in dictionary
        if element.lower() in words:
            # print * instead of each letter in an element
            for letter in range(len(element)):
                print('*', end="")
            counter += 1
        # else
        else:
            # if it is the first element and it is not uppercase, print it
            if counter == 0 and element.islower():
                print(element.capitalize(), end="")
                counter += 1
            # otherwise, print element
            else:
                print(element, end="")
                counter += 1
        # if counter is less than length of split element
        if counter < len(splitMessage):
            # print whitespace after the word
            print(' ', end="")
        # otherwise, print end of line
        else:
            print()

# define a function to load dictionary


def load(dictionary):
    # Load dictionary into memory, returning true if successful else false"""
    file = open(dictionary, "r")
    for line in file:
        words.add(line.rstrip("\n"))
    file.close()
    return True


if __name__ == "__main__":
    main()
