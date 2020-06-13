#!/usr/bin/python3
# numbers.py
# Illustrate the basic usage of numbers.

numbers = ((1, 2), (2, 1), (1.2, 3.4), (3.4, 1.2))
operators = ('+', '-', '*', '/', '//', '%', '**')

for x, y in numbers:
    print(f'type = {type(x)}')
    for operator in operators:
        expr = f'{x} {operator} {y}'
        print(f'{expr} =>', eval(expr))
    print()
