import numpy as np

def tabliczka(x1, x2, y1, y2):
    max_len = len(str(x2 * y2))
    xs = np.arange(x1, x2 + 1)
    ys = np.arange(y1, y2 + 1)
    
    line = ''.join(str(n).rjust(max_len + 1) for n in xs)
    line = ''.ljust(max_len + 1) + line
    print(line)

    xs = np.insert(xs, 0, 1)
    for y in ys:
        xys = y * xs
        line = ''.join(str(n).rjust(max_len + 1) for n in xys)
        print(line)


tabliczka(95, 105, 8, 12)
# tabliczka(3, 5, 2, 4)