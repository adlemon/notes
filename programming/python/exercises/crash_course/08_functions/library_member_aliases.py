#!/usr/bin/python3
# library_member_aliases.py
# Illustrates loading members of a module under aliases.

from library_example import x as lib_x
from library_example import f as lib_fun

print(f'lib_x = {lib_x}')
print('calling lib_fun:', end=' ')
lib_fun()
