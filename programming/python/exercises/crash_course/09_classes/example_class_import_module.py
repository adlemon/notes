#!/usr/bin/python3
# example_class_import_module.py
# Shows how to use a class in an imported module.

import example_class_module as ECM

obj1 = ECM.C1(1)
print(f'obj1.x = {obj1.x}')

obj2 = ECM.C2(2)
print(f'obj2.y = {obj2.y}')
