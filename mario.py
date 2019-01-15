import cs50

# prompt the user for half-pyramids' height (should be between 1 and 8 inclusive)
while True:
    height = cs50.get_int("Please, input the half-pyramids's height: ")
    if height >= 1 and height <= 8:
        break
# set a counter of "#" to print to 1
counter = 1
# for every line
for i in range(height):
    # print height-counter spaces
    for k in range(height - counter):
        print(" ", end="")
    # print counter "#"
    for l in range(counter):
        print("#", end="")
    # print 2 spaces
    for m in range(2):
        print(" ", end="")
    # print counter of "#"
    for n in range(counter):
        print("#", end="")
    # increment a counter by 1
    counter += 1
    # print \n
    print()