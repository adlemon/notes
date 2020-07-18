#!/usr/bin/python3
# binary_search_tree_random_node.py
# Implement a binary search tree that supports the following operations:
#   * insert(value): inserts value;
#   * find(value): returns a node with the value if there is such a node;
#       returns None if there is no node with the value;
#   * delete(value): removes a node containing the value; raises an error if
#       there is no node with the value;
#   * random_value(): returns a random value, with every node equally likely.
# CCI4.11;

import random


class BinaryTreeNode:
    def __init__(self, value):
        self.value = value
        self.node_count = 1
        self.left = None
        self.right = None


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def __str__(self):
        if not self.root:
            return '<Empty>'

        str_lines = []

        stack = [(self.root, '', ())]
        while stack:
            node, label, open_branches = stack.pop()

            str_lines.append('{}{}{}-> {} [{}]'.format(
                3 * ' ' if label else '',
                ''.join(('|' if is_open else ' ') + 3 * ' '
                        for is_open in open_branches[:-1]),
                label,
                node.value,
                node.node_count,
            ))

            if node.right:
                stack.append((node.right, 'R', open_branches + (False, )))
            if node.left:
                stack.append((node.left, 'L',
                              open_branches + (node.right is not None, )))

        return '\n'.join(str_lines)

    def copy(self):
        t = BinarySearchTree()

        stack = [self.root] if self.root else []
        while stack:
            node = stack.pop()
            t.insert(node.value)
            for child in (node.left, node.right):
                if child:
                    stack.append(child)

        return t

    def insert(self, value):
        if not self.root:
            self.root = BinaryTreeNode(value)
            return

        cursor = self.root
        while True:
            cursor.node_count += 1
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

    def find(self, value):
        cursor = self.root
        while cursor:
            if value == cursor.value:
                return cursor
            elif value < cursor.value:
                cursor = cursor.left
            elif value > cursor.value:
                cursor = cursor.right
        return cursor

    def find_path(self, value):
        if not self.root:
            return None

        path = [self.root]
        while True:
            if path[-1] is None:
                return None
            elif path[-1].value == value:
                break
            elif path[-1].value < value:
                path.append(path[-1].right)
            elif path[-1].value > value:
                path.append(path[-1].left)

        return path

    def delete_node(self, path):
        # If the node to delete does not have both children, then we can promote
        # the unique child to the deleted node's place.
        if not (path[-1].left and path[-1].right):
            # Update the node counts along the path.
            for node in path:
                node.node_count -= 1

            child = path[-1].left if path[-1].left else path[-1].right
            if len(path) == 1:
                self.root = child
                return

            if path[-1].value <= path[-2].value:
                path[-2].left = child
            else:
                path[-2].right = child
            return

        # Find a maximum-value node in the left subtree and delete it.
        max_node = path[-1].left
        max_node_parent = path[-1]
        max_node_path = path + [max_node]
        while max_node.right:
            max_node_parent = max_node
            max_node = max_node.right
            max_node_path.append(max_node)
        self.delete_node(max_node_path)

        # Copy the value from the deleted node into the node to delete.
        path[-1].value = max_node.value

    def delete(self, value):
        path = self.find_path(value)
        if not path:
            raise ValueError('BinarySearchTree.delete with missing value')
        self.delete_node(path)

    def get_in_order_index(self, i):
        if not self.root:
            raise ValueError(
                'BinarySearchTree.get_in_order_index on empty tree')

        cursor = self.root
        while cursor:
            left_node_count = cursor.left.node_count if cursor.left else 0
            if i == left_node_count:
                return cursor.value
            elif i < left_node_count:
                cursor = cursor.left
            elif i > left_node_count:
                cursor = cursor.right
                i -= (left_node_count + 1)

    def random_value(self):
        if not self.root:
            raise ValueError('BinarySearchTree.random_value on empty tree')

        i = random.randrange(self.root.node_count)
        return self.get_in_order_index(i)


def main():
    m = 10
    n = 10
    n_sample = 10000

    t = BinarySearchTree()
    for x in random.sample(range(1, m + n + 1), m + n):
        t.insert(x)
    print(t)
    print(80 * '=')

    for x in range(m + 1, m + n + 1):
        t.delete(x)
    print(t)
    print(80 * '=')

    h = {}
    for _ in range(n_sample):
        x = t.random_value()
        h[x] = h.get(x, 0) + 1

    for x in sorted(h):
        print(f'{x:2} : {h[x]:4} ({h[x] / n_sample:6.2%})')


if __name__ == '__main__':
    main()
