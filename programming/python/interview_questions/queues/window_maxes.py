#!/usr/bin/python3
# window_maxes.py
# Given a list lst and an positive integer k such that k <= len(lst), return the
# list of the maximums of sliding windows of length k in lst. For example,
# given the list lst = [1, 2, 3, 1, 2, 1] and the integer k = 3, the list of
# maximums of the sliding windows of length k in lst is
#   [
#     3, # = max(lst[0] = 1, lst[1] = 2, lst[2] = 3)
#     3, # = max(lst[1] = 2, lst[2] = 3, lst[3] = 1)
#     3, # = max(lst[2] = 3, lst[3] = 1, lst[4] = 2)
#     2, # = max(lst[3] = 1, lst[4] = 2, lst[5] = 1)
#   ].
# DCP4.3;


def window_max_brute_force(lst, k):
    return [max(lst[i:(i + k)]) for i in range(len(lst) - k + 1)]


def window_max_queue(lst, k):
    # We will maintain a list called window that is a filtered list of the indices
    # in the current window. We filter the list of all indices in the current
    # window by removing all indices i such that there is a later index j > i such
    # that lst[j] > lst[i]. We can filter such indices i because they can never
    # corresponding to future window maximums -- if i is in a future window, then
    # j is also in the window, and we have that lst[j] > lst[i].
    window = []
    window_maximums = []
    for i in range(len(lst)):
        # Remove an index from the front of window if it has left the window.
        if window and window[0] < i - k + 1:
            window.pop(0)

        # Filter window and add the current index.
        while window and lst[window[-1]] < lst[i]:
            window.pop()
        window.append(i)

        # If we have accumulated a full window, then add the corresponding index to
        # the list of window maximums.
        if i >= k - 1:
            window_maximums.append(lst[window[0]])

    return window_maximums


def main():
    tests = (
        (([1, 2, 3, 4, 5, 4, 3, 2, 1], 1), [1, 2, 3, 4, 5, 4, 3, 2, 1]),
        (([1, 2, 3, 4, 5, 4, 3, 2, 1], 2), [2, 3, 4, 5, 5, 4, 3, 2]),
        (([1, 2, 3, 4, 5, 4, 3, 2, 1], 3), [3, 4, 5, 5, 5, 4, 3]),
        (([1, 2, 3, 4, 5, 4, 3, 2, 1], 4), [4, 5, 5, 5, 5, 4]),
        (([1, 2, 3, 4, 5, 4, 3, 2, 1], 5), [5, 5, 5, 5, 5]),
        (([5, 4, 3, 2, 1, 2, 3, 4, 5], 1), [5, 4, 3, 2, 1, 2, 3, 4, 5]),
        (([5, 4, 3, 2, 1, 2, 3, 4, 5], 2), [5, 4, 3, 2, 2, 3, 4, 5]),
        (([5, 4, 3, 2, 1, 2, 3, 4, 5], 3), [5, 4, 3, 2, 3, 4, 5]),
        (([5, 4, 3, 2, 1, 2, 3, 4, 5], 4), [5, 4, 3, 3, 4, 5]),
        (([5, 4, 3, 2, 1, 2, 3, 4, 5], 5), [5, 4, 3, 4, 5]),
        (([1, 1, 1, 2, 1, 1, 1, 2, 1, 1,
           1], 1), [1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1]),
        (([1, 1, 1, 2, 1, 1, 1, 2, 1, 1,
           1], 2), [1, 1, 2, 2, 1, 1, 2, 2, 1, 1]),
        (([1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1], 3), [1, 2, 2, 2, 1, 2, 2, 2, 1]),
        (([1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1], 4), [2, 2, 2, 2, 2, 2, 2, 2]),
    )
    sols = (
        window_max_brute_force,
        window_max_queue,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, ((lst, k), want) in enumerate(tests):
        print('Test {}:'.format(test_index + 1))
        print('lst = {}, k = {}'.format(lst, k))
        print('want = {}'.format(want))

        for sol in sols:
            got = sol(lst, k)
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
