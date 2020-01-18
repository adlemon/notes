#!/usr/bin/python3
# print_zigzag.py
# Given a string s and an integer w, print the string in zigzag form with width
# w. In zigzag form with width w, the string is printed on w lines. The
# printing begins in the first column and the first line. Each subsequent
# character is one character to the left of the previous character and one row
# either above or below. The w-1 characters after the first character are each
# one row below the previous character; the next w-1 characters are each one
# row above the previous characters; then the pattern repeats. For example,
# given the string s = 'abcdefghij' and the integer w = 3, you should print the
# following.
#   a   e   i
#    b d f h j
#     c   g
# DCP2.3;

def print_zigzag_all_lines(s, w):
  if w == 1:
    return s

  lines = w * ['']
  columns = w * [0]
  line = column = 0
  delta = 1
  for c in s:
    lines[line] += (column - columns[line]) * ' ' + c

    column += 1
    columns[line] = column

    if line == 0:
      delta = +1
    elif line == w-1:
      delta = -1
    line += delta

  return '\n'.join(lines)

def print_zigzag_line_by_line(s, w):
  if w == 1:
    return s

  lines = [len(s) * [' '] for _ in range(w)]
  for i in range(w):
    j = i
    is_descending = True
    while j < len(s):
      lines[i][j] = s[j]
      if is_descending:
        # Advance the cursor for lines i+1, ..., w-2, w-1, w-2, ..., i+1, i.
        j += 2 * (w - i - 1)
      else:
        # Advance the cursor for lines i-1, ..., 1, 0, 1, ..., i-1, i.
        j += 2 * i
      is_descending = not is_descending

  return '\n'.join(''.join(line).rstrip() for line in lines)

def main():
  tests = (
    (
      ('abcdefghij', 3),
      '\n'.join([
        'a   e   i',
        ' b d f h j',
        '  c   g'
      ])
    ),
    (
      ('abcdef', 1),
      'abcdef',
    ),
    (
      ('abcdef', 2),
      '\n'.join([
        'a c e',
        ' b d f'
      ])
    ),
    (
      ('abcdefghijklm', 4),
      '\n'.join([
        'a     g     m',
        ' b   f h   l',
        '  c e   i k',
        '   d     j'
      ])
    ),
    (
      ('abcdefghijklmn', 5),
      '\n'.join([
        'a       i',
        ' b     h j',
        '  c   g   k',
        '   d f     l n',
        '    e       m'
      ])
    ),
  )
  sols = (
    print_zigzag_all_lines,
    print_zigzag_line_by_line,
  )

  correct_counts = {sol: 0 for sol in sols}
  for (s, w), want in tests:
    print('s = {}, w = {}, want =\n{}'.format(s, w, want))
    for sol in sols:
      got = sol(s, w)
      if got == want:
        print('{} passes'.format(sol.__name__))
        correct_counts[sol] += 1
      else:
        print('{} fails; got =\n{}'.format(sol.__name__, got))
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
