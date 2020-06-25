import matplotlib.pyplot as plt
import random


class RandomWalk:
    """Class to generate random walks on a two-dimensional lattice.

    The random walk modeled by this class starts at the origin and at each step
    transitions from the point (x, y) uniformly at random to one of the 80
    points (xx, yy) such that
      1 <= ||(x, y) - (xx, yy)||_{inf} = max(|x - xx|, |y - yy|) <= 4."""
    def __init__(self):
        pass

    def _step(self):
        """Returns a step in the random walk.

        This method returns a tuple whose first element is the step in the
        x-direction and whose second element is the step in the y-dircetion."""
        while True:
            dx = random.randint(-4, 4)
            dy = random.randint(-4, 4)
            if not (dx == 0 and dy == 0):
                return dx, dy

    def walk(self, num_steps=5_000):
        """Returns a random walk with num_steps steps.

        This method returns a tuple whose first element is a list of
        x-coordinates and whose second element is a list of y-coordinates. See
        the class-level comment for a description of the walk's structure."""
        x = [0] + num_steps * [None]
        y = x.copy()
        for i in range(num_steps):
            dx, dy = self._step()
            x[i + 1] = x[i] + dx
            y[i + 1] = y[i] + dy

        return x, y


x, y = RandomWalk().walk()

plt.style.use('classic')
fig, ax = plt.subplots()
ax.scatter(x, y, s=10, c=range(len(x)), cmap=plt.cm.Blues, edgecolors='none')
ax.scatter((x[0], x[-1]), (y[0], y[-1]),
           c=('green', 'red'),
           edgecolors='none',
           s=50)
ax.xaxis.set_visible(False)
ax.yaxis.set_visible(False)
plt.show()
