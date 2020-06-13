#!/usr/bin/python3
# print_even.py
# Print the even numbers in a for loop and their sum.

s = 0
for i in range(11):
    if (i % 2) == 1:
        continue

    print(i)
    s += i

print(f'The sum of the printed numbers is {s}.')
