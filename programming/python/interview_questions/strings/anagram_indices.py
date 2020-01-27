#!/usr/bin/python3
# anagram_indices.py
# Given strings s and w, find the starting indices of all anagrams of w in s.
# For example, given s = 'abacbaa' and w = 'ab', you should return [0, 1, 4],
# since anagrams of w start at indices 0, 1, and 4 of s.
# DCP2.1;

def anagram_indices_brute_force(s, w):
  # Two strings are anagrams if and only if they have the same unique characters
  # and each unique character occurs the same number of times.
  def are_anagrams(s1, s2):
    if len(s1) != len(s2):
      return False

    character_count_diffs = {}
    for c in s1:
      character_count_diffs[c] = character_count_diffs.get(c, 0) + 1

    for c in s2:
      character_count_diffs[c] = character_count_diffs.get(c, 0) - 1
      if character_count_diffs[c] < 0:
        return False
      if character_count_diffs[c] == 0:
        del character_count_diffs[c]

    return True

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

  # Let d be a dictionary with arbitrary keys and integer values. We assume that
  # keys that are included in the dictionary correspond to values of 0. Given a
  # key and an integer delta, we add delta to the value of key in the
  # dictionary. If this results in the value of the key being 0, then we remove
  # the key from the dictionary.
  def update_key_value(d, key, delta):
    d[key] = d.get(key, 0) + delta
    if d[key] == 0:
      del d[key]

  # We will maintain a dictionary diffs whose keys are characters, and whose
  # values are the numbers of occurrences of the characters in w minus the
  # numbers of occurrences of the characters in substrings of s. If this
  # difference in occurrences is 0, then we do not include the character as a
  # key in the dictionary. Whenever this dictionary is empty, we have found a
  # substring of s that is an anagram of w. We begin by computing this
  # dictionary for the first len(w) characters of s.
  diffs = {}
  for c in w:
    update_key_value(diffs, c, +1)
  for i in range(len(w)):
    update_key_value(diffs, s[i], -1)
  anagram_indices = [] if diffs else [0]

  # We can easily update the dictionary when we shift the substring by one
  # character -- we increment the count for the character that leaves the
  # substring, and decrement the count for the character that enters the
  # substring.
  for i in range(1, len(s) - len(w) + 1):
    update_key_value(diffs, s[i-1], +1)
    update_key_value(diffs, s[i + len(w) - 1], -1)
    if not diffs:
      anagram_indices.append(i)

  return anagram_indices

def main():
  tests = (
    (('abacbaa', 'ab'), [0, 1, 4]),
    (('aabbcc', 'abc'), []),
    (('abccab', 'abc'), [0, 3]),
    (('aaaaa', 'a'), [0, 1, 2, 3, 4]),
    (('a', 'aa'), []),
  )
  sols = (
    anagram_indices_brute_force,
    anagram_indices_running_histogram,
  )

  correct_counts = {sol: 0 for sol in sols}
  for test_index, ((s, w), want) in enumerate(tests):
    print('Test {}:'.format(test_index + 1))
    print('s = {}, w = {}'.format(s, w))
    print('want = {}'.format(want))

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
