from collections import defaultdict
n = int(input().split()[0])
d = defaultdict(int,[tuple(map(int, input().split())) for _ in range(n)])
s = n
while s:
    m = max(d.keys(), key = lambda k: k if d[k] > 1 else -1)

    if d[m] == 1:
        print(len({x:y for x,y in d.items() if y!=0}))
        exit(0)

    d[m] -= 2
    d[2*m] += 1
    if d[2*m] == 1:
        s+=1
    if d[m] == 0:
        s-=1
    print(d)