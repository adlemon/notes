#!/usr/bin/python3
# binary_tree_is_balanced.py
# A binary tree is called "balanced" if the heights of the left and right
# subtrees of every node differ by at most 1. Write a function to test whether a
# binary tree is balanced.
# CCI4.4;


class BinaryTree:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        strs = []
        stack = [(self, '', ())]
        while stack:
            node, label, open_branches = stack.pop()

            strs.append('{}{}{}-> {}'.format(
                3 * ' ' if label else '',
                ''.join('|' + 3 * ' ' if is_open else 4 * ' '
                        for is_open in open_branches[:-1]),
                label,
                node.data,
            ))

            if node.right:
                stack.append((node.right, 'R', open_branches + (False, )))
            if node.left:
                stack.append((node.left, 'L',
                              open_branches + (node.right is not None, )))

        return '\n'.join(strs)

    def is_leaf(self):
        return (self.left is None) and (self.right is None)

    def height_and_is_balanced(self):
        if self.is_leaf():
            return 1, True

        if self.left is None:
            right_height, _ = self.right.height_and_is_balanced()
            return (right_height + 1), (right_height == 1)
        if self.right is None:
            left_height, _ = self.left.height_and_is_balanced()
            return (left_height + 1), (left_height == 1)

        left_height, left_is_balanced = self.left.height_and_is_balanced()
        right_height, right_is_balanced = self.right.height_and_is_balanced()

        height = max(left_height, right_height) + 1
        is_balanced = (left_is_balanced and right_is_balanced
                       and abs(left_height - right_height) <= 1)
        return height, is_balanced

    def is_balanced(self):
        return self.height_and_is_balanced()[1]


def make_binary_tree(*nodes):
    if len(nodes) == 0:
        return None
    if len(nodes) == 1:
        return BinaryTree(nodes[0])

    data, left, right = nodes
    return BinaryTree(
        data,
        make_binary_tree(*left),
        make_binary_tree(*right),
    )


def main():
    tests = (
        (
            make_binary_tree(
                1,
                (2, (3, ), (4, )),
                (5, (6, ), (7, )),
            ),
            True,
        ),
        (
            make_binary_tree(
                1,
                (2, (3, ), (4, )),
                (5, ),
            ),
            True,
        ),
        (
            make_binary_tree(
                1,
                (2, (3, ), (4, )),
                (),
            ),
            False,
        ),
        (
            make_binary_tree(
                1,
                (
                    2,
                    (
                        3,
                        (
                            4,
                            (5, ),
                            (),
                        ),
                        (),
                    ),
                    (),
                ),
                (
                    6,
                    (
                        7,
                        (
                            8,
                            (9, ),
                            (),
                        ),
                        (),
                    ),
                    (),
                ),
            ),
            False,
        ),
    )
    sols = (BinaryTree.is_balanced, )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print(f'Test {test_index + 1}:')
        print(f't =\n{data}')
        print(f'want = {want}')

        for sol in sols:
            got = sol(data)
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
