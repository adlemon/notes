#!/usr/bin/python3
# binary_tree_path_sum_count.py
# You are a given a binary tree whose values are integers (which may be positive
# or negative) and a target integer. Return the number of paths in the tree
# (which may or may not start at the root and may or may not end at a leaf) such
# that the sum of the values of the nodes in the path is equal to the target
# integer.
# CCI4.12;


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
                stack.append((node.left, 'L',
                              open_branches + (node.right is not None, )))

        return '\n'.join(str_lines)

    def path_sum_count_sums_list(self, target_value, prefix_sums=None):
        prefix_sums = prefix_sums or []
        path_sums = [path_sum + self.value for path_sum in prefix_sums]
        path_sums.append(self.value)

        path_sum_count = sum(path_sum == target_value
                             for path_sum in path_sums)
        if self.left:
            path_sum_count += self.left.path_sum_count_sums_list(
                target_value, path_sums)
        if self.right:
            path_sum_count += self.right.path_sum_count_sums_list(
                target_value, path_sums)

        return path_sum_count

    def path_sum_count_sums_map(self, target_value):
        return self.path_sum_count_sums_map_helper(target_value, 0, {0: 1})

    def path_sum_count_sums_map_helper(self, target_value, sum_to_root,
                                       sum_to_root_counts):
        sum_to_root += self.value
        # The sum of a path v1, ..., vk in the tree, where vk is the current
        # node, is the sum from the root to vk minus the sum from the root to
        # the parent of v1. We want to count the number of paths such that
        #   sum(root to vk) - sum(root to parent of v1) = target_value.
        # Rearranging this equation, we find that
        #   sum(root to parent of v1) = sum(root to vk) - target_value.
        # Thus, the number of paths that end at vk and have the target_value is
        # the number of paths with value sum(root_to_vk) - target_value.
        path_sum_count = sum_to_root_counts.get(sum_to_root - target_value, 0)

        sum_to_root_counts[sum_to_root] = (
            sum_to_root_counts.get(sum_to_root, 0) + 1)

        if self.left:
            path_sum_count += self.left.path_sum_count_sums_map_helper(
                target_value, sum_to_root, sum_to_root_counts)
        if self.right:
            path_sum_count += self.right.path_sum_count_sums_map_helper(
                target_value, sum_to_root, sum_to_root_counts)

        sum_to_root_counts[sum_to_root] -= 1
        if sum_to_root_counts[sum_to_root] == 0:
            del sum_to_root_counts[sum_to_root]

        return path_sum_count


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
    tests = ((
        (
            make_binary_tree(
                3,
                (
                    1,
                    (-1, (), (3, )),
                    (2, (-3, ), ()),
                ),
                (
                    2,
                    (-3, (3, (), (-2, )), ()),
                    (4, (-5, (), (-1, )), ()),
                ),
            ),
            3,
        ),
        9,
    ), )
    sols = (
        BinaryTree.path_sum_count_sums_list,
        BinaryTree.path_sum_count_sums_map,
    )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print(f'Test {test_index + 1}:')
        print('t =\n{}\nvalue = {}'.format(*data))
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
