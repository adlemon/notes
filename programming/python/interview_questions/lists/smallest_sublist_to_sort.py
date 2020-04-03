#!/usr/bin/python3
# smallest_sublist_to_sort.py
# Given a list of numbers, determine the indices of the smallest sublist that
# must be sorted in order to sort the entire list in ascending order. Return
# None, None if the list is already sorted in ascending order. For example,
# given the list [1, 2, 5, 4, 3, 6], you should return (2, 4) because sorting
# the sublist between index 2 (the element with value 5) and index 4 (the
# element with value 3) sorts the entire list, and it is not possible to sort
# the entire list by sorting a smaller sublist.
# DCP1.2;


def smallest_sublist_to_sort_brute_force(lst):
    for width in range(1, len(lst) + 1):
        for lo in range(0, len(lst) - width + 1):
            hi = lo + width - 1
            lst_copy = lst[:]
            lst_copy[lo:(hi + 1)] = sorted(lst_copy[lo:(hi + 1)])
            if lst_copy == sorted(lst_copy):
                return (lo, hi) if lo < hi else (None, None)


def smallest_sublist_to_sort_sort(lst):
    sorted_lst = sorted(lst)
    lo = hi = None
    for i in range(len(lst)):
        if lst[i] != sorted_lst[i]:
            if lo is None:
                lo = i
            hi = i
    return lo, hi


def smallest_sublist_to_sort_cumulative_extrema(lst):
    # Let i be the smallest index with the property that
    #   (*) there exists an index j > i such that lst[j] < lst[i],
    # and let i be None if no index satisfies (*). We claim that i is the left
    # endpoint of the smallest sublist that needs to be sorted in order to sort
    # the list. First, suppose that no index satisfies (*). Then for all indices
    # i < j we have that lst[i] <= lst[j]. Thus, the list is already sorted, so
    # returning None is correct. Now suppose that there exists at least one index
    # that satisfies (*). In this case,
    #   (1) we need to move the element at index i in the original list because
    #       the element at index j > i is to the right of the element at index i
    #       in the original list, but the element at index j is to the left of the
    #       element at index i in the sorted list since lst[j] < lst[i];
    #   (2) we do not need to move any element to the left of index i because for
    #       all indices k < i we have that lst[i] >= lst[k] since index k cannot
    #       satisfy (*) since i is the smallest index that satisfies (*).
    # We can efficiently find the smallest index i that satisfies (*) by starting
    # at the end of the list, and moving towards the front of the list, keeping
    # track of the smallest element that we have seen so far; any element that is
    # larger than the smallest element seen so far satisfies (*); the last element
    # that we encounter that satisfies (*) is the desired index i.
    cum_min = lst[-1]
    lo = None
    for i in range(len(lst) - 1, -1, -1):
        if lst[i] > cum_min:
            lo = i
        else:
            cum_min = lst[i]

    # Although the reasoning to find the right endpoint is essentially the mirror
    # of the reasoning to find the left endpoint, we give the argument in detail
    # for completeness. Let i be the largest index with the property that
    #   (**) there exists an index j < i such that lst[j] > lst[i],
    # and let i be None if no index satisfies (**). We claim that i is the right
    # endpoint of the smallest sublist that needs to be sorted in order to sort
    # the list. First, suppose that no index satisfies (**). Then for all indices
    # i > j we have that lst[i] >= lst[j]. Thus, the list is already sorted, so
    # returning None is correct. Now suppose that there exists at least one index
    # that satisfies (**). In this case,
    #   (1) we need to move the element at index i in the original list because
    #       the element at index j < i is to the left of the element at index i in
    #       the original list, but the element at index j is to the right of the
    #       element at index i in the sorted list since lst[j] > lst[i];
    #   (2) we do not need to move any element to the right of index i because for
    #       all indices k > i we have that lst[i] <= lst[k] since index k cannot
    #       satisfy (**) since i is the largest index that satisfies (**).
    # We can efficiently find the largest index i that satisfies (**) by starting
    # at the end of the list, and moving towards the back of the list, keeping
    # track of the largest element that we have seen so far; any element that is
    # smaller than the largest element seen so far satisfies (**); the last
    # element that we encounter that satisfies (**) is the desired index i.
    cum_max = lst[0]
    hi = None
    for i in range(len(lst)):
        if lst[i] < cum_max:
            hi = i
        else:
            cum_max = lst[i]

    return lo, hi


def main():
    tests = (
        ([1, 2, 5, 4, 3, 6], (2, 4)),
        ([1, 2, 3, 4, 5, 6], (None, None)),
        ([2, 3, 4, 5, 6, 1], (0, 5)),
        ([6, 1, 2, 3, 4, 5], (0, 5)),
        ([6, 5, 4, 3, 2, 1], (0, 5)),
        ([1, 6, 5, 4, 3, 2], (1, 5)),
        ([1, 4, 3, 5, 6, 2], (1, 5)),
        ([5, 4, 3, 2, 1, 6], (0, 4)),
    )
    sols = (
        smallest_sublist_to_sort_brute_force,
        smallest_sublist_to_sort_sort,
        smallest_sublist_to_sort_cumulative_extrema,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (lst, want) in enumerate(tests):
        print('Test {}:'.format(test_index + 1))
        print('lst = {}'.format(lst))
        print('want = {}'.format(want))

        for sol in sols:
            got = sol(lst)
            if got == want:
                print('{} passes'.format(sol.__name__))
                correct_counts[sol] += 1
            else:
                print('{} fails; got = {}'.format(sol.__name__, got))

        print()

    print('Summary:')
    for sol in sols:
        print('{}: {} of {} correct'.format(sol.__name__, correct_counts[sol],
                                            len(tests)))


if __name__ == '__main__':
    main()
