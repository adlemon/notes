#!/usr/bin/python3
# binary_search_tree_successor.py
# The "successor" of a node in a binary search tree is the node that comes after
# the given node in an in-order traversal of tree. Given a binary search tree
# with links both from parent to child and child to parent, and a node in the
# tree, return the successor of the given node in the tree.
# CCI4.6;


class BinaryTreeNode:
    def __init__(self, value, parent=None, left=None, right=None):
        self.value = value
        self.parent = parent
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.value)


class BinarySearchTree:
    def __init__(self):
        self._root = None

    def __str__(self):
        if self._root is None:
            return '<Empty>'

        strs = []
        stack = [(self._root, '', ())]
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

    def insert(self, value):
        if self._root is None:
            self._root = BinaryTreeNode(value)
            return

        cursor = self._root
        while True:
            if value < cursor.value:
                if cursor.left is None:
                    cursor.left = BinaryTreeNode(value, cursor)
                    return
                cursor = cursor.left
            else:
                if cursor.right is None:
                    cursor.right = BinaryTreeNode(value, cursor)
                    return
                cursor = cursor.right

    def find(self, value):
        if self._root is None:
            return None

        cursor = self._root
        while cursor:
            if value == cursor.value:
                return cursor
            elif value < cursor.value:
                cursor = cursor.left
            elif value > cursor.value:
                cursor = cursor.right

        return None

    def find_successor_in_order(self, target_node):
        # Perform an in-order traversal of the tree. When we process the target
        # node, we set a flag telling us to return the next node that we
        # process.
        stack = [[self._root, False]]
        return_next_node = False
        while stack:
            node, is_left_processed = stack[-1]

            if node.left and not is_left_processed:
                stack[-1][1] = True
                stack.append([node.left, False])
                continue
            else:
                stack.pop()
                if return_next_node:
                    return node
                if node == target_node:
                    return_next_node = True
                if node.right:
                    stack.append([node.right, False])

        return None

    def find_successor_backtrack(self, target_node):
        # There are two cases to consider.
        #   (1) If the target_node has a right child, then the next node that we
        #       process in an in-order traversal is obtained by going to the
        #       right once, and then left as far as we can.
        if target_node.right is not None:
            cursor = target_node.right
            while cursor.left:
                cursor = cursor.left
            return cursor

        # (2) If the target_node does not have a right child, then we travel up
        #     the tree until we find a node whose left child is the previous
        #     node that we visited. This node is the successor of the target
        #     node. Note that it is possible that we do not find such a node --
        #     in this case the target node is the last node processed in an
        #     in-order traversal, and we return None.
        previous = target_node
        cursor = previous.parent
        while cursor and (cursor.left is not previous):
            previous = cursor
            cursor = cursor.parent
        return cursor


def main():
    complete_bst = BinarySearchTree()
    for x in (4, 2, 1, 3, 6, 5, 7):
        complete_bst.insert(x)
    right_bst = BinarySearchTree()
    for x in (1, 2, 3, 4, 5, 6, 7):
        right_bst.insert(x)
    left_bst = BinarySearchTree()
    for x in (7, 6, 5, 4, 3, 2, 1):
        left_bst.insert(x)
    incomplete_bst = BinarySearchTree()
    for x in (3, 1, 2, 6, 5, 4, 7):
        incomplete_bst.insert(x)

    tests = [((t, t.find(x)), t.find(x + 1))
             for t in (complete_bst, right_bst, left_bst, incomplete_bst)
             for x in range(1, 8)]
    sols = (
        BinarySearchTree.find_successor_in_order,
        BinarySearchTree.find_successor_backtrack,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print(f'Test {test_index + 1}:')
        print(f't =\n{data[0]}\nx = {data[1]}\nwant = {want}')

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
