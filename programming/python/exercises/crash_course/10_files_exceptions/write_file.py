#!/usr/bin/python3
# write_file.py
# Demonstrates writing a file.

filename = 'write_file_out.txt'


def display_file(filename):
    """Displays the name of a file and its contents."""
    print(filename)
    print(80 * '=')
    with open(filename) as f:
        print(f.read()[:-1])
    print(80 * '=')


# Clear a file and write some text in it.
with open(filename, 'w') as f:
    f.write('Line 1\n')
display_file(filename)

# Append some text to the end of a file without clearing it.
with open(filename, 'a') as f:
    f.write('Line 2\n')
print()
display_file(filename)
