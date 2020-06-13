#!/usr/bin/python3
# counter_class_test.py
# Unit tests for the counter_class module.

import unittest

import counter_class


class TestCounterClass(unittest.TestCase):
    """Unit tests for the 'Counter' class in the module 'counter_class'."""
    def setUp(self):
        """Create a counter object to use in tests."""
        self.counter = counter_class.Counter()

    def test_init(self):
        self.assertEqual(self.counter.count(), 0)

    def test_increment_1(self):
        self.counter.increment()
        self.assertEqual(self.counter.count(), 1)

    def test_increment_10(self):
        for _ in range(10):
            self.counter.increment()
        self.assertEqual(self.counter.count(), 10)

    def test_increment_10_with_count_calls(self):
        for _ in range(10):
            self.counter.increment()
            self.counter.count()
        self.assertEqual(self.counter.count(), 10)


if __name__ == '__main__':
    unittest.main()
