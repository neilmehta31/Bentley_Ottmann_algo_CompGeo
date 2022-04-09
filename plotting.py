import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection

lines=[]
with open("testcases.txt") as inputfile:
    for segment in inputfile:
        x1,y1,x2,y2 = segment.split()
        # print(x1,y1,x2,y2)
        lines.append([(float(x1),float(y1)),(float(x2),float(y2))])
# print(lines)

lc = LineCollection(lines,zorder=1,label="Line segments")
fig = plt.figure()

ax1 = fig.add_subplot(1, 1, 1)
ax1.add_collection(lc)
ax1.autoscale()

x_intersections = []
y_intersections = []
with open("output.txt") as points:
    for point in points:
        x,y = point.split()
        x_intersections.append(float(x))
        y_intersections.append(float(y))
ax1.scatter(x_intersections, y_intersections, c='r',label="Intersection Points")
plt.legend()
plt.show()