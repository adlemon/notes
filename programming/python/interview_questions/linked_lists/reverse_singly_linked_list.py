#!/usr/bin/python3
# reverse_singly_linked_list.py
# Reverse a singly linked list.
# DCP3.1;

class LinkedList(object):
  def __init__(self, data, next=None):
    self.data = data
    self.next = next

  def __str__(self):
    return (
      '{} -> {}'.format(self.data, self.next)
      if self.next
      else str(self.data)
    )

  def copy(self):
    return LinkedList(
      self.data,
      self.next.copy() if self.next else None
    )

  def __eq__(self, other):
    return str(self) == str(other)

  def reverse_recursive_helper(self):
    if not self.next:
      return self, self

    rest_head, rest_tail = self.next.reverse_recursive_helper()
    rest_tail.next = self
    self.next = None

    return rest_head, self

  def reverse_recursive(self):
    return self.reverse_recursive_helper()[0]

  def reverse_iterative(self):
    precursor = None
    cursor = self
    while cursor:
      cursor.next, cursor, precursor = precursor, cursor.next, cursor
    return precursor

def make_linked_list_from_list(lst):
  return (
    LinkedList(lst[0], make_linked_list_from_list(lst[1:]))
    if lst
    else None
  )

def main():
  tests = (
    (
      make_linked_list_from_list([1]),
      make_linked_list_from_list([1])
    ),
    (
      make_linked_list_from_list([1, 2]),
      make_linked_list_from_list([2, 1])
    ),
    (
      make_linked_list_from_list([1, 2, 3]),
      make_linked_list_from_list([3, 2, 1])
    ),
    (
      make_linked_list_from_list([1, 2, 3, 4]),
      make_linked_list_from_list([4, 3, 2, 1])
    ),
    (
      make_linked_list_from_list([1, 2, 3, 4, 5]),
      make_linked_list_from_list([5, 4, 3, 2, 1])
    ),
  )
  sols = (
    LinkedList.reverse_recursive,
    LinkedList.reverse_iterative,
  )

  correct_counts = {sol: 0 for sol in sols}
  for test_index, (lst, want) in enumerate(tests):
    print('Test {}:'.format(test_index + 1))
    print('lst = {}'.format(lst))
    print('want = {}'.format(want))

    for sol in sols:
      got = sol(lst.copy())
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
