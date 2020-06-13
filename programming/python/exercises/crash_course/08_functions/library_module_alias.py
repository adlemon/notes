#!/usr/bin/python3
# library_module_alias.py
# Illustrates loading a module under an alias.

import library_example as lib

print(f'lib.x = {lib.x}')
print('calling lib.f():', end=' ')
lib.f()
