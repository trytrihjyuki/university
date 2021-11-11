import numpy as np

def eksperyment(num_tests, max_series = 3):
    results = np.zeros(num_tests)

    for i in range(num_tests):
        series_side = None
        series_len = 0
        cnt = 0

        while series_len < max_series:
            cnt += 1
            toss = np.random.choice(['T', 'E'])
            if toss == series_side:
                series_len += 1
            else:
                series_side = toss
                series_len = 1

        results[i] = cnt

    return np.average(results)


print(eksperyment(1000, 3))