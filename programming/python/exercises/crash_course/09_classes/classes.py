#!/usr/bin/python3
# classes.py
# Illustrates the basic use of classes.


class C1:
    """A simple example of a class."""
    def __init__(self, x):
        """Create a C1 object."""
        self.x = x

    def f(self, m=1):
        """Returns m times x."""
        return m * self.x

    def g(self):
        """Returns 2 times x."""
        return 2 * self.x


class C2(C1):
    """A simple example of subclass."""
    def __init__(self, x, y):
        """Create a C2 object."""
        super().__init__(x)
        self.y = y

    def g(self):
        """Returns 3 times x.

        This function overrides the corresponding function in C1."""
        return 3 * self.x

    def h(self):
        """Returns x plus y.

        This function does not have a counterpart in C1."""
        return self.x + self.y


obj1 = C1(5)
print(f'obj1.f(10) = {obj1.f(10)}')
print(f'obj1.g() = {obj1.g()}')

obj2 = C2(6, 7)
print()
print(f'obj2.f(10) = {obj2.f(10)}')
print(f'obj2.g() = {obj2.g()}')
print(f'obj2.h() = {obj2.h()}')
