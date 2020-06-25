import random

import plotly


class Die:
    """Class representing a single die."""
    def __init__(self, num_sides=6):
        """Initializes a die with num_sides (which has a default value of 6)."""
        self.num_sides = num_sides

    def roll(self):
        """Returns a single roll of the die."""
        return random.randint(1, self.num_sides)


# Simulating rolling the die.
d = Die()
roll_counts = {}
for _ in range(1000):
    r = d.roll()
    roll_counts[r] = roll_counts.get(r, 0) + 1

roll_values = sorted(roll_counts)
roll_counts = [roll_counts[roll_value] for roll_value in roll_values]

# Make a histogram of the results.
plotly.offline.plot(
    {
        'data': [plotly.graph_objs.Bar(x=roll_values, y=roll_counts)],
        'layout':
        plotly.graph_objs.Layout(
            title='1000 Results of Rolling a Six-Sided Die Once',
            xaxis={'title': 'Roll Value'},
            yaxis={'title': 'Number of Rolls'},
        ),
    },
    filename='six_sided_die.html',
)

# Simulating rolling the die twice.
roll_twice_counts = {}
for _ in range(1000):
    r = d.roll() + d.roll()
    roll_twice_counts[r] = roll_twice_counts.get(r, 0) + 1

roll_twice_values = sorted(roll_twice_counts)
roll_twice_counts = [roll_twice_counts[r] for r in roll_twice_values]

plotly.offline.plot(
    {
        'data':
        [plotly.graph_objs.Bar(x=roll_twice_values, y=roll_twice_counts)],
        'layout':
        plotly.graph_objs.Layout(
            title='1000 Results of Rolling a Six-Sided Die Twice',
            xaxis={'title': 'Sum of Roll Values'},
            yaxis={'title': 'Number of Roll Pairs'})
    },
    filename='six_sided_die_twice.html',
)
