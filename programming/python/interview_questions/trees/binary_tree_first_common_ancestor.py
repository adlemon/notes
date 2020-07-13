#!/usr/bin/python3
# binary_tree_first_common_ancestor.py
# You are given a binary tree (not necessarily a binary search tree) and two
# nodes in the tree. Return the first common ancestor of the two nodes in the
# tree.
# CCI4.8;


class FirstCommonAncestorSearchState:
    def __init__(self, has_node1, has_node2, first_common_ancestor=None):
        self.has_node1 = has_node1
        self.has_node2 = has_node2
        self.first_common_ancestor = first_common_ancestor


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
                ''.join(('|' if is_open else ' ') + 3 * ' '
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

    def first_common_ancestor(self, node1, node2):
        return (self.first_common_ancestor_helper(node1,
                                                  node2).first_common_ancestor)

    def first_common_ancestor_helper(self, node1, node2):
        has_node1 = (self == node1)
        has_node2 = (self == node2)
        for child in (self.left, self.right):
            if not child:
                continue

            child_search = child.first_common_ancestor_helper(node1, node2)
            if child_search.first_common_ancestor:
                return child_search

            has_node1 = has_node1 or child_search.has_node1
            has_node2 = has_node2 or child_search.has_node2

        return FirstCommonAncestorSearchState(
            has_node1,
            has_node2,
            self if (has_node1 and has_node2) else None,
        )


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
    t1 = make_binary_tree(
        1,
        (2, (3, ), (4, )),
        (5, (6, ), (7, )),
    )
    print(t1)

    t2 = make_binary_tree(
        1,
        (2, (), (3, (4, ), ())),
        (5, (6, (), (7, )), ()),
    )
    print(t2)

    tests = (
        ((t1, t1.left.left, t1.left.right), t1.left),
        ((t1, t1.left, t1.right), t1),
        ((t1, t1.left.right, t1.right.left), t1),
        ((t1, t1.left, BinaryTree(0)), None),
        ((t1, BinaryTree(0), BinaryTree(0)), None),
        ((t2, t2.left.right.left, t2.right.left.right), t2),
    )
    sols = (BinaryTree.first_common_ancestor, )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, ((t, node1, node2), want) in enumerate(tests):
        print(f'Test {test_index + 1}:')
        print(f't =\n{t}')
        print(f'node1.value = {node1.value}, node2.value = {node2.value}')
        print(f'want.value = {want.value if want else None}')

        for sol in sols:
            got = sol(t, node1, node2)
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
