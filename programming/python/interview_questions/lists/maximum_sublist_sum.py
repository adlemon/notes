#!/usr/bin/python3
# maximum_sublist_sum.py
# Given a list, return the maximum sum of a sublist of the list. For example,
#   * given the list [1, 2, -10, 3, 4, -10], you should return 7 because the
#     maximum sum of a sublist is 3 + 4 = 7;
#   * given the list [-1, -1, -1], you should return 0 because the maximum sum
#     of a sublist is 0 (which we define to be the sum of the empty list).
# DCP1.3;

def maximum_sublist_sum_brute_force(lst):
  # Compute the sum of each sublist and take the maximum.
  return max(
    sum(lst[i:j])
    for i in range(len(lst))
    for j in range(i, len(lst) + 1)
  )

def maximum_sublist_sum_clipped_running_sum(lst):
  # Let phi[i] be the maximum sum of a sublist of lst whose last element is the
  # element at index i. Observe that phi[0] = lst[0] and
  # phi[i] = max(phi[i-1], 0) + lst[i] for i > 0 because a maximum-sum sublist
  # whose last element is the element at index i is either an extension of a
  # maximum-sum sublist whose last element is the element at index i-1 or a
  # singleton sublist consisting only of the element at index i. Finally, we
  # note that the maximum sum of a sublist of lst is the maximum of the phi[i].
  # In order to implement this idea efficiently, we note that we only need to
  # know phi[i-1] to compute phi[i]; in particular, we do not need to store
  # phi[0], ..., phi[i-2]. Additionally, we can keep track of the maximum value
  # of phi[i] at the same time that we are computing the phi[i].
  phi = maximum_sublist_sum = 0
  for x in lst:
    phi = max(phi, 0) + x
    maximum_sublist_sum = max(maximum_sublist_sum, phi)
  return maximum_sublist_sum

def main():
  tests = (
    ([1, 2, -10, 3, 4, -10], 7),
    ([-1, -1, -1], 0),
    ([3, 4, -10, 1, 2], 7),
    ([-1, -1, -1, 3], 3),
    ([3, -1, -1, -1], 3),
  )
  sols = (
    maximum_sublist_sum_brute_force,
    maximum_sublist_sum_clipped_running_sum,
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
