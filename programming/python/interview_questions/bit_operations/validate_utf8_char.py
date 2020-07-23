#!/usr/bin/python3
# validate_utf8.py
# UTF-8 is a character encoding that maps each symbol to one, two, three, or
# four bytes. The rules for mapping characters are as follows:
#   * for a single-byte character, the first bit must be zero;
#   * for an n-byte character, the first byte must start with n ones and a zero;
#     the other n - 1 bytes must start with 10.
# Visually, this can be represented as follows.
#   Bytes | Byte Format
#   ------|-------------------------------------
#      1  | 0xxxxxxx
#      2  | 110xxxxx 10xxxxxx
#      3  | 1110xxxx 10xxxxxx 10xxxxxx
#      4  | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
# Write a function that takes in an array of integers as input, and returns
# whether the concatenation of the integers is a valid UTF-8 character.
# DCP20.8;


def validate_utf8_char(b):
    try:
        if ((b[0] >> 7) & 1) == 0b0:
            num_bytes = 1
        elif ((b[0] >> 5) & 0b111) == 0b110:
            num_bytes = 2
        elif ((b[0] >> 4) & 0b1111) == 0b1110:
            num_bytes = 3
        elif ((b[0] >> 3) & 0b11111) == 0b11110:
            num_bytes = 4
        else:
            return False

        if len(b) != num_bytes:
            return False

        for i in range(1, num_bytes):
            if ((b[i] >> 6) & 0b11) != 0b10:
                return False

        return True
    except:
        return False


def main():
    tests = (
        ([0b01010101], True),
        ([0b11010101, 0b10101010], True),
        ([0b11010101, 0b11000000], False),
        ([0b11010101], False),
        ([0b11101010, 0b10101010, 0b10101010], True),
        ([0b11101010, 0b10101010, 0b11010101], False),
        ([0b11101010, 0b11010101, 0b10101010], False),
        ([0b11101010, 0b11010101, 0b11010101], False),
        ([0b11110101, 0b10101010, 0b10101010, 0b10101010], True),
        ([0b11110101, 0b10101010, 0b10101010, 0b11010101], False),
        ([0b11110101, 0b10101010, 0b11010101, 0b10101010], False),
        ([0b11110101, 0b11010101, 0b10101010, 0b10101010], False),
    )
    sols = (validate_utf8_char, )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print('Test {}:'.format(test_index + 1))
        print('data = {}'.format(', '.join('{:08b}'.format(x) for x in data)))
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
