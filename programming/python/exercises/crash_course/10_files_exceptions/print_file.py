#!/usr/bin/python3
# print_file.py
# Prompt the user for the name of a file, and then print the contents of the
# file.

while True:
    filename = input("Enter the name of the file (or 'q' to quit): ")
    if filename == 'q':
        break

    try:
        with open(filename) as f:
            contents = f.read()
    except FileNotFoundError:
        print(f'Failed to open file for reading: {filename}\n')
    else:
        print(f'{filename}:')
        print(contents)
