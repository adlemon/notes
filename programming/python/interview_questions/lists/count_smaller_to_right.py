#!/usr/bin/python3
# count_smaller_to_right.py
# Given a list return a list with the same size as the original list such that
# every element of the returned list is the number of elements in the original
# list that are smaller and to the right of the corresponding element in the
# original list. For example, given the list [3, 1, 2], you should return the
# list [2, 0, 0] because
#   * there are two elements in the original list that are to the right of and
#     smaller than the first element in the original list (1 and 2 are less than
#     3),
#   * there are no elements in the original list that are to the right of and
#     smaller than the second element in the original list, and
#   * there are no elements in the original list that are to the right of and
#     smaller than the third element in the original list.
# DCP1.4;

def count_smaller_to_right_brute_force(lst):
  smaller_to_right_counts = len(lst) * [0]
  for i in range(len(lst)):
    for j in range(i + 1, len(lst)):
      if lst[j] < lst[i]:
        smaller_to_right_counts[i] += 1
  return smaller_to_right_counts

# TODO: Find a more efficient solution.

def main():
  tests = (
    ([1, 2, 3, 4, 5], [0, 0, 0, 0, 0]),
    ([5, 4, 3, 2, 1], [4, 3, 2, 1, 0]),
    ([1, 1, 1, 1, 1], [0, 0, 0, 0, 0]),
    ([1, 2, 3, 2, 1], [0, 1, 2, 1, 0]),
    ([1, 2, 3, 1, 2], [0, 1, 2, 0, 0]),
  )
  sols = (
    count_smaller_to_right_brute_force,
  )

  correct_counts = {sol: 0 for sol in sols}
  for lst, want in tests:
    print('lst = {}, want = {}'.format(lst, want))
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
    print(
      '{}: {} of {} correct'.format(
        sol.__name__,
        correct_counts[sol],
        len(tests)
      )
    )

if __name__ == '__main__':
  main()
