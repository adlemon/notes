#!/usr/bin/python3
# sets.py
# Illustrates the usage of sets.

# Create a set literal.
print({1, 2, 3, 3, 2, 1})

# Add to a set.
print()
s = {1, 2, 3}
s.add(4)
print(s)

# Remove from a set.
print()
s = {1, 2, 3, 4}
s.remove(4)
print(s)

# Construct a set from a list.
print()
print(set([1, 2, 3, 3, 2, 1]))
