#!/usr/bin/python3
# square_function_test.py
# Unit tests for the square_function module.

import unittest

import square_function


class TestSquare(unittest.TestCase):
    """Tests for the function 'square' in the module 'square_function'."""
    def test_zero(self):
        self.assertEqual(square_function.square(0), 0)

    def test_positive_1(self):
        self.assertEqual(square_function.square(1), 1)

    def test_negative_1(self):
        self.assertEqual(square_function.square(-1), 1)

    def test_positive_2(self):
        self.assertEqual(square_function.square(2), 4)

    def test_negative_2(self):
        self.assertEqual(square_function.square(-2), 4)


if __name__ == '__main__':
    unittest.main()
