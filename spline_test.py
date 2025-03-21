import numpy as np
import scipy.interpolate as interpolate
import matplotlib.pyplot as plt

x = np.array([0,  1,  2,  3,  4, 5])
y = np.array([0,  1,  2,  2,  2, 2])

t, c, k = interpolate.splrep(x, y, k=4)
N = 100
xmin, xmax = x.min(), x.max()
xx = np.linspace(xmin, xmax, N)
spline = interpolate.BSpline(t, c, k)

plt.plot(x, y, 'bo', label='Original points')
plt.plot(xx, spline(xx), 'r', label='BSpline')
plt.grid()
plt.legend(loc='best')
plt.show()
