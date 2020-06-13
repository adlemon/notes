#!/usr/bin/python3
# read_file.py
# Demonstrates different ways of reading a file.

# Read the entire contents of a file as a string.
print('Read the entire contents of a file as a string:')
with open('read_file_in.txt') as f:
    file_contents = f.read().rstrip()
print(file_contents)

# Read a file line-by-line.
print('\nRead a file line by line')
with open('read_file_in.txt') as f:
    for line in f:
        print(f'line = {line.rstrip()}')

# Read the lines of a file into a list of strings.
print('\nRead the lines of a file into a list of strings:')
with open('read_file_in.txt') as f:
    lines = f.readlines()
for line in lines:
    print(f'line = {line.rstrip()}')
