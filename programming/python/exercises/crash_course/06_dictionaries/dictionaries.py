#!/usr/bin/python3
# dictionaries.py
# Illustrates the use of dictionaries.

# Create a dictionary literal.
d = {'one': 1, 'two': 2, 1: ('one', 'unus'), 2: ('two', 'duo')}
print(d)

# Access and modify dictionary entries.
print()
d = {1: 'one', 2: 'two', 3: 'tree'}
d[3] = 'three'
for key in d:
    print(f'key = {key}, value = {d[key]}')

# Get a value from a dictionary using a default value for missing keys.
print()
d = {1: 'one', 2: 'two', 3: 'three'}
for key in (1, 4):
    expr = f'd.get({key}, None)'
    print(f'{expr} => {eval(expr)}')

# Delete keys.
print()
d = {'one': 1, 'two': 2, 'tree': 3}
del d['tree']
d['three'] = 3
print(d)

# Loop through the key-value pairs in a dictionary.
print()
for key, value in {'one': 1, 'two': 2, 'three': 3}.items():
    print(f'key = {key}, value = {value}')

# Check if a dictionary contains a key.
print()
d = {'one': 1, 'two': 2, 'three': 3}
for key in ('one', 'four'):
    expr = f"'{key}' in d, '{key}' not in d"
    print(f'{expr} => {eval(expr)}')

# Get the list of values in a dictionary.
print()
print('values =', list({'one': 1, 'two': 2, 'three': 3}.values()))
