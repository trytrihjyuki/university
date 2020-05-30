import random
import sys
import time

# N = 6
N = int(sys.argv[1])
restart = 0

def placeQueens():
    global restart
    diffs = set()
    sums = set()
    rows = []
    for i in range(N):
        rows.append(i)
    random.shuffle(rows)
    for q in range(N):
        random.shuffle(rows)
        flag = True
        for row in rows:
            if ((q+row) not in sums) and ((q-row) not in diffs):
                flag = False
                rows.remove(row)
                sums.add(q+row)
                diffs.add(q-row)
                break
        if flag:
            restart+=1
            return False
    return True

#I
# good = 0
# tests = 1000000
# for i in range(tests):
    # restart = 0
    # placeQueens()
    # if restart == 0:
        # good+=1
# print("{} no restarts on {} tests: {}%".format(good, tests, float((good/tests)*100)))

#II
t_end = time.time() + 60
flag = False
while time.time() < t_end and (not flag):
    flag = placeQueens()