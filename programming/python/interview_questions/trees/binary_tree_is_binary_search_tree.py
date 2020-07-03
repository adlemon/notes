#!/usr/bin/python3
# binary_tree_is_binary_search_tree.py
# Recall that a binary tree is called a "binary search tree" if the value of
# every node is greater than or equal to the values of all nodes in the left
# subtree and less than or equal to the values of all nodes in the right
# subtree. Write a function to test whether a given binary tree is a binary
# search tree.
# CCI4.5;


class IsSearchTreeResult:
    def __init__(self, is_search_tree=False, min_value=None, max_value=None):
        self.is_search_tree = is_search_tree
        self.min_value = min_value
        self.max_value = max_value


class BinaryTree:
    def __init__(self, value, left=None, right=None):
        self.value = value
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
                node.value,
            ))

            if node.right:
                stack.append((node.right, 'R', open_branches + (False, )))
            if node.left:
                stack.append((node.left, 'L',
                              open_branches + (node.right is not None, )))

        return '\n'.join(strs)

    def is_leaf(self):
        return (self.left is None) and (self.right is None)

    def is_search_tree_get_min_max_helper(self):
        if self.is_leaf():
            return IsSearchTreeResult(True, self.value, self.value)

        if self.left is None:
            right_result = self.right.is_search_tree_get_min_max_helper()
            if not (right.is_search_tree
                    and self.value <= right_result.min_value):
                return IsSearchTreeResult()
            return IsSearchTreeResult(True, self.value, right_result.max_value)

        if self.right is None:
            left_result = self.left.is_search_tree_get_min_max_helper()
            if not (left_result.is_search_tree
                    and self.value >= left_result.max_value):
                return IsSearchTreeResult()
            return IsSearchTreeResult(True, left_result.min_value, self.value)

        left_result = self.left.is_search_tree_get_min_max_helper()
        right_result = self.right.is_search_tree_get_min_max_helper()

        if not (left_result.is_search_tree and right_result.is_search_tree and
                left_result.max_value <= self.value <= right_result.min_value):
            return IsSearchTreeResult()

        return IsSearchTreeResult(True, left_result.min_value,
                                  right_result.max_value)

    def is_search_tree_get_min_max(self):
        return self.is_search_tree_get_min_max_helper().is_search_tree

    def is_search_tree_give_min_max(self, min_value=None, max_value=None):
        if (min_value is not None) and (self.value < min_value):
            return False
        if (max_value is not None) and (self.value > max_value):
            return False
        if (self.left and not self.left.is_search_tree_give_min_max(
                min_value, self.value)):
            return False
        if (self.right and not self.right.is_search_tree_give_min_max(
                self.value, max_value)):
            return False
        return True


def make_binary_tree(*nodes):
    if len(nodes) == 0:
        return None
    if len(nodes) == 1:
        return BinaryTree(nodes[0])

    value, left_nodes, right_nodes = nodes
    return BinaryTree(
        value,
        make_binary_tree(*left_nodes),
        make_binary_tree(*right_nodes),
    )


def main():
    tests = (
        (
            make_binary_tree(1),
            True,
        ),
        (
            make_binary_tree(
                4,
                (2, (1, ), (3, )),
                (6, (5, ), (7, )),
            ),
            True,
        ),
        (
            make_binary_tree(
                4,
                (2, (1, ), (5, )),
                (6, (5, ), (7, )),
            ),
            False,
        ),
    )
    sols = (
        BinaryTree.is_search_tree_get_min_max,
        BinaryTree.is_search_tree_give_min_max,
    )

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
