#!/usr/bin/python3
# divide_ints.py
# Repeatedly prompt the user for pairs of integers, and print the results of
# dividing the first integer in the pair by the second.

while True:
    try:
        i1 = input("Enter an integer ('q' to quit): ")
        if i1 == 'q':
            break
        i1 = int(i1)

        i2 = int(input('Enter an integer: '))

        d = i1 / i2
    except ValueError:
        print('Invalid integer.\n')
    except ZeroDivisionError:
        print('Cannot divide by zero.\n')
    else:
        print(f'{i1} / {i2} => {d}\n')
