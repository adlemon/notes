#!/usr/bin/python3
# write_in_int.py
# You are given two integers, src and dst, and two nonnegative integers i and
# j. You may assume that src can be represented using j - i + 1 bits. Write a
# function that sets the indices between the bits in dst between the 0-based
# indices i and j to the bit representation of dst.
# CCI5.2;


def write_in_int_bit_by_bit(src, dst, i, j):
    mask_src = 1
    mask_dst = (1 << i)

    for _ in range(j - i + 1):
        # Clear the bit in dst.
        dst &= ~mask_dst
        # Set the bit in dst if the bit in src in set.
        if src & mask_src:
            dst |= mask_dst
        # Shift the masks to the next bits.
        mask_src <<= 1
        mask_dst <<= 1
        print(f'{_}, {dst:b}')

    return dst


def write_in_int_single_mask(src, dst, i, j):
    # Create a bit vector consisting of j - i + 1 1-bits.
    mask = (1 << (j - i + 1)) - 1
    return (dst & (~(mask << i))) | (src << i)


def main():
    tests = (
        ((0b1010, 0b0000, 0, 3), 0b1010),
        ((0b1010, 0b1111, 0, 3), 0b1010),
        ((0b101, 0b000, 0, 2), 0b101),
        ((0b101, 0b10001, 1, 3), 0b11011),
        ((0b101, 0b10000, 1, 3), 0b11010),
        ((0b101, 0b00001, 1, 3), 0b01011),
    )
    sols = (
        write_in_int_bit_by_bit,
        write_in_int_single_mask,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print(f'Test {test_index + 1}:')
        print('src = {:b}, dst = {:b}, i = {}, j = {}'.format(*data))
        print(f'want = {want:b}')

        for sol in sols:
            got = sol(*data)
            if got == want:
                print(f'{sol.__name__} passes')
                correct_counts[sol] += 1
            else:
                print(f'{sol.__name__} fails; got = {got}')

        print()

    print('Summary:')
    for sol in sols:
        print(f'{sol.__name__}: {correct_counts[sol]} of {len(tests)} correct')


if __name__ == '__main__':
    main()
