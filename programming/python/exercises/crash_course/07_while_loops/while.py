#!/usr/bin/python3
# while.py
# Compute the sum of numbers entered by a user.

print('This program computes the sum of the numbers that you enter.')
s = 0
while True:
    x = int(input('Enter the next number or 0 if done: '))
    if x == 0:
        break
    s += x

print(f'The sum of the numbers that you entered is {s}.')
