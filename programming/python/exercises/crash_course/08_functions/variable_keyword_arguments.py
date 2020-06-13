#!/usr/bin/python3
# variable_keyword_arguments.py
# Illustrates the use of arbitrary keyword arguments.


def set_in_dictionary(d, **keys):
    for key, value in keys.items():
        d[key] = value


d = {}
set_in_dictionary(d, x='1', y='2')
print(d)
