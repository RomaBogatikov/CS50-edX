import cs50
# prompt the user to input the amount of change owed (non-negative number)
while True:
    amount = cs50.get_float("Change owed: ")
    if amount >= 0:
        break
# calculate the amount in cents
cents = amount * 100

# set counter of coins to 0
count = 0
# while cents >= 25 (and so on) increment the counter by 1, and substract the coin value (25, 10, 5, or 1) from cents
while cents >= 25:
    count += 1
    cents -= 25

while cents >= 10:
    count += 1
    cents -= 10

while cents >= 5:
    count += 1
    cents -= 5

while cents >= 1:
    count += 1
    cents -= 1

print(count)