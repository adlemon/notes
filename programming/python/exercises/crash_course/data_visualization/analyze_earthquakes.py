#!/usr/bin/python3
# analyze_earthquakes.py

import json

from plotly.graph_objs import Scattergeo, Layout
from plotly import offline

# Load the data.
mags, titles, lons, lats = [], [], [], []
with open('data/eq_data_30_day_m1.json') as f:
    data = json.load(f)

    for earthquake in data['features']:
        try:
            mags.append(earthquake['properties']['mag'])
            titles.append(earthquake['properties']['title'])
            lon, lat, _ = earthquake['geometry']['coordinates']
            lons.append(lon)
            lats.append(lat)
        except:
            print(f'failed to parse: {earthquake}')

# Draw a map of the earthquakes.
offline.plot(
    {
        'data': [
            {
                'type': 'scattergeo',
                'lon': lons,
                'lat': lats,
                'text': titles,
                'marker': {
                    'size': [5 * mag for mag in mags],
                    'color': mags,
                    'colorscale': 'Portland',
                    'colorbar': {
                        'title': 'Magnitude'
                    },
                },
            },
        ],
        'layout':
        Layout(title='Earthquakes'),
    },
    filename='earthquakes_map.html',
)
