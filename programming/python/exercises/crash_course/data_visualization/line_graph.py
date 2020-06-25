import matplotlib.pyplot as plt

x = list(range(1, 6))
y = [xx**2 for xx in x]

plt.style.use('seaborn')
fig, ax = plt.subplots()
ax.plot(x, y, linewidth=3, c='red')
ax.set_title('Squares', fontsize=24)
ax.set_xlabel('x', fontsize=14)
ax.set_ylabel('x^2', fontsize=14)
ax.tick_params(axis='both', labelsize=14)

plt.show()
