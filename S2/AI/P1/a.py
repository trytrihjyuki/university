#!/usr/bin/python

import random
import time
from random import randrange
# input

with open('zad5_input.txt','r') as f:
    lines = f.readlines()

n = int(lines[0][0])
m = int(lines[0][2])

rowNumbers = []
columnNumbers = []

rows = []
columns = []

for i in range(1,n+1):
    rowNumbers.append(int(lines[i].strip()))
for i in range(n+1,m+n+1):
    columnNumbers.append(int(lines[i].strip()))

for i in range(n):
    temp = []
    for j in range(m):
        temp.append(0)
    rows.append(temp)

for j in range(m):
    temp = []
    for i in range(n):
        temp.append(0)
    columns.append(temp)

last = time.time()

niewielkieprawdopodobienstwo = 0.1
maxWaiting = 5.0

def opt_dist(row,D):
    bestAns = len(row)
    for i in range(len(row) - D + 1):
        ones = 0
        for j in range(i,i + D):
            if row[j] == 1:
                ones+=1
        allOnes = row.count(1)
        bestAns = min(bestAns, allOnes - ones + (D - ones))
    return bestAns

def getBad(t):
    ans = []
    if t == 'row':
        for i in range(n):
            if opt_dist(rows[i], rowNumbers[i]):
                ans.append(i)
    else:
        for j in range(m):
            if opt_dist(columns[j], columnNumbers[j]):
                ans.append(j)
    return ans

def clear():
    global last
    last = time.time()
    for i in range(n):
        for j in range(m):
            rows[i][j] = 0
            columns[j][i] = 0

while getBad('row') or getBad('column'):
    # print('BadRows: {} BadColumns: {}'.format(len(getBad('row')),len(getBad('column'))))

    if maxWaiting <= time.time() - last:
        clear()
    badRows = getBad('row')

    badColumns = getBad('column')
    if random.random() < niewielkieprawdopodobienstwo:
        # print('[1] RANDOMOWE SPIERDOLENIE')
        badRows = rows[randrange(n)]
        badColumns = columns[randrange(m)]

    if (badRows and random.choice(['row','column']) == 'row') or (not badColumns):
        i = random.choice(badRows)
        bestInd = 0
        oldRow = opt_dist(rows[i],rowNumbers[i])
        # print('[1.1] Naprawiam {} wiersz.\tPotrzeba {} do poprawnego wiersza.'.format(i,opt_dist(rows[i],rowNumbers[i])))
        for j in range(m):
            best = 0
            oldVal = rows[i][j]
            oldColumn = opt_dist(columns[j],columnNumbers[j])
            rows[i][j] = not oldVal
            columns[j][i] = not oldVal
            if best < (oldRow - opt_dist(rows[i],rowNumbers[i]) + oldColumn - opt_dist(columns[j],columnNumbers[j])) and (oldRow - opt_dist(rows[i],rowNumbers[i]) + oldColumn - opt_dist(columns[j],columnNumbers[j])) > 0:
                best = oldRow - opt_dist(rows[i],rowNumbers[i]) + oldColumn - opt_dist(columns[j],columnNumbers[j])
                bestInd = j
                # print('Bedzie poprawa o conajmniej {}.'.format(best))
            # print('\tTEST: old: {} {}. new: {} {}\tPoprawa: {} {}'.format(oldRow,oldColumn,opt_dist(rows[i],rowNumbers[i]),opt_dist(columns[j],columnNumbers[j]),oldRow - opt_dist(rows[i],rowNumbers[i]),oldColumn - opt_dist(columns[j],columnNumbers[j])))
            rows[i][j] = oldVal
            columns[j][i] = oldVal

        if random.random() < niewielkieprawdopodobienstwo:
            # print('[2] RANDOMOWE SPIERDOLENIE')
            bestInd = randrange(m)

        rows[i][bestInd] = not rows[i][bestInd]
        columns[bestInd][i] = not columns[bestInd][i]
        # print('[1.2] Naprawilem {} wiersz.\tPotrzeba {} do poprawnego wiersza. Poprawa o: {}\n'.format(i,opt_dist(rows[i],rowNumbers[i]),best))
    else:
        j = random.choice(badColumns)
        bestInd = 0
        oldColumn = opt_dist(columns[i],columnNumbers[i])

        # print('[2.1] Naprawiam {} kolumne.\tPotrzeba {} do poprawnej kolumny.'.format(j,opt_dist(columns[j],columnNumbers[j])))
        for i in range(n):
            best = 0
            oldVal = rows[i][j]
            oldRow = opt_dist(rows[i],rowNumbers[i])
            rows[i][j] = not oldVal
            columns[j][i] = not oldVal
            if best < (oldRow - opt_dist(rows[i],rowNumbers[i]) + oldColumn - opt_dist(columns[j],columnNumbers[j])) and (oldRow - opt_dist(rows[i],rowNumbers[i]) + oldColumn - opt_dist(columns[j],columnNumbers[j])) > 0:
                best = oldRow - opt_dist(rows[i],rowNumbers[i]) + oldColumn - opt_dist(columns[j],columnNumbers[j])
                bestInd = i
                # print('Bedzie poprawa o conajmniej {}.'.format(best))
            # print('\tTEST: old: {} {}. new: {} {}\tPoprawa: {} {}'.format(oldRow,oldColumn,opt_dist(rows[i],rowNumbers[i]),opt_dist(columns[j],columnNumbers[j]),oldRow - opt_dist(rows[i],rowNumbers[i]),oldColumn - opt_dist(columns[j],columnNumbers[j])))
            rows[i][j] = oldVal
            columns[j][i] = oldVal

        if random.random() < niewielkieprawdopodobienstwo:
            # print('[3] RANDOMOWE SPIERDOLENIE')
            bestInd = randrange(n)

        rows[bestInd][j] = not rows[bestInd][j]
        columns[j][bestInd] = not columns[j][bestInd]
        # print('[2.2] Naprawilem {} kolumne.\tPotrzeba {} do poprawnej kolumny. Poprawa o: {}\n'.format(j,opt_dist(columns[j],columnNumbers[j]),best))

output = open("zad5_output.txt","w+")
for row in rows:
    str1 = ""
    row = ['#' if x else '.' for x in row]
    output.write("{}\n".format(str1.join(row)))
output.close() 
