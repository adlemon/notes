#!/usr/bin/python3
# find_occurs_once_among_occurs_twice.py
# You are given a list of integers such that there is a unique element that
# occurs once, and all other elements occur twice. Find the element that occurs
# once.
# DCP17.1;


def find_occurs_once_among_occurs_twice_count_elements(lst):
    element_counts = {}
    for x in lst:
        element_counts[x] = element_counts.get(x, 0) + 1

    for x in element_counts:
        if element_counts[x] == 1:
            return x

    return None


def find_occurs_once_among_occurs_twice_xor(lst):
    x = 0
    for y in lst:
        x ^= y
    return x


def main():
    tests = (
        ([1, 2, 2, 3, 3], 1),
        ([1, 1, 2, 3, 3], 2),
        ([1, 1, 2, 2, 3], 3),
        ([1, 2, 3, 2, 3], 1),
        ([3, 1, 2, 1, 3], 2),
        ([1, 2, 2, 1, 3], 3),
    )
    sols = (
        find_occurs_once_among_occurs_twice_count_elements,
        find_occurs_once_among_occurs_twice_xor,
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
