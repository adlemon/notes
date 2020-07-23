#!/usr/bin/python3
# integer_division_with_primitives.py
# Implement integer division for positive integers using addition, subtraction
# and bit operations.
# DCP17.2;

import random


def integer_division(dividend, divisor):
    return dividend // divisor


def integer_division_primitives(dividend, divisor):
    # Find the most significant bit of the quotient: that is, the largest value
    # of bit such that bit is a power of 2, and bit * divisor <= dividend. We
    # find bit (and bit_times_divisor) by using bit-shift operations to
    # effectively multiply bit and bit_times_divisor by 2 for as long as we can
    # do so without violating the inequality bit * divisor <= dividend.
    bit = 1
    bit_times_divisor = divisor
    while (bit_times_divisor << 1) <= dividend:
        bit <<= 1
        bit_times_divisor <<= 1

    # We now iterate over bits from most to least significant, starting with the
    # most significant bit of the quotient. The loop invariants are
    #   quotient * divisor <= dividend, and
    #   remainder = dividend - quotient * divisor.
    # If bit * divisor >= remainder, then we update quotient and remainder:
    #   quotient <- quotient + bit
    #   remainder <- dividend - (quotient + bit) * divisor
    #              = remainder - bit * divisor.
    # Note that remainder >= 0 after each iteration because we only update
    # quotient and remainder when remainder >= bit * divisor.
    quotient = 0
    remainder = dividend
    while remainder >= divisor:
        if remainder >= bit_times_divisor:
            quotient |= bit
            remainder -= bit_times_divisor
        bit >>= 1
        bit_times_divisor >>= 1

    return quotient


def random_integer_division_test_case():
    divisor = random.randint(1, 100)
    quotient = random.randint(1, 100)
    remainder = random.randint(0, divisor)
    return (quotient * divisor + remainder, divisor)


def main():
    random.seed(0)
    tests = tuple(
        (dividend, divisor) for dividend in range(1, 5)
        for divisor in range(1, 5)) + (
            (100, 10),
            (99, 10),
            (101, 10),
        ) + tuple(random_integer_division_test_case() for _ in range(25))
    sols = (integer_division_primitives, )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, data in enumerate(tests):
        print('Test {}:'.format(test_index + 1))
        print('dividend = {}, divisor = {}'.format(*data))
        want = integer_division(*data)
        print('want = {}'.format(want))

        for sol in sols:
            got = sol(*data)
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
