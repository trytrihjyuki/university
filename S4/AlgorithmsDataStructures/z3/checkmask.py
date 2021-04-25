#!/usr/bin/python3
colorings = []
BADMASK = ('...','...','...')
while True:
    coloring = []
    try:
        line = input()
    except EOFError:
        break
    if line != '':
        colorings.append(line)


for i in range(0,len(colorings),5):
    flag = False
    for j in range(3):
        m = (colorings[i+j],colorings[i+j+1],colorings[i+j+2])
        if m == BADMASK:
            flag = True
    if not flag:
        print("GOOD COLORING!!!!")
        for k in range(i,i+5):
            print(colorings[k])
        exit(0)