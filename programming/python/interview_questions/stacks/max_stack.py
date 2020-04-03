#!/usr/bin/python3
# max_stack.py
# Implement a data structure that supports the following operations.
#   (1) push: add a value to the data structure
#   (2) pop: remove the last value added to the data structure and return it
#   (3) peek: return the last value added to the data structure (without
#       removing it from the data structure)
#   (4) max: return the maximum value currently stored in the data structure
# DCP4.1;


class MaxStackTuples(object):
    def __init__(self):
        self.values = []

    def push(self, value):
        self.values.append(
            (value, max(value, self.values[-1][1]) if self.values else value))

    def pop(self):
        if not self.values:
            raise IndexError('pop from empty MaxStack')
        return self.values.pop()[0]

    def peek(self):
        if not self.values:
            raise IndexError('peek at empty MaxStack')
        return self.values[-1][0]

    def max(self):
        if not self.values:
            raise IndexError('max from empty MaxStack')
        return self.values[-1][1]


class MaxStackTwoStacks(object):
    def __init__(self):
        self.values = []
        self.maxes = []

    def push(self, value):
        self.values.append(value)
        self.maxes.append(max(self.maxes[-1], value) if self.maxes else value)

    def pop(self):
        if not self.values:
            raise IndexError('pop from empty MaxStack')
        self.maxes.pop()
        return self.values.pop()

    def peek(self):
        if not self.values:
            raise IndexError('peek at empty MaxStack')
        return self.values[-1]

    def max(self):
        if not self.values:
            raise IndexError('max from empty MaxStack')
        return self.maxes[-1]


def main():
    tests = (
        ('push', (1, ), None),
        ('push', (3, ), None),
        ('push', (2, ), None),
        ('peek', tuple(), 2),
        ('peek', tuple(), 2),
        ('max', tuple(), 3),
        ('pop', tuple(), 2),
        ('peek', tuple(), 3),
        ('max', tuple(), 3),
        ('pop', tuple(), 3),
        ('peek', tuple(), 1),
        ('max', tuple(), 1),
        ('pop', tuple(), 1),
    )
    sols = (
        MaxStackTuples,
        MaxStackTwoStacks,
    )

    correct_counts = {sol: 0 for sol in sols}
    for sol in sols:
        print('{}:'.format(sol.__name__))
        s = sol()

        for test_index, (op, data, want) in enumerate(tests):
            print('Test {}:'.format(test_index + 1))
            print('op = {}, data = {}'.format(op, data))
            print('want = {}'.format(want))

            got = getattr(s, op)(*data)
            if got == want:
                print('Test passes')
                correct_counts[sol] += 1
            else:
                print('Test fails; got = {}'.format(got))
            print()

        print()

    print('Summary:')
    for sol in sols:
        print('{}: {} of {} correct'.format(sol.__name__, correct_counts[sol],
                                            len(tests)))


if __name__ == '__main__':
    main()
