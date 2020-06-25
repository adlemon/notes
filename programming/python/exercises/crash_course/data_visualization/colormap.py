import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
plt.style.use('seaborn')

x = list(range(1, 1001))
y = [xx**2 for xx in x]

fig, ax = plt.subplots()
ax.scatter(x, y, c=y, cmap=plt.cm.Blues, s=10)
ax.set_title('Squares', fontsize=24)
ax.set_xlabel('x', fontsize=14)
ax.set_ylabel('x^2', fontsize=14)
ax.tick_params(axis='both', which='major', labelsize=14)
ax.yaxis.set_major_formatter(ticker.StrMethodFormatter('{x:,}'))

plt.savefig('colormap.png', bbox_inches='tight')
