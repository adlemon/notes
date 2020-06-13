#!/usr/bin/python3
# conditionals.py
# Demonstrates basic use of conditionals.

# if statements.
for predicate in (True, False):
    if predicate:
        print(f'evaluate the consequence if the predicate is {predicate}')

# if-else statements.
print()
for predicate in (True, False):
    if predicate:
        print('evaluate the consequence if the predicate is {predicate}')
    else:
        print('evaluate the alternative if the predicate is True?')

# if-elif-else statements.
print()
for i in range(0, 5):
    print(f'i = {i}: ', end='')
    if i == 1:
        print('one')
    elif i == 2:
        print('two')
    elif i == 3:
        print('three')
    else:
        print('not one, two, or three')

# Comparison operators.
print()
comparison_operators = ('==', '!=', '<', '<=', '>', '>=')
for operator in comparison_operators:
    for x in range(-1, 2):
        for y in range(-1, 2):
            expr = f'{x} {operator} {y}'
            print(f'{expr} => {eval(expr)}')

# Boolean operators.
print()
boolean_operators = ('and', 'or')
for operator in boolean_operators:
    for x in (False, True):
        for y in (False, True):
            expr = f'{x} {operator} {y}'
            print(f'{expr} => {eval(expr)}')

# Check membership in a list.
print()
for x in (1, 5):
    expr = f'{x} in [0, 1, 2]'
    print(f'{expr} => {eval(expr)}')

# List used as predicate.
print()
for lst in ([], [1], [1, 2]):
    print(f'lst = {lst}:', end=' ')
    if lst:
        print('counts as True')
    else:
        print('counts as False')
