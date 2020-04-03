#!/usr/bin/python3
# palindrome_pairs.py
# Given a list of words, return the list of all ordered pairs of unique indices
# such that the concatenation of the strings at those indices is a palindrome.
# For example, given the list of words ['ab', 'ba', 'x', 'yx'], you should
# return the list [(0, 1), (1, 0), (2, 3)] since 'ab' + 'ba' = 'abba',
# 'ba' + 'ab' = 'baab', and 'x' + 'yx' are palindromes.
# DCP2.2;


def palindrome_pairs_brute_force(words):
    def is_palindrome(s):
        return s == s[::-1]

    palindrome_pairs = []
    for i in range(len(words)):
        for j in range(len(words)):
            if i != j and is_palindrome(words[i] + words[j]):
                palindrome_pairs.append((i, j))

    return palindrome_pairs


def palindrome_pairs_dictionary(words):
    def is_palindrome(s):
        lo = 0
        hi = len(s) - 1
        while lo < hi:
            if s[lo] != s[hi]:
                return False
            lo += 1
            hi -= 1
        return True

    word_indices = {}
    for i, w in enumerate(words):
        if w in word_indices:
            word_indices[w].append(i)
        else:
            word_indices[w] = [i]

    # Let w1 and w2 be words with len(w1) >= len(w2). There are two possible ways
    # in which w1 + w2 can be a palindrome:
    #   (1) if w1 = x + p and w2 = reversed(x), where x is an arbitrary string and
    #       p is a palindrome, then w1 + w2 = x + p + reversed(x) is a palindrome;
    #   (2) if w1 = p + x and w2 = reversed(x), where x is an arbitrary string and
    #       p is a palindrome, then w2 + w1 = reversed(x) + p + x is a palindrome.
    palindrome_pairs = set()
    for i, w in enumerate(words):
        for k in range(len(w) + 1):
            prefix = w[:k]
            suffix = w[k:]

            reversed_prefix = prefix[::-1]
            reversed_suffix = suffix[::-1]

            # (1) x = prefix, p = suffix
            if is_palindrome(suffix):
                for j in word_indices.get(reversed_prefix, []):
                    if i != j:
                        palindrome_pairs.add((i, j))
            # (2) x = suffix, p = prefix
            if is_palindrome(prefix):
                for j in word_indices.get(reversed_suffix, []):
                    if i != j and (j, i) not in palindrome_pairs:
                        palindrome_pairs.add((j, i))

    return list(palindrome_pairs)


def main():
    tests = (
        (['ab', 'ba', 'x', 'yx'], [(0, 1), (1, 0), (2, 3)]),
        (['ab', 'ba', 'cba'], [(0, 1), (0, 2), (1, 0)]),
        (['ab', 'ba', 'ba'], [(0, 1), (0, 2), (1, 0), (2, 0)]),
        (['abc', 'ba', 'ab', 'cba'], [(0, 1), (0, 3), (1, 2), (2, 1), (2, 3),
                                      (3, 0)]),
        (['abcb', 'a'], [(0, 1)]),
        (['aba', ''], [(0, 1), (1, 0)]),
        (['a', 'b', 'a'], [(0, 2), (2, 0)]),
        (['abcded', 'cba'], [(0, 1)]),
    )
    sols = (
        palindrome_pairs_brute_force,
        palindrome_pairs_dictionary,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (words, want) in enumerate(tests):
        print('Test {}:'.format(test_index + 1))
        print('words = {}'.format(words))
        print('want = {}'.format(want))

        for sol in sols:
            got = sorted(sol(words))
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
