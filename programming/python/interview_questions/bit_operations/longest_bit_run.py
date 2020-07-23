#!/usr/bin/python3
# longest_bit_run.py
# Find the length of the longest run of consecutive 1s in the binary
# representation of a given nonnegative integer.
# DCP17.3;


def construct_from_bits(bits):
    x = 0
    for bit in reversed(bits):
        x = (x << 1) | bit
    return x


def longest_bit_run_iterate_through_bits(x):
    # Iterate through the bits of x, keeping track of the maximum run length.
    max_run_length = 0
    while x > 0:
        while (x & 1) == 0:
            x >>= 1

        current_run_length = 0
        while (x & 1) == 1:
            current_run_length += 1
            x >>= 1

        max_run_length = max(max_run_length, current_run_length)

    return max_run_length


def longest_bit_run_shift_and(x):
    # The maximum run length is the number of times that we can shift x by one
    # bit and AND it with itself without getting 0.
    max_run_length = 0
    while x > 0:
        max_run_length += 1
        x &= (x >> 1)
    return max_run_length


def main():
    tests = tuple((construct_from_bits(bits), run_length)
                  for bits, run_length in (
                      ((0, ), 0),
                      ((1, ), 1),
                      ((1, 1, 0, 0), 2),
                      ((1, 0, 1, 0), 1),
                      ((0, 1, 1, 0), 2),
                      ((0, 0, 1, 1), 2),
                      ((1, 1, 1, 0, 0, 1, 1), 3),
                      ((1, 1, 0, 0, 1, 1, 1), 3),
                  ))
    sols = (
        longest_bit_run_iterate_through_bits,
        longest_bit_run_shift_and,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print('Test {}:'.format(test_index + 1))
        print('x = {}'.format(data))
        print('want = {}'.format(want))

        for sol in sols:
            got = sol(data)
            if got == want:
                print('{} passes'.format(sol.__name__))
                correct_counts[sol] += 1
            else:
                print('{} fails; got = {}'.format(sol.__name__, len(tests)))

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
