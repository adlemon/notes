#!/usr/bin/python3
# functions_and_lists.py
# Demonstrates how a function modifies list arguments.


def f(lst, x):
    lst.append(x)


lst = []
for x in range(1, 6):
    f(lst, x)
    print(f'lst = {lst}')
