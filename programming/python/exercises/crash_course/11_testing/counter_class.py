#!/usr/bin/python3
# counter_class.py
# Define a simple counter class. This class is intended to be used in an example
# showing how to write unit tests for a class, and is not intended to be
# particularly useful or interesting in its own right.


class Counter:
    def __init__(self):
        """Initializes a new counter with a count of 0."""
        self._count = 0

    def increment(self):
        """Increases the count by 1."""
        self._count += 1

    def count(self):
        """Returns the count."""
        return self._count
