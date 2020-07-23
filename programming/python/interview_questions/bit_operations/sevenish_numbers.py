#!/usr/bin/python3
# sevenish_numbers.py
# A sevenish number is a that can be written as the sum of distinct
# nonnegative-integer powers of 7. The first few sevenish numbers are
#    1 = 7^0,
#    7 = 7^1,
#    8 = 7^0 + 7^1, and
#   49 = 7^2.
# Write a function that, given a positive integer n, returns the nth sevenish
# number.
# DCP17.4;

import math


def sevenish_number_brute_force(n):
    sevenish_numbers = {0}
    power_of_seven = 1
    while len(sevenish_numbers) <= n:
        sevenish_numbers |= {
            sevenish_number + power_of_seven
            for sevenish_number in sevenish_numbers
        }
        power_of_seven *= 7
    return sorted(sevenish_numbers)[n]


def sevenish_number_bits(n):
    # Let the binary representation of n be
    #   b0 * 2^0 + b1 * 2^1 + ... + bk * 2^k.
    # The nth sevenish number is
    #   b0 * 7^0 + b1 * 7^1 + ... + bk * 7^k.
    s = 0
    power_of_seven = 1
    while n > 0:
        if (n & 1) == 1:
            s += power_of_seven
        n >>= 1
        power_of_seven *= 7

    return s


def main():
    tests = (
        (1, 1),
        (2, 7),
        (3, 8),
        (4, 49),
        (5, 50),
        (6, 56),
        (7, 57),
        (8, 343),
        (9, 344),
        (10, 350),
        (11, 351),
        (12, 392),
        (13, 393),
        (14, 399),
        (15, 400),
    )
    sols = (
        sevenish_number_brute_force,
        sevenish_number_bits,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print('Test {}:'.format(test_index))
        print('n = {}'.format(data))
        print('want = {}'.format(want))

        for sol in sols:
            got = sol(data)
            if got == want:
                print('{} passes'.format(sol.__name__))
                correct_counts[sol] += 1
            else:
                print('{} fails; got = {}'.format(sol.__name__, got))

        print()

    print('Summary:')
    for sol in sols:
        print('{}: {} of {} correct'.format(
            sol.__name__,
            correct_counts[sol],
            len(tests),
        ))


if __name__ == '__main__':
    main()
