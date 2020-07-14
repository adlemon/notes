#!/usr/bin/python3
# binary_search_tree_insertion_sequences.py
# You are given a binary search tree that was constructed without rebalancing.
# Return a list of all permutations of the values in the tree that could
# possibly represent the order in which the elements were inserted into the
# tree. For example, given the following tree:
#   -> 2
#      L-> 1
#      R-> 3
# you should return [[2, 1, 3], [2, 3, 1]] because the orders in which the
# values 1, 2, and 3 can be inserted into a binary search tree such that the
# binary search tree is equal to the given tree are [2, 1, 3] and [2, 3, 1].
# CCI4.9;


class BinaryTreeNode:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.value)


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def __str__(self):
        if not self.root:
            return '<Empty>'

        strs = []

        stack = [(self.root, '', ())]
        while stack:
            node, label, open_branches = stack.pop()

            strs.append('{}{}{}-> {}'.format(
                3 * ' ' if label else '',
                ''.join(('|' if is_open else ' ') + 3 * ' '
                        for is_open in open_branches[:-1]),
                label,
                node,
            ))

            if node.right:
                stack.append((node.right, 'R', open_branches + (False, )))
            if node.left:
                stack.append((node.left, 'L',
                              open_branches + (node.right is not None, )))

        return '\n'.join(strs)

    def insert(self, value):
        if not self.root:
            self.root = BinaryTreeNode(value)
            return

        cursor = self.root
        while True:
            if value <= cursor.value:
                if cursor.left:
                    cursor = cursor.left
                else:
                    cursor.left = BinaryTreeNode(value)
                    return
            else:
                if cursor.right:
                    cursor = cursor.right
                else:
                    cursor.right = BinaryTreeNode(value)
                    return


def interleave_lists(lst1, lst2):
    if not lst1:
        return [lst2]
    if not lst2:
        return [lst1]

    interleaved_lists = []
    for lst in interleave_lists(lst1[1:], lst2):
        interleaved_lists.append([lst1[0]] + lst)
    for lst in interleave_lists(lst1, lst2[1:]):
        interleaved_lists.append([lst2[0]] + lst)

    return interleaved_lists


def insertion_sequences(node):
    if not node:
        return [[]]
    if not (node.left or node.right):
        return [[node.value]]

    sequences = []
    left_sequences = insertion_sequences(node.left)
    right_sequences = insertion_sequences(node.right)
    for left_sequence in left_sequences:
        for right_sequence in right_sequences:
            for rest in interleave_lists(left_sequence, right_sequence):
                sequences.append([node.value] + rest)
    return sequences


def make_binary_search_tree(*values):
    t = BinarySearchTree()
    for x in values:
        t.insert(x)
    return t


def main():
    tests = (
        (make_binary_search_tree(1, 2, 3), [[1, 2, 3]]),
        (make_binary_search_tree(1, 3, 2), [[1, 3, 2]]),
        (make_binary_search_tree(2, 1, 3), [[2, 1, 3], [2, 3, 1]]),
        (make_binary_search_tree(3, 1, 2), [[3, 1, 2]]),
        (make_binary_search_tree(3, 2, 1), [[3, 2, 1]]),
    )
    sols = (insertion_sequences, )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print(f'Test {test_index + 1}:')
        print(f't =\n{data}')
        print(f'want = {want}')

        for sol in sols:
            got = sol(data.root)
            if sorted(got) == sorted(want):
                print(f'{sol.__name__} passes')
                correct_counts[sol] += 1
            else:
                print(f'{sol.__name__} fails; got = {got}')

        print()

    print('Summary:')
    for sol in sols:
        print(f'{sol.__name__}: {correct_counts[sol]} of {len(tests)} correct')


if __name__ == '__main__':
    main()
