import numpy as np
import matplotlib.pyplot as plt


def f(t):
    return np.exp(-t)*np.power((((32.*np.exp(2.*t))/200.) + (np.exp(99.*t)/200.) + ((167.*np.exp(-t))/200.)), 100)


ts = np.linspace(0.0005, 0.0006, num=2000)
ys = f(ts)
plt.plot(ts, ys)
plt.show()

# t = 0.000575
print(f(0.000575))