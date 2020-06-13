#!/usr/bin/python3
# example_class_import_alias.py
# Import a class from a module with an alias.

from example_class_module import C1 as CC1, C2 as CC2

obj1 = CC1(1)
print(f'obj1.x = {obj1.x}')

obj2 = CC2(2)
print(f'obj2.y = {obj2.y}')
