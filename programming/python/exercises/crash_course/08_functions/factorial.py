#!/usr/bin/python3
# factorial.py
# Print a table of factorials.


def factorial(n):
    if n == 0:
        return 1
    return n * factorial(n - 1)


for n in range(10):
    print(f'factorial({n}) = {factorial(n)}')
