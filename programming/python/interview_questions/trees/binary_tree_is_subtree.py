#!/usr/bin/python3
# binary_tree_is_subtree.py
# Define two binary trees to be equal if they have exactly the same structure,
# and corresponding nodes have the same values. Write a function to check
# whether a binary tree is equal to a subtree of another binary tree.
# CCI4.10;


class BinaryTree:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

    def __str__(self):
        str_lines = []

        stack = [(self, '', ())]
        while stack:
            node, label, open_branches = stack.pop()

            str_lines.append('{}{}{}-> {}'.format(
                3 * ' ' if label else '',
                ''.join(('|' if is_open else ' ') + 3 * ' '
                        for is_open in open_branches[:-1]),
                label,
                node.value,
            ))

            if node.right:
                stack.append((node.right, 'R', open_branches + (False, )))
            if node.left:
                stack.append(
                    (node.left, 'L', open_branches + (node.left is None, )))

        return '\n'.join(str_lines)

    def __eq__(self, other):
        if type(other) != type(self):
            return False
        return ((self.value == other.value) and (self.left == other.left)
                and (self.right == other.right))

    def copy(self):
        return BinaryTree(
            self.value,
            self.left.copy() if self.left else None,
            self.right.copy() if self.right else None,
        )

    def has_subtree_recursive(self, other):
        if self == other:
            return True
        if self.left and self.left.has_subtree_recursive(other):
            return True
        if self.right and self.right.has_subtree_recursive(other):
            return True
        return False

    def structured_pre_order_traversal(self):
        traversal = (self.value, )
        for child in (self.left, self.right):
            traversal += (child.structured_pre_order_traversal() if child else
                          (None, ))
        return traversal

    def has_subtree_structured_pre_order_traversal(self, other):
        return is_sublist(
            self.structured_pre_order_traversal(),
            other.structured_pre_order_traversal(),
        )


def is_sublist(lst1, lst2):
    for i in range(len(lst1) - len(lst2) + 1):
        is_match = True
        for j in range(len(lst2)):
            if lst1[i + j] != lst2[j]:
                is_match = False
                break
        if is_match:
            return True
    return False


def make_binary_tree(*nodes):
    if len(nodes) == 0:
        return None
    if len(nodes) == 1:
        return BinaryTree(nodes[0])

    root_value, left_nodes, right_nodes = nodes
    return BinaryTree(
        root_value,
        make_binary_tree(*left_nodes),
        make_binary_tree(*right_nodes),
    )


def main():
    trees = (
        make_binary_tree(
            1,
            (2, (3, ), (4, )),
            (5, (6, ), (7, )),
        ),
        make_binary_tree(2, (3, ), (4, )),
        make_binary_tree(5, (6, ), (7, )),
        make_binary_tree(2),
        make_binary_tree(6),
        make_binary_tree(2, (3, ), (5, )),
    )
    tests = (
        ((trees[0], trees[0].copy()), True),
        ((trees[0], trees[1]), True),
        ((trees[0], trees[2]), True),
        ((trees[0], trees[3]), False),
        ((trees[0], trees[4]), True),
        ((trees[0], trees[5]), False),
    )
    sols = (
        BinaryTree.has_subtree_recursive,
        BinaryTree.has_subtree_structured_pre_order_traversal,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print(f'Test {test_index + 1}:')
        print('t1 =\n{}\nt2 =\n{}'.format(*data))
        print(f'want = {want}')

        for sol in sols:
            got = sol(*data)
            if got == want:
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
