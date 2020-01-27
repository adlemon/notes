#!/usr/bin/python3
# linked_list_sum_little_endian.py
# We can represent a nonnegative integer using a linked list where each node
# contains a single digit. In the "little endian" convention, the digits are
# stored from least significant to most significant. For example, the number
# 54321 is represented using the list 1 -> 2 -> 3 -> 4 -> 5. Given two linked
# lists representing nonnegative integers, return a linked list representing
# the sum of the integers. For example, given the lists 9 -> 9 (representing
# the integer 99) and 5 -> 2 (representing the integer 25), you should return
# the list 4 -> 2 -> 1 (representing the integer 124).
# DCP3.2;

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

  def __add__(self, other):
    head = tail = LinkedList(None)
    carry = 0
    while self or other or carry:
      carry, digit = divmod(
        (self.data if self else 0) + (other.data if other else 0) + carry,
        10
      )
      tail.next = LinkedList(digit)
      tail = tail.next
      if self:
        self = self.next
      if other:
        other = other.next

    return head.next

  def __eq__(self, other):
    return str(self) == str(other)

def make_linked_list_from_integer(i):
  rest, digit = divmod(i, 10)
  return LinkedList(
    digit,
    make_linked_list_from_integer(rest) if rest != 0 else None
  )

def main():
  tests = (
    (
      (
        make_linked_list_from_integer(0),
        make_linked_list_from_integer(2)
      ),
      make_linked_list_from_integer(2),
    ),
    (
      (
        make_linked_list_from_integer(1),
        make_linked_list_from_integer(2)
      ),
      make_linked_list_from_integer(3),
    ),
    (
      (
        make_linked_list_from_integer(2),
        make_linked_list_from_integer(9)
      ),
      make_linked_list_from_integer(11),
    ),
    (
      (
        make_linked_list_from_integer(63),
        make_linked_list_from_integer(72)
      ),
      make_linked_list_from_integer(135),
    ),
    (
      (
        make_linked_list_from_integer(8),
        make_linked_list_from_integer(96)
      ),
      make_linked_list_from_integer(104),
    ),
    (
      (
        make_linked_list_from_integer(8),
        make_linked_list_from_integer(996)
      ),
      make_linked_list_from_integer(1004),
    ),
    (
      (
        make_linked_list_from_integer(996),
        make_linked_list_from_integer(8)
      ),
      make_linked_list_from_integer(1004),
    ),
  )
  sols = (
    LinkedList.__add__,
  )

  correct_counts = {sol: 0 for sol in sols}
  for test_index, ((lst1, lst2), want) in enumerate(tests):
    print('Test {}:'.format(test_index + 1))
    print('lst1 = {}, lst2 = {}'.format(lst1, lst2))
    print('want = {}'.format(want))

    for sol in sols:
      got = sol(lst1, lst2)
      if got == want:
        print('{} passes'.format(sol.__name__))
        correct_counts[sol] += 1
      else:
        print('{} fails; got = {}'.format(sol.__name__, got))

    print()

  print('Summary:')
  for sol in sols:
    print(
      '{}: {} of {}'.format(
        sol.__name__,
        correct_counts[sol],
        len(tests)
      )
    )

if __name__ == '__main__':
  main()
