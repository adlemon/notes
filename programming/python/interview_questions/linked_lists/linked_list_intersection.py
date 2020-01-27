#!/usr/bin/python3
# linked_list_intersection.py
# Given two linked lists, return the first node at which the lists intersect,
# or None if the lists do not intersect. You may assume that the lists do not
# have cycles.
# DCP3.4;

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

  def __len__(self):
    return 1 + (len(self.next) if self.next else 0)

def make_intersecting_linked_lists(lst1, lst2, lst12):
  dummy1 = tail1 = LinkedList(None)
  dummy2 = tail2 = LinkedList(None)

  for x in lst1:
    tail1.next = LinkedList(x)
    tail1 = tail1.next
  for x in lst2:
    tail2.next = LinkedList(x)
    tail2 = tail2.next
  intersection_node = None
  for x in lst12:
    tail1.next = tail2.next = LinkedList(x)
    if not intersection_node:
      intersection_node = tail1.next
    tail1 = tail1.next
    tail2 = tail2.next

  return (dummy1.next, dummy2.next), intersection_node

def linked_list_intersection_length_difference(lst1, lst2):
  # Compute the lengths of the two lists.
  len1 = len(lst1)
  len2 = len(lst2)

  # Create cursors for the two lists, and advance the cursor for the longer list
  # by the difference in list lengths.
  cursor1 = lst1
  cursor2 = lst2
  if len1 > len2:
    for _ in range(len1 - len2):
      cursor1 = cursor1.next
  elif len2 > len1:
    for _ in range(len2 - len1):
      cursor2 = cursor2.next

  # Move the cursors forward together until we find the intersection or we reach
  # the ends of the lists.
  while cursor1 and cursor2:
    if cursor1 == cursor2:
      return cursor1
    cursor1 = cursor1.next
    cursor2 = cursor2.next

  return None

def linked_list_intersection_two_cursor(lst1, lst2):
  # We create two cursors, cursor12 and cursor21. We move cursor12 through lst1
  # and then through lst2; we move cursor21 through lst2 and then through lst1.
  # We claim that if the lists intersect, then cursor12 and cursor21 will meet
  # for the first time at the first node of intersection; moreover, if the lists
  # do not intersect, then cursors will simultaneously be None at some point.
  # Case I: the lists intersect
  # Let n1 be the number of nodes in lst1 before the intersection node, n2 be
  # the number of nodes in lst2 before the intersection node, and n12 be the
  # number of nodes including and after the intersection node. After we advance
  # cursor12 n1 + n2 + n12 times, then cursor12 will be at the intersection node
  # because it will have gone through lst1 (n1 + n12 increments), and it will
  # have gone through the portion of lst2 before the intersection node (n2
  # increments). Similarly, after we advance cursor21 n1 + n2 + n12 times, then
  # cursor21 will be at the intersection node because it will have gone through
  # lst2 (n2 + n12 increments), and it will have gone through the portion of
  # lst1 before the intersection node (n1 increments). Thus, the two cursors
  # will meet at the first intersection node after n1 + n2 + n12 increments.
  # Case II: the lists do not intersect
  # Case II(a): the lists have the same length
  # If the lists have the same length, then we can find the intersection node by
  # iterating through the lists in tandem. If the lists do not intersect, then
  # we will reach the end of both lists at the same time, and both of the
  # cursors will be None.
  # Case II(b): the lists have different lengths
  # If the lists have different lengths and do not intersect, then after
  # n1 + n2 + 2 * n12, both cursors will have traversed both lists, and will
  # therefore be None.
  cursor12 = lst1
  cursor21 = lst2
  while cursor12 or cursor21:
    if cursor12 is None:
      cursor12 = lst2
    if cursor21 is None:
      cursor21 = lst1

    if cursor12 == cursor21:
      return cursor12

    cursor12 = cursor12.next
    cursor21 = cursor21.next

def main():
  tests = (
    make_intersecting_linked_lists([11, 12, 13], [21, 22, 23], [1, 2, 3]),
    make_intersecting_linked_lists([], [21, 22, 23], [1, 2, 3]),
    make_intersecting_linked_lists([11, 12, 13], [], [1, 2, 3]),
    make_intersecting_linked_lists([], [], [1, 2, 3]),
    make_intersecting_linked_lists([11, 12, 13], [21, 22, 23], []),
    make_intersecting_linked_lists([1, 2, 3], [1, 2, 3], []),
  )
  sols = (
    linked_list_intersection_length_difference,
    linked_list_intersection_two_cursor,
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
      '{}: {} of {} correct'.format(
        sol.__name__,
        correct_counts[sol],
        len(tests)
      )
    )

if __name__ == '__main__':
  main()
