#!/usr/bin/python3
# smallest_rotated_string.py
# You are given a string of length n and an integer k. The string can be
# manipulated by taking one of the first k letters and moving it to the end of
# the string.
#
# Write a program to determine the lexicographically smallest string that can
# be created after an unlimited number of moves.
#
# For example, suppose w are given the string 'dcab' and the integer k = 1.
# The smallest string that can be obtained by applying 1-rotations to the
# string is 'abdc'.
# DCP2.4;

def smallest_rotated_string(s, k):
  if k > 1:
    # If k > 1, then we can sort the string. First, we show that it is possible
    # to swap any two adjacent characters in the string. Let n be the length of
    # the string, and suppose we want to swap the characters at indices i and
    # i+1 for some i such that 0 <= i < n-1.
    # (1) Move the characters s[0], ..., s[i-1] to the end of the string.
    # s[0], s[1], ..., s[i-1], s[i], s[i+1], s[i+2], s[i+3], ..., s[n-1]
    # ==> s[1], ..., s[i-1], s[i], s[i+1], s[i+2], s[i+3], ..., s[n-1], s[0]
    # ...
    # ==> s[i], s[i+1], s[i+2], s[i+3], ..., s[n-1], s[0], s[1], ..., s[i-1]
    # (2) Move the character s[i+1] to the end of the string.
    # ==> s[i], s[i+2], s[i+3], ..., s[n-1], s[0], s[1], ..., s[i-1], s[i+1]
    # (3) Move the character s[i] to the end of the string.
    # ==> s[i+2], s[i+3], ..., s[n-1], s[0], s[1], ..., s[i-1], s[i+1], s[i]
    # (4) Move the characters s[i+2], ..., s[n-1] to the end of the string.
    # ==> s[i+3], ..., s[n-1], s[0], s[1], ..., s[i-1], s[i+1], s[i], s[i+2]
    # ...
    # ==> s[0], s[1], ..., s[i-1], s[i+1], s[i], s[i+2], s[i+3], ..., s[n-1]
    # We can use a sequence of such swaps of adjacent characters to sort the
    # string. First, we use such swaps to move the smallest character to the
    # front of the string. Then, we use such swaps to move the second smallest
    # character to the second index in the string. We continue in this manner
    # until the string is sorted.
    return ''.join(sorted(s))

  # Find the smallest rotated string.
  n = len(s)
  i = 0
  for j in range(n):
    # Check if s[j:] + s[:j] < s[i:] + s[:i].
    for k in range(n):
      c_i = s[(i + k) % n]
      c_j = s[(j + k) % n]
      if c_i < c_j:
        break
      elif c_i > c_j:
        i = j
        break

  return s[i:] + s[:i]

def main():
  tests = (
    (('dcab', 1), 'abdc'),
    (('caba', 1), 'abac'),
    (('xaxax', 2), 'aaxxx')
  )
  sols = (
    smallest_rotated_string,
  )

  correct_counts = {sol: 0 for sol in sols}
  for (s, k), want in tests:
    print('s = {}, k = {}, want = {}'.format(s, k, want))
    for sol in sols:
      got = sol(s, k)
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
