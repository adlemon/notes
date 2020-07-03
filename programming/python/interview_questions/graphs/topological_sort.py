#!/usr/bin/python3
# topological_sort.py
# Given a directed graph, return a sorted ordering of the nodes in the graph
# such that if there is an edge in the graph from a node u to a node v, then
# the node u appears before the node v in the list. If no such ordering exists,
# return None. Such an ordering of the nodes is called a topological ordering.
# CCI4.7; DCP10.5;


class DirectedGraph(object):
    def __init__(self, vertices, edges):
        self.adjacency_lists = {v: set() for v in vertices}
        for u, v in edges:
            self.adjacency_lists[u].add(v)

    def __str__(self):
        return '\n'.join(
            '{}: {}'.format(u, ', '.join(sorted(self.adjacency_lists[u])))
            for u in sorted(self.adjacency_lists.keys()))

    def topological_ordering(self):
        prerequisites = {v: set() for v in self.adjacency_lists}
        for u in self.adjacency_lists:
            for v in self.adjacency_lists[u]:
                prerequisites[v].add(u)

        topological_order = []
        ready_to_visit = {v for v, us in prerequisites.items() if not us}
        visited = set()
        while len(topological_order) < len(self.adjacency_lists):
            if not ready_to_visit:
                return None

            u = ready_to_visit.pop()
            topological_order.append(u)

            for v in self.adjacency_lists[u]:
                prerequisites[v].remove(u)
                if not prerequisites[v]:
                    ready_to_visit.add(v)

        return topological_order


def is_topological_order(g, vertices):
    try:
        if len(g.adjacency_lists) != len(vertices):
            return False

        for j in range(1, len(vertices)):
            for i in range(j):
                if vertices[i] in g.adjacency_lists[vertices[j]]:
                    return False

        return True
    except:
        return False


def main():
    tests = (
        (DirectedGraph(('a', 'b', 'c', 'd', 'e', 'f', 'g'), (
            ('a', 'b'),
            ('a', 'c'),
            ('b', 'd'),
            ('b', 'e'),
            ('c', 'f'),
            ('c', 'g'),
        )), True),
        (DirectedGraph(('a', 'b', 'c', 'd', 'e', 'f'), (
            ('a', 'b'),
            ('a', 'c'),
            ('d', 'e'),
            ('d', 'f'),
        )), True),
        (DirectedGraph(('a', 'b', 'c', 'd', 'e'), (
            ('a', 'b'),
            ('b', 'c'),
            ('c', 'd'),
            ('d', 'e'),
        )), True),
        (DirectedGraph(('a', 'b', 'c'), (
            ('a', 'b'),
            ('b', 'c'),
            ('c', 'a'),
        )), False),
        (DirectedGraph(('a', 'b', 'c', 'd'), (
            ('a', 'b'),
            ('b', 'c'),
            ('c', 'd'),
            ('d', 'b'),
        )), False),
    )
    sols = (DirectedGraph.topological_ordering, )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (g, has_topological_ordering) in enumerate(tests):
        print('Test {}:'.format(test_index + 1))
        print('g =\n{}'.format(g))
        print('has_topological_ordering = {}'.format(has_topological_ordering))

        for sol in sols:
            got = sol(g)
            if ((has_topological_ordering and is_topological_order(g, got))
                    or (not has_topological_ordering and got is None)):
                print('{} passes'.format(sol.__name__))
                correct_counts[sol] += 1
            else:
                print('{} fails; got = {}'.format(sol.__name__, got))

        print()

    print('Summary:')
    for sol in sols:
        print('{}: {} of {} correct'.format(sol.__name__, correct_counts[sol],
                                            len(tests)))


if __name__ == '__main__':
    main()
