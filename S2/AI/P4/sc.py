import sys
import math
from random import seed
from random import random
from random import randint

# Grab the pellets as fast as you can!
def manhhatan(p1,p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])
# width: size of the grid
# height: top left corner is (x=0, y=0)
width, height = [int(i) for i in input().split()]
board = []
for i in range(height):
    row = input()  # one line of the grid: space " " is floor, pound "#" is wall
    row_b = [False if r == '#' else True for r in row]
    board.append(row_b)

lastPos = {}
lastPos = {}
pacPos = {}
pacPos_og = {}
# game loop
num = 0
while True:
    num+=1
    my_score, opponent_score = [int(i) for i in input().split()]
    lastPos = pacPos_og.copy()
    pacPos.clear()
    pacPos_og.clear()
    visible_pac_count = int(input())  # all your pacs and enemy pacs in sight
    myPacs = []
    for i in range(visible_pac_count):
        pac_id, mine, x, y, type_id, speed_turns_left, ability_cooldown = input().split()
        pac_id = int(pac_id)
        mine = mine != "0"
        x = int(x)
        y = int(y)
        if mine:
            myPacs.append((pac_id,(x,y)))
            pacPos[pac_id] = (x,y)
            pacPos_og[pac_id] = (x,y)
        speed_turns_left = int(speed_turns_left)
        ability_cooldown = int(ability_cooldown)
    visible_pellet_count = int(input())  # all pellets in sight
    bestMoves = {}
    for pac in myPacs:
        bm = (-1,(-1,-1))
        bestMoves[pac[0]] = bm


    pallets = []

    for i in range(visible_pellet_count):
        x, y, value = [int(j) for j in input().split()]
        pallets.append((value,(x,y)))

    pallets.sort()

    for pallet in pallets:
        # print("%d %d %d\n"%(x,y,value), file=sys.stderr)
        candidates = []

        for p in myPacs:
            candidates.append((manhhatan(pacPos[p[0]],pallet[1]),p[0]))

        candidates.sort()
        if candidates[0][0] < 1000:
            bestMoves[candidates[0][1]] = pallet[1]
            pacPos[candidates[0][1]] = (10000,10000)

    output = ""
    for p in myPacs:
        m = bestMoves[p[0]]
        seed(num)
        num+=1
        if p[0] in lastPos:
            print(lastPos[p[0]], file=sys.stderr)
            print(pacPos_og[p[0]], file=sys.stderr)
        if p[0] in lastPos and lastPos[p[0]] == pacPos_og[p[0]]:
            print("siema", file=sys.stderr)
            print(lastPos[p[0]], file=sys.stderr)
            print(lastPos[p[0]], file=sys.stderr)
            if random() >= 0.2:
                seed(num)
                num+=1
                print("%d %d"%(x,y), file=sys.stderr)
                x = randint(0,width-1)
                y = randint(0,height-1)
                while not board[y][x]:
                    x = randint(0,width-1)
                    y = randint(0,height-1)
                output+="MOVE  " + str(p[0]) + " " + str(x) + " " + str(y) + "| "
            else:
                print("elo", file=sys.stderr)
        else:
            if m[1] != -1:
                output+="MOVE  " + str(p[0]) + " " + str(m[0]) + " " + str(m[1]) + "| "
            else:
                seed(num)
                num+=1
                x = randint(0,width-1)
                y = randint(0,height-1)
                while not board[y][x]:
                    x = randint(0,width-1)
                    y = randint(0,height-1)
                output+="MOVE  " + str(p[0]) + " " + str(x) + " " + str(y) + "| "
    print(output)


