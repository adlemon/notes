#!/usr/bin/python3
# random_example.py
# Simple example of the standard random module.

import random

print('random.randint(1, 10):')
for _ in range(5):
    print(random.randint(1, 10))

print("\nrandom.choice(['a', 'b', 'c', 'd', 'e']):")
for _ in range(3):
    print(random.choice(['a', 'b', 'c', 'd', 'e']))
