import matplotlib.pyplot as plt

x = list(range(1, 6))
y = [xx**2 for xx in x]

plt.style.use('seaborn')
fig, ax = plt.subplots()
ax.scatter(
    x,
    y,
    s=200,
    c=(
        (
            0,  # R
            0,  # G
            1,  # B
        ), ))
ax.set_title('Squares', fontsize=24)
ax.set_xlabel('x', fontsize=14)
ax.set_ylabel('x^2', fontsize=14)
ax.tick_params(axis='both', which='major', labelsize=14)
ax.axis([min(x) - 1, max(x) + 1, min(y) - 1, max(y) + 1])

plt.show()
