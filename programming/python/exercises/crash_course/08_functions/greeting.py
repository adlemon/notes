#!/usr/bin/python3
# greeting.py
# Prints greetings to the standard output.


def hello_world():
    """Prints 'Hello, World!'

    Prints the string 'Hello, World!' to the standard output."""
    print('Hello, World!')


def greet(addressee, greeting='Hello'):
    """Prints a greeting to an addressee.

    Prints a greeting to an addressee to the standard output. The addressee must
    be specified; the greeting is optional and defaults to 'Hello' if no
    greeting is specified."""
    print(f'{greeting}, {addressee}!')


hello_world()
greet(greeting='Salve', addressee='Munde')
greet(input('Enter an addressee: '))
