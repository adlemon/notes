#!/usr/bin/python3
# write_read_json.py
# Illustrates writing data to and reading data from JSON files.

import json

filename = 'write_read_json_data.json'
data = {1: 'one', 'two': 2}

# Write the data to the JSON file.
with open(filename, 'w') as f:
    json.dump(data, f)

# Read the data from the JSON file.
with open(filename) as f:
    x = json.load(f)
    print(f'read data: {x}')
