import math
def pierwiastek(n):
    curr_sum = 0
    i = 1
    while curr_sum <= n:
        curr_sum += 2*i - 1
        i += 1

    return i-2

# simple testing
for i in range(100000):
    assert pierwiastek(i) == math.floor(math.sqrt(i))

