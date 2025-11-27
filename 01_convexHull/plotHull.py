import matplotlib.pyplot as plt

# Read convexHull.txt
xs = []
ys = []
with open("convexHull.txt", "r") as f:
    for line in f:
        x, y = map(float, line.split())
        xs.append(x)
        ys.append(y)

# Close the hull for plotting
xs.append(xs[0])
ys.append(ys[0])

plt.figure()
plt.plot(xs, ys, marker='o')      # hull edges
plt.scatter(xs, ys)               # hull points
plt.title("Convex Hull")
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.show()
