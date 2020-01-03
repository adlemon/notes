# leave_one_out_products.py
# Given a list, return a list that has the same length as the original list, and
# whose ith element is the product of all of the elements in the original list
# except for the ith element. For example,
#   * given the list [1, 2, 3, 4, 5], return the list [120, 60, 40, 30, 24];
#   * given the list [3, 2, 1], return the list [2, 3, 6].
# DCP1.1;

def leave_one_out_products_brute_force(lst):
  products = len(lst) * [1]
  for i in range(len(lst)):
    for j in range(len(lst)):
      if j != i:
        products[i] *= lst[j]
  return products

def leave_one_out_products_division(lst):
  # Iterate over the elements of the list, counting the number of zero elements
  # and computing the product of the nonzero elements.
  num_zero = 0
  product_nonzeros = 1
  for x in lst:
    if x == 0:
      num_zero += 1
    else:
      product_nonzeros *= x

  if num_zero > 1:
    # If there is more than one zero element, then the list of leave-one-out
    # products is all zeros.
    return len(lst) * [0]
  if num_zero == 1:
    # If there is exactly one zero element, then the list of leave-one-out
    # products has the product of the nonzero elements in the index
    # corresponding to the zero element in the original list and zeros
    # everywhere else.
    return [product_nonzeros if x == 0 else 0 for x in lst]
  # If there are no zero elements, then the list of leave-one-out products is
  # obtained by dividing the product of all of the list elements by the
  # corresponding element in the original list.
  return [product_nonzeros / x for x in lst]

def leave_one_out_products_before_and_after(lst):
  # Compute the lists
  #   product_before[i] = lst[0] * ... * lst[i-1]
  #                     = product_before[i-1] * lst[i-1]
  # and
  #   product_after[i] = lst[i+1] * ... * lst[-1]
  #                    = lst[i+1] * product_after[i+1].
  product_before = len(lst) * [1]
  product_after = len(lst) * [1]
  for i in range(1, len(lst)):
    product_before[i] = product_before[i-1] * lst[i-1]
    product_after[-(i+1)] = product_after[-i] * lst[-i]
  # The ith element of the list of leave-one-out products is
  #   lst[0] * ... * lst[i-1] * lst[i+1] * ... * lst[-1]
  #     = product_before[i] * product_after[i].
  return [b * a for b, a in zip(product_before, product_after)]

def main():
  tests = (
    ([1, 2, 3, 4, 5], [120, 60, 40, 30, 24]),
    ([3, 2, 1], [2, 3, 6]),
    ([0, 1, 2, 3], [6, 0, 0, 0]),
    ([0, 1, 0, 3], [0, 0, 0, 0]),
  )
  sols = (
    leave_one_out_products_brute_force,
    leave_one_out_products_division,
    leave_one_out_products_before_and_after,
  )

  correct_counts = {sol.__name__: 0 for sol in sols}
  for test_index, (lst, want) in enumerate(tests):
    print('Test {}: lst = {}, want = {}'.format(test_index + 1, lst, want))
    for sol in sols:
      got = sol(lst)
      if got == want:
        correct_counts[sol.__name__] += 1
        print('{} passes'.format(sol.__name__))
      else:
        print('{} fails; got = {}'.format(sol.__name__, got))
    print()

  print('Summary:')
  for sol in sols:
    print(
      '{}: {} of {} correct'.format(
        sol.__name__
        correct_counts[sol.__name__],
        len(tests)
      )
    )

if __name__ == '__main__':
  main()
