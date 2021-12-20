from timeit import default_timer as timer
import numpy as np
import matplotlib.pyplot as plt

def pierwsze_imperatywna(n):
    ans = []
    i = 2 # 2 is first prime :p
    while i <= n:
        ds = []
        j = 2
        prime = True
        while j < i:
            if i % j == 0:
                prime = False
                break
            j+=1
        if prime:
            ans.append(i)
        i+=1

    return ans


def pierwsze_skladana(n):
    return [i for i in range(1,n+1) if len([j for j in range(1,i+1) if i%j == 0]) == 2]

def check_p(k):
    return 2 == len((list(filter(lambda x: k%x == 0, range(1, k+1)))))

def pierwsze_funkcyjna(n):
    return list(filter(check_p, range(1, n+1)))



if __name__ == '__main__':
    times = {'f': [], 's': [], 'i': []}
    tests = np.logspace(1, 4, 10, endpoint=False).astype(int)

    for j in tests: 
        t1 = timer()
        out_f = pierwsze_funkcyjna(j)
        t2 = timer()
        out_s = pierwsze_skladana(j)
        t3 = timer()
        out_i = pierwsze_imperatywna(j)
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

