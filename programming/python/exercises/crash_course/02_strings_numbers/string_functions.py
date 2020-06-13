#!/usr/bin/python3
# string_functions.py
# Demonstrate some basic string functions.

s = '  Hello, world!  '

methods = (
    str.lower,
    str.upper,
    str.title,
    str.rstrip,
    str.lstrip,
    str.strip,
)

print(f's = "{s}"')
for method in methods:
    print(f's.{method.__name__}()',
          (max(len(method.__name__)
               for method in methods) - len(method.__name__) + 1) * ' ',
          f'=> "{method(s)}"',
          sep='')

# Replace one substring with another.
s = 'abc dbce'
print(f"\ns = {s}\ns.replace('bc', 'fg') => {s.replace('bc', 'fg')}")

# Count the number of occurrences of a substring in a string.
print(f"s.count('bc') => {s.count('bc')}")
