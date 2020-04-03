#!/usr/bin/python3
# balanced_delimiters.py
# Consider a string that only contains parentheses, '(' and ')', curly brackets,
# '{' and '}', and square brackets, '[' and ']'. Such a string is said to be
# "balanced" if one of the following conditions is true:
#   (1) the string is the empty string;
#   (2) the string has the form '(s)', '{s}', or '[s]', where s is a balanced
#       string; or
#   (3) the string has the form 's1s2', where s1 and s2 are nonempty balanced
#       strings.
# Write a function that checks whether such a string is balanced.
# DCP4.2;


def is_balanced_recursive(s):
    # Base case: the empty string is balanced.
    if s == '':
        return True

    matching_delimiters = {
        '(': ')',
        '{': '}',
        '[': ']',
    }

    # Check for balanced strings of the form '(s)', '{s}', or '[s]', where is a
    # a balanced string.
    if (s[-1] == matching_delimiters.get(s[0], None)
            and is_balanced_recursive(s[1:-1])):
        return True

    # Check for balanced strings of the form 's1s2', where s1 and s2 are balanced
    # strings.
    for i in range(2, len(s) - 1, 2):
        if is_balanced_recursive(s[:i]) and is_balanced_recursive(s[i:]):
            return True

    # If we did not match any of the patterns above, then the string is not
    # balanced.
    return False


def is_balanced_stack(s):
    matching_delimiters = {
        '(': ')',
        '{': '}',
        '[': ']',
    }

    open_delimiters = []
    for c in s:
        if c in matching_delimiters:
            # If the current character is an open delimiter, then we push it onto the
            # stack of open delimiters.
            open_delimiters.append(c)
        elif open_delimiters and matching_delimiters[open_delimiters[-1]] == c:
            # If the current character is not an open delimiter, then we check whether
            # the current character matches the last unmatched open delimiter. If we
            # find a match, then we pop the last unmatched open delimiter off the
            # stack.
            open_delimiters.pop()
        else:
            # If the current character is neither an open delimiter nor a match for
            # the last unmatched open delimiter, then the string is not balanced.
            return False

    return not open_delimiters


def main():
    tests = (
        ('', True),
        ('()', True),
        ('{}', True),
        ('[]', True),
        ('()()', True),
        ('(())', True),
        ('[]{}', True),
        ('[{}]', True),
        ('()[]{}', True),
        ('([]){}', True),
        ('(', False),
        ('[', False),
        ('(]', False),
        ('([)]', False),
    )
    sols = (
        is_balanced_recursive,
        is_balanced_stack,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (s, want) in enumerate(tests):
        print('Test {}:'.format(test_index + 1))
        print('s = {}'.format(s))
        print('want = {}'.format(want))

        for sol in sols:
            got = sol(s)
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
