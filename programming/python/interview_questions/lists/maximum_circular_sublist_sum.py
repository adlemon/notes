#!/usr/bin/python3
# maximum_circular_sublist_sum.py
# Given a list, return the maximum sum of a "circular sublist" of the list. By
# "circular sublist", we mean either a sublist or the union of a suffix and
# prefix of the list. Intuitively, we think of a "circular sublist" that is
# allowed to "wrap around" from the end of the list back to the front. For
# example,
#   * given the list [1, 2, -10, 3, 4, -10], you should return 7 because the
#     maximum sum of a sublist is 3 + 4 = 7;
#   * given the list [-1, -1, -1], you should return 0 because the maximum sum
#     of a sublist is 0 (which we define to be the sum of the empty list);
#   * given the list [1, -10, 1], you should return 1 + 1 = 2, where the sublist
#     corresponding to the maximum sum of a sublist is the sublist that "wraps
#     around" from the 1 at the end of the list to the 1 at the beginning of the
#     list.
# DCP1.3;

def maximum_circular_sublist_sum_brute_force(lst):
  # Compute the sum of each "circular sublist" and take the maximum. Given i and
  # j with 0 <= i < len(lst) and 0 <= j <= len(lst), we associate (i, j) with
  # the sublist lst[i:j] if i <= j and with the "wrapped around sublist"
  # lst[:j] + lst[i:] if i > j.
  return max(
    sum(lst[i:j] if i <= j else lst[:j] + lst[i:])
    for i in range(len(lst))
    for j in range(len(lst) + 1)
  )

def maximum_circular_sublist_sum_clipped_running_sum(lst):
  # A sublist that "wraps around" leaves out a sublist that does not "wrap
  # around". Thus, the sum of a sublist that wraps around is the sum of all of
  # the elements in the list minus the sum of the elements that are left out.
  # The maximum sum of a sublist that "wraps around" is therefore the sum of all
  # of elements in the list minus the minimum sum of a sublist that does not
  # wrap around. See maximum_sublist_sum.py for an algorithm to compute the
  # maximum sum of a sublist that does not wrap around. We use this algorithm
  # and a variant of it to compute the maximum and minimum sublist sums.
  # Finally, we return the maximum of the maximum sum of a sublist that wraps
  # around and the maximum sum of a sublist that does not wrap around.
  phi = psi = maximum_sublist_sum = minimum_sublist_sum = total_sum = 0
  for x in lst:
    phi = max(phi, 0) + x
    maximum_sublist_sum = max(maximum_sublist_sum, phi)

    psi = min(psi, 0) + x
    minimum_sublist_sum = min(minimum_sublist_sum, psi)

    total_sum += x

  return max(maximum_sublist_sum, total_sum - minimum_sublist_sum)

def main():
  tests = (
    ([1, 2, -10, 3, 4, -10], 7),
    ([-1, -1, -1], 0),
    ([1, -10, 1], 2),
    ([1, 1, 1], 3),
  )
  sols = (
    maximum_circular_sublist_sum_brute_force,
    maximum_circular_sublist_sum_clipped_running_sum,
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
    print('{}: {} of {} correct'.format(sol.__name__, correct_counts[sol], len(tests)))

if __name__ == '__main__':
  main()
