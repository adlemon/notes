#!/usr/bin/python3
# binary_tree_level_lists.py
# Given a binary tree, construct a list lst such that, for each d, lst[d] is a
# linked list containing all of the nodes in the tree at depth d, ordered from
# left to right.
# CCI4.3;


class LinkedListNode:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

    def __str__(self):
        return str(self.data)


class LinkedList:
    def __init__(self):
        self._head = self._tail = LinkedListNode(None)
        self._length = 0

    def _nodes(self):
        nodes = []
        cursor = self._head.next
        while cursor:
            nodes.append(cursor)
            cursor = cursor.next
        return nodes

    def __str__(self):
        return ' -> '.join(str(node.data) for node in self._nodes())

    def __eq__(self, other):
        if type(other) != type(self):
            return False

        self_cursor = self._head.next
        other_cursor = other._head.next
        while (self_cursor is not None) and (other_cursor is not None):
            if self_cursor.data != other_cursor.data:
                return False
            self_cursor = self_cursor.next
            other_cursor = other_cursor.next

        return (self_cursor is None) and (other_cursor is None)

    def append(self, data):
        self._tail.next = LinkedListNode(data)
        self._tail = self._tail.next


class BinaryTreeNode:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.data)


class BinaryTree:
    def __init__(self, root):
        self.root = root

    def __str__(self):
        strs = []

        stack = [(self.root, '', ())]
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

    def level_linked_lists_breadth_first(self):
        current_level_nodes = [self.root]
        level_lists = []
        while current_level_nodes:
            current_level_list = LinkedList()
            next_level_nodes = []
            for node in current_level_nodes:
                current_level_list.append(node)
                if node.left:
                    next_level_nodes.append(node.left)
                if node.right:
                    next_level_nodes.append(node.right)

            level_lists.append(current_level_list)
            current_level_nodes = next_level_nodes

        return level_lists

    def level_linked_lists_depth_first(self):
        stack = [(self.root, 0)]
        level_lists = []
        while stack:
            node, depth = stack.pop()

            if depth >= len(level_lists):
                level_lists.append(LinkedList())
            level_lists[depth].append(node)

            if node.right:
                stack.append((node.right, depth + 1))
            if node.left:
                stack.append((node.left, depth + 1))

        return level_lists


def make_linked_list_from_values(*args):
    lst = LinkedList()
    for x in args:
        lst.append(x)
    return lst


def level_lists_str(level_lists):
    return '\n'.join(f'{depth}: {nodes}'
                     for depth, nodes in enumerate(level_lists))


def main():
    trees = (
        BinaryTree(
            BinaryTreeNode(
                1,
                BinaryTreeNode(
                    2,
                    BinaryTreeNode(4),
                    BinaryTreeNode(5),
                ),
                BinaryTreeNode(
                    3,
                    BinaryTreeNode(6),
                    BinaryTreeNode(7),
                ),
            )),
        BinaryTree(
            BinaryTreeNode(
                1,
                BinaryTreeNode(
                    2,
                    None,
                    BinaryTreeNode(5),
                ),
                BinaryTreeNode(
                    3,
                    BinaryTreeNode(6),
                    BinaryTreeNode(7),
                ),
            )),
        BinaryTree(
            BinaryTreeNode(
                1,
                BinaryTreeNode(
                    2,
                    BinaryTreeNode(4),
                    None,
                ),
                BinaryTreeNode(
                    3,
                    BinaryTreeNode(6),
                    BinaryTreeNode(7),
                ),
            )),
        BinaryTree(
            BinaryTreeNode(
                1,
                BinaryTreeNode(
                    2,
                    BinaryTreeNode(4),
                    BinaryTreeNode(5),
                ),
                BinaryTreeNode(
                    3,
                    None,
                    BinaryTreeNode(7),
                ),
            )),
        BinaryTree(
            BinaryTreeNode(
                1,
                BinaryTreeNode(
                    2,
                    BinaryTreeNode(4),
                    BinaryTreeNode(5),
                ),
                BinaryTreeNode(
                    3,
                    BinaryTreeNode(6),
                    None,
                ),
            )),
        BinaryTree(
            BinaryTreeNode(
                1,
                BinaryTreeNode(
                    2,
                    BinaryTreeNode(4),
                    None,
                ),
                BinaryTreeNode(
                    3,
                    None,
                    BinaryTreeNode(7),
                ),
            )),
        BinaryTree(
            BinaryTreeNode(
                1,
                None,
                BinaryTreeNode(
                    3,
                    BinaryTreeNode(6),
                    BinaryTreeNode(7),
                ),
            )),
    )
    level_linked_lists = (
        [
            make_linked_list_from_values(trees[0].root),
            make_linked_list_from_values(
                trees[0].root.left,
                trees[0].root.right,
            ),
            make_linked_list_from_values(
                trees[0].root.left.left,
                trees[0].root.left.right,
                trees[0].root.right.left,
                trees[0].root.right.right,
            ),
        ],
        [
            make_linked_list_from_values(trees[1].root),
            make_linked_list_from_values(
                trees[1].root.left,
                trees[1].root.right,
            ),
            make_linked_list_from_values(
                trees[1].root.left.right,
                trees[1].root.right.left,
                trees[1].root.right.right,
            ),
        ],
        [
            make_linked_list_from_values(trees[2].root),
            make_linked_list_from_values(
                trees[2].root.left,
                trees[2].root.right,
            ),
            make_linked_list_from_values(
                trees[2].root.left.left,
                trees[2].root.right.left,
                trees[2].root.right.right,
            ),
        ],
        [
            make_linked_list_from_values(trees[3].root),
            make_linked_list_from_values(
                trees[3].root.left,
                trees[3].root.right,
            ),
            make_linked_list_from_values(
                trees[3].root.left.left,
                trees[3].root.left.right,
                trees[3].root.right.right,
            ),
        ],
        [
            make_linked_list_from_values(trees[4].root),
            make_linked_list_from_values(
                trees[4].root.left,
                trees[4].root.right,
            ),
            make_linked_list_from_values(
                trees[4].root.left.left,
                trees[4].root.left.right,
                trees[4].root.right.left,
            ),
        ],
        [
            make_linked_list_from_values(trees[5].root),
            make_linked_list_from_values(
                trees[5].root.left,
                trees[5].root.right,
            ),
            make_linked_list_from_values(
                trees[5].root.left.left,
                trees[5].root.right.right,
            ),
        ],
        [
            make_linked_list_from_values(trees[6].root),
            make_linked_list_from_values(trees[6].root.right),
            make_linked_list_from_values(
                trees[6].root.right.left,
                trees[6].root.right.right,
            ),
        ],
    )
    sols = (
        BinaryTree.level_linked_lists_breadth_first,
        BinaryTree.level_linked_lists_depth_first,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(zip(trees, level_linked_lists)):
        print(f'Test {test_index + 1}:')
        print(f't =\n{data}')
        print(f'want =\n{level_lists_str(want)}')

        for sol in sols:
            got = sol(data)
            if all(got_list == want_list
                   for got_list, want_list in zip(got, want)):
                print(f'{sol.__name__} passes')
                correct_counts[sol] += 1
            else:
                print(f'{sol.__name__} fails; got =\n{level_lists_str(got)}')

        print()

    print('Summary:')
    for sol in sols:
        print(f'{sol.__name__}: {correct_counts[sol]} of {len(trees)} correct')

    return got, want


if __name__ == '__main__':
    got, want = main()
