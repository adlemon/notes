#!/usr/bin/python3
# analyze_temperatures.py

import csv
from datetime import datetime

import matplotlib.pyplot as plt

dates, highs, lows = [], [], []
station_name = None
with open('data/sitka_weather_2018_simple.csv') as f:
    reader = csv.reader(f)
    header_row = next(reader)

    date_index = header_row.index('DATE')
    high_index = header_row.index('TMAX')
    low_index = header_row.index('TMIN')
    name_index = header_row.index('NAME')

    for i, row in enumerate(reader):
        try:
            date = datetime.strptime(row[date_index], '%Y-%m-%d')
            high = int(row[high_index])
            low = int(row[low_index])
        except ValueError:
            print(f'Error parsing date row {i}')
        else:
            dates.append(date)
            highs.append(high)
            lows.append(low)
            if i == 1:
                station_name = row[name_index].split(',')[0].title()

# Plot the daily high temperatures.
plt.style.use('seaborn')
fig, ax = plt.subplots()
ax.plot(dates, highs, c='red', alpha=0.5)
ax.plot(dates, lows, c='blue', alpha=0.5)
plt.fill_between(dates, highs, lows, facecolor='blue', alpha=0.1)
plt.title(f'Daily Temperatures for {station_name}', fontsize=24)
fig.autofmt_xdate()
plt.xlabel('Date', fontsize=16)
plt.ylabel('Temperature (F)', fontsize=16)
plt.tick_params(axis='both', which='major', labelsize=16)
plt.show()
