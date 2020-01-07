#!/usr/bin/python3
# anagram_indices.py
# Given strings s and w, find the starting indices of all anagrams of w in s.
# For example, given s = 'abacbaa' and w = 'ab', you should return [0, 1, 4],
# since anagrams of w start at indices 0, 1, and 4 of s.
# DCP2.1;

def anagram_indices_brute_force(s, w):
  # Given a string s, return a dictionary whose keys are the unique characters
  # in s, and whose values are the corresponding numbers of occurrences of each
  # of the unique characters in s.
  def character_counts(s):
    counts = {}
    for c in s:
      counts[c] = counts.get(c, 0) + 1
    return counts

  # Two strings are anagrams if and only if they have the same unique characters
  # and each unique character occurs the same number of times.
  def are_anagrams(s1, s2):
    return character_counts(s1) == character_counts(s2)

  # Iterate through all substrings of s that have the same length of w, and
  # check whether each of these substrings is an anagram of w.
  anagram_indices = []
  for i in range(len(s) - len(w) + 1):
    if are_anagrams(s[i:(i + len(w))], w):
      anagram_indices.append(i)
  return anagram_indices

def anagram_indices_running_histogram(s, w):
  # If the length of s is less than the length of w, then it is impossible for s
  # to contain an anagram of w.
  if len(s) < len(w):
    return []

  # Get a dictionary whose keys are the unique characters in w, and whose
  # corresponding values are the numbers of times that each unique character
  # occurs in w.
  character_counts_w = {}
  for c in w:
    character_counts_w[c] = character_counts_w.get(w, 0) + 1

  # Get a dictionary whose keys are the unique characters in the first len(w)
  # characters of s, and whose corresponding values are the numbers of times
  # that each unique character occurs in w.
  character_counts_sub_s = {}
  for i in range(len(w)):
    character_counts_sub_s[s[i]] = character_counts_sub_s.get(s[i], 0) + 1

  # The first len(w) of characters are an anagram of w if and only if they
  # contain the same unique characters as appear in w, and each character
  # appears the same number of times in w and the first len(w) characters of s.
  anagram_indices = (
    [0]
    if character_counts_sub_s == character_counts_w
    else []
  )
  # Iterate over all substrings of s that have length len(w), except for the
  # first len(w) characters since we have already checked if this substring is
  # an anagram of w.
  for i in range(1, len(s) - len(w) + 1):
    # Decrement the count of the character at index i - 1 in s. If the count for
    # this character becomes zero, remove it from the dictionary.
    character_counts_sub_s[s[i-1]] -= 1
    if character_counts_sub_s[s[i-1]] == 0:
      del character_counts_sub_s[s[i-1]]

    # Increment the count of the character at index i + len(w) - 1.
    character_counts_sub_s[s[i + len(w) - 1]] = (
      character_counts_sub_s.get(s[i + len(w) - 1], 0) + 1
    )

    # The substring s[i:(i + len(w))] is an anagram for w if and only if the
    # dictionary representing the character counts for this substring is equal
    # to the dictionary representing the character counts for w.
    if character_counts_sub_s == character_counts_w:
      anagram_indices.append(i)

  return anagram_indices

def main():
  tests = (
    ('abacbaa', 'ab', [0, 1, 4]),
    ('aabbcc', 'abc', []),
    ('abccab', 'abc', [0, 3]),
    ('aaaaa', 'a', [0, 1, 2, 3, 4]),
    ('a', 'aa', []),
  )
  sols = (
    anagram_indices_brute_force,
    anagram_indices_running_histogram,
  )

  correct_counts = {sol: 0 for sol in sols}
  for s, w, want in tests:
    print('s = {}, w = {}, want = {}'.format(s, w, want))
    for sol in sols:
      got = sol(s, w)
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
