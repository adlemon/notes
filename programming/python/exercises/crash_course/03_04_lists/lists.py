#!/usr/bin/python3
# lists.py
# Illustrate basic operations on lists.

# Indexing.
n = 5
lst = [(i, i - n) for i in range(n)]
print(f'lst = {lst}')
for i in range(-len(lst), len(lst)):
    print(f'lst[{i:2}] = {lst[i]}')

# Length.
lst = [0, 1, 2, 3, 4]
print(f'\nlst = {lst}')
print(f'len(lst) = {len(lst)}')

# Adding to lists.
lst = ['a', 'c', 'd']
print(f'\nlst = {lst}')

lst.insert(1, 'b')
print(f"after lst.insert(1, 'b'): lst = {lst}")

lst.append('e')
print(f"after lst.append('e'): lst = {lst}")

# Remove from lists.
lst = ['a', 'b', 'b', 'c', 'c', 'x', 'x', 'd', 'd']
print(f'\nlst = {lst}')

del lst[2]
print(f'after del lst[2]: lst = {lst}')

result = lst.pop()
print(f'after lst.pop() (result: {result}): lst = {lst}')

result = lst.pop(3)
print(f'after lst.pop(3) (result: {result}): lst = {lst}')

lst.remove('x')
print(f"after lst.remove('x'): lst = {lst}")

# Sorting lists.
lst = [4, 1, 3, 5, 2]
print(f'\nlst = {lst}')
print(f'sorted(lst) = {sorted(lst)}')
print(f'sorted(lst, reverse=True) = {sorted(lst, reverse=True)}')

lst.sort()
print(f'after lst.sort(): lst = {lst}')
lst.sort(reverse=True)
print(f'after lst.sort(reverse=True): lst = {lst}')

# Reversing lists.
lst = [0, 1, 2, 3, 4]
print(f'\nlst = {lst}')
print(f'reversed(lst) = {list(reversed(lst))}')
lst.reverse()
print(f'after lst.reverse(): lst = {lst}')

# Iterate over the elements of a list.
print('\nfor loop:')
for x in [0, 1, 2, 3, 4]:
    print(f'x = {x}')

print('\nlist comprehension:')
print([x**2 for x in range(1, 11) if (x % 2) == 0])

# Compute functions of a list.
print('\nlist functions:')
lst = [0, 1, 2, 3]
list_functions = (min, max, sum)
for list_function in list_functions:
    print(f'{list_function.__name__}({lst}) = {list_function(lst)}')

# Ranges.
print('\nrange:')
for range_args in ((5, ), (1, 5), (1, 5, 2), (5, 0, -1), (5, 0, -2)):
    expr = f"list(range({', '.join(str(x) for x in range_args)}))"
    print(f'{expr} => {eval(expr)}')

# Slices.
print('\nslices:')
slice_args_tuple = (
    ':',
    '1:',
    ':3',
    '-2:',
    ':-2',
    '1:3',
    '1:-2',
    '-4:4',
    '-4:-2',
    '::2',
    '1:-2:2',
    '::-1',
    '4:-4:-1',
)
for slice_args in slice_args_tuple:
    expr = f'[0, 1, 2, 3, 4, 5][{slice_args}]'
    print(f'{expr} => {eval(expr)})')

# Tuples.
print('\ntuples are *immutable* ordered collections of heterogeneous objects:')
print((1, ))
print((1, 2))
