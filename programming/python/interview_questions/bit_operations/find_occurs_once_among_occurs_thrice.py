#!/usr/bin/python3
# find_occurs_once_among_occurs_thrice.py
# You are given a list of integers such that there is a unique element that
# occurs once, and all other elements occur three times. Find the element that
# occurs once.
# DCP17.1;


def find_occurs_once_among_occurs_thrice_count_elements(lst):
    element_counts = {}
    for x in lst:
        element_counts[x] = element_counts.get(x, 0) + 1

    for x in element_counts:
        if element_counts[x] == 1:
            return x

    return None


def find_occurs_once_among_occurs_thrice_bit_array(lst):
    # Let b[i] be the ith binary digit of the element that appears once, t[i]
    # be the number of distinct elements that appear three times and whose ith
    # binary digit is 1, and n[i] be the number of elements (counting
    # duplicates) whose ith binary digit is 1. Then we have that
    #   n[i] = 3 * t[i] + b[i]
    # and hence that
    #   b[i] = n[i] % 3.
    # Thus, we can find the ith binary digit of the element that appears once
    # by iterating through the list, keeping a running count modulo 3 of the
    # number of elements whose ith binary digit is 1.
    bits = []
    for x in lst:
        bit_index = 0
        while x > 0:
            if (x & 1) == 1:
                while bit_index >= len(bits):
                    bits.append(0)
                bits[bit_index] = (bits[bit_index] + 1) % 3
            bit_index += 1
            x >>= 1

    # Reconstruct the element that appears once in the list from its binary
    # representation.
    y = 0
    for i, b in enumerate(bits):
        y |= (b << i)

    return y


def find_occurs_once_among_occurs_thrice_two_bits(lst):
    # Let b[i] be the ith binary digit of the element that appears once, t[i]
    # be the number of distinct elements that appear three times and whose ith
    # binary digit is 1, and n[i] be the number of elements (counting
    # duplicates) whose ith binary digit is 1. Then we have that
    #   n[i] = 3 * t[i] + b[i]
    # and hence that
    #   b[i] = n[i] % 3.
    # Thus, we can find the ith binary digit of the element that appears once
    # by iterating through the list, keeping a running count modulo 3 of the
    # number of elements whose ith binary digit is 1.
    #
    # We can represent these running counts modulo 3 using two integers, b0 and
    # b1, where the ith binary digit of b0 + 2 * b1 is the running count modulo
    # 3 of the number of elements whose ith binary digit is 1. If b0[i] is the
    # ith binary digit of b0, b1[i] is the ith binary digit of b1, x is the
    # element of the list that we are currently processing, and x[i] is the ith
    # binary digit of x, then we update the values of b0[i] and b1[i] as in the
    # following table.
    #   b0[i]  b1[i]  x[i]  ==>  b0[i]  b1[i]
    #   -------------------------------------
    #     0      0      0          0      0
    #     0      0      1          1      0
    #     0      1      0          0      1
    #     0      1      1          0      0
    #     1      0      0          1      0
    #     1      0      1          0      1
    # The disjunctive normal form of the update function is as follows.
    #   b0[i] = ((NOT b0[i]) AND (NOT b1[i]) AND x[i])
    #           OR (b0[i] AND (NOT b1[i]) AND (NOT x[i])),
    #   b1[i] = ((NOT b0[i]) AND b1[i] AND (NOT x[i]))
    #           OR (b0[i] AND (NOT b1[i]) AND x[i]).
    # Note that these two updates must be performed simultaneously.
    b0 = b1 = 0
    for x in lst:
        b0, b1 = (
            ((~b0) & (~b1) & x) | (b0 & (~b1) & (~x)),
            ((~b0) & b1 & (~x)) | (b0 & (~b1) & x),
        )

    return b0


def main():
    tests = (
        ([1, 2, 2, 2, 3, 3, 3], 1),
        ([1, 1, 1, 2, 3, 3, 3], 2),
        ([1, 1, 1, 2, 2, 2, 3], 3),
        ([1, 2, 3, 3, 2, 2, 3], 1),
        ([3, 1, 3, 1, 3, 1, 2], 2),
        ([1, 1, 2, 2, 3, 2, 1], 3),
    )
    sols = (
        find_occurs_once_among_occurs_thrice_count_elements,
        find_occurs_once_among_occurs_thrice_bit_array,
        find_occurs_once_among_occurs_thrice_two_bits,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print('Test {}:'.format(test_index + 1))
        print('data = {}'.format(data))
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
