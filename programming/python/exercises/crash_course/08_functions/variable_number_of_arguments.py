#!/usr/bin/python3
# variable_number_of_arguments.py
# Illustrates a function with a variable number of arguments.


def product(*values):
    p = 1
    for x in values:
        p *= x
    return p


print(f'product(1) = {product(1)}')
print(f'product(1, 2) = {product(1, 2)}')
print(f'product(1, 2, 3) = {product(1, 2, 3)}')
print(f'product(1, 2, 3, 4) = {product(1, 2, 3, 4)}')
print(f'product(1, 2, 3, 4, 5) = {product(1, 2, 3, 4, 5)}')
