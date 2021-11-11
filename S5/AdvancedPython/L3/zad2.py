from timeit import default_timer as timer
import matplotlib.pyplot as plt
import numpy as np

def doskonale_imperatywna(n):
    ans = []
    
    i = 2
    while i <= n:
        ds = []
        j = 1
        while j < i:
            if i % j == 0:
                ds.append(j)
            j+=1
        suma = 0
        for d in ds:
            suma+=d
        if suma == i:
            ans.append(i)
        i+=1

    return ans


def doskonale_skladana(n):
    return [i for i in range(2,n+1) if i == [s for s in [0] for d in [j for j in range(i) if j and i%j == 0] for s in [s+d]][-1]] # I have totally no idea how i can create [1,2,3,...] using only list comprehension, i.e. withou if statement and without range() :c


def check_d(k):
    return k == sum((list(filter(lambda x: k%x == 0, list(range(1, k))))))

def doskonale_funkcyjna(n):
    return list(filter(check_d, list(range(2, n+1))))



if __name__ == '__main__':
    tests = np.logspace(1, 5, 7, endpoint=False).astype(int)
    times = {'f': [], 's': [], 'i': []}

    for j in tests: 
        t1 = timer()
        out_f = doskonale_funkcyjna(j)
        t2 = timer()
        out_s = doskonale_skladana(j)
        t3 = timer()
        out_i = doskonale_imperatywna(j)
        t4 = timer()
        assert set(out_i) == set(out_f)
        assert set(out_i) == set(out_s)
        times['f'].append(t2 - t1)
        times['s'].append(t3 - t2)
        times['i'].append(t4 - t3)


    print('TIMES')
    for i, j in enumerate(tests):
        print(f"\nn = {j}\nfunctional: {times['f'][i]}\ncomprehension: {times['s'][i]}\nimparitive: {times['i'][i]}")
    
    # plot
    plt.plot(tests, np.array(times['f']), label='functional')
    plt.plot(tests, times['s'], label='comprehension')
    plt.plot(tests, times['i'], label='imparitive')
    plt.xlabel('n')
    plt.ylabel('time [s]')
    plt.legend()
    plt.show()
