#!/usr/bin/python3
# linked_list_saw.py
# Given a linked list x[0] -> ... -> x[n-1], rearrange the nodes in the list to
# produce a list y[0] -> ... -> y[n-1] such that
#   y[i] <= y[i+1], i = 0, 2, 4, ...
#   y[i] >= y[i+1], i = 1, 3, 5, ...
# For example, given the list 1 -> 3 -> 4 -> 2 -> 5, you could return the list
# 1 -> 3 -> 2 -> 5 -> 4.
# DCP3.3;

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
    return LinkedList(self.data, self.next.copy() if self.next else None)

  def is_sawtooth(self):
    expect_nondecreasing = True
    cursor1 = self
    cursor2 = self.next
    while cursor2:
      if expect_nondecreasing:
        if cursor2.data < cursor1.data:
          return False
      else:
        if cursor2.data > cursor1.data:
          return False
      cursor1, cursor2 = cursor2, cursor2.next
      expect_nondecreasing = not expect_nondecreasing

    return True

  # We will iterate through the list maintaining variables to a node cursor1
  # and its successor cursor2. If cursor1 and cursor2 do not have the expected
  # relationship, then we swap them. Let cursor0 be the predecessor of cursor1.
  # We claim that if cursor1 had its expected relationship with cursor0, then
  # cursor2 will have the expected relationship with cursor0 after we swap
  # cursor1 and cursor2. There are two cases to consider.
  #   (1) Suppose we expect cursor1 <= cursor2, but it is actually the case that
  #       cursor1 > cursor2. Additionally, suppose that cursor1 had its expected
  #       relationship with cursor0: that is, cursor0 >= cursor1. Then, by
  #       transitivity, we have that cursor0 >= cursor1 > cursor2. Thus, cursor2
  #       has the expected relationship with cursor0 after we swap cursor1 and
  #       cursor2.
  #   (2) Suppose we expect cursor1 >= cursor2, but it is actually the case that
  #       cursor1 < cursor2. Additionally, suppose that cursor1 had its expected
  #       relationship with cursor0: that is, cursor0 <= cursor1. Then, by
  #       transitivity, we have that cursor0 <= cursor1 < cursor2. Thus, cursor2
  #       has the expected relationship with cursor0 after we swap cursor1 and
  #       cursor2.
  def sawtooth_parity(self):
    cursor1 = self
    cursor2 = self.next
    expect_nondecreasing = True
    while cursor2:
      if (
        (expect_nondecreasing and cursor2.data < cursor1.data)
        or (not expect_nondecreasing and cursor2.data > cursor1.data)
      ):
        cursor1.data, cursor2.data = cursor2.data, cursor1.data
      cursor1, cursor2 = cursor2, cursor2.next
      expect_nondecreasing = not expect_nondecreasing

    return self

  def sawtooth_two_step(self):
    cursor1 = self
    cursor2 = self.next
    while cursor2:
      if cursor1.data > cursor2.data:
        cursor1.data, cursor2.data = cursor2.data, cursor1.data
      cursor1, cursor2 = cursor2, cursor2.next

      if not cursor2:
        break

      if cursor1.data < cursor2.data:
        cursor1.data, cursor2.data = cursor2.data, cursor1.data
      cursor1, cursor2 = cursor2, cursor2.next

    return self

def make_linked_list_from_list(lst):
  return (
    LinkedList(lst[0], make_linked_list_from_list(lst[1:]))
    if lst
    else None
  )

def main():
  tests = (
    make_linked_list_from_list([1, 2, 3, 4, 5]),
    make_linked_list_from_list([5, 4, 3, 2, 1]),
    make_linked_list_from_list([1, 2]),
    make_linked_list_from_list([2, 1]),
    make_linked_list_from_list([1, 2, 3]),
    make_linked_list_from_list([1, 3, 2]),
    make_linked_list_from_list([2, 1, 3]),
    make_linked_list_from_list([2, 3, 1]),
    make_linked_list_from_list([3, 1, 2]),
    make_linked_list_from_list([3, 2, 1]),
  )
  sols = (
    LinkedList.sawtooth_parity,
    LinkedList.sawtooth_two_step,
  )

  correct_counts = {sol: 0 for sol in sols}
  for lst in tests:
    print('lst = {}'.format(lst))
    for sol in sols:
      got = sol(lst.copy())
      if got.is_sawtooth():
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
