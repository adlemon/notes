#!/usr/bin/python3
# example_class_import.py
# Shows how to import a class from a module.

from example_class_module import C1, C2

obj1 = C1(1)
print(f'obj1.x = {obj1.x}')

obj2 = C2(2)
print(f'obj2.y = {obj2.y}')
