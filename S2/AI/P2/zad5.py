import random
import heapq
from collections import deque

class PriorityQueue:
    def __init__(self):
        self._queue = []
        self._index = 0
 
    def push(self, item, priority):
        heapq.heappush(self._queue, (priority, self._index, item))
        self._index += 1
 
    def pop(self):
        return heapq.heappop(self._queue)[-1]

    def len(self):
        return len(self._queue)

with open('zad_input.txt','r') as f:
    lines = f.readlines()

tmpl = []
for line in lines:
    tmpl.append(line.strip())
n = len(tmpl)
m = len(tmpl[0])
maze = []
for i in range(n):
    maze.append(tmpl[i])

### END OF INPUT ###

comando_starts = set()
possible_moves = ['U','D','R','L']
moves_seq = []
goals = []

move_f = {
    'U': (lambda pos: (pos[0]-1, pos[1])),
    'D': (lambda pos: (pos[0]+1, pos[1])),
    'R': (lambda pos: (pos[0], pos[1]+1)),
    'L': (lambda pos: (pos[0], pos[1]-1))
}

for i in range(n):
    for j in range(len(maze[0])):
        if maze[i][j] == 'S':
            comando_starts.add((i,j))
            maze[i] = maze[i][:j] + ' ' + maze[i][j+1:]
        if maze[i][j] == 'G':
            goals.append((i,j))
        if maze[i][j] == 'B':
            comando_starts.add((i,j))
            goals.append((i,j))
            maze[i] = maze[i][:j] + 'G' + maze[i][j+1:]

###HEURA###
distances = {}
for i in range(n):
    for j in range(len(maze[0])):
        if maze[i][j] == ' ':
            distances[(i,j)] = n*m+10
        if maze[i][j] == 'G':
            distances[(i,j)] = 0

def BFS(v):
    queue = deque()
    visited = set()
    queue.append((v,0))
    while queue:
        st = queue.popleft()
        vb = st[0]
        dist = st[1]
        distances[vb] = min(distances[vb],dist)
        if vb in visited:
            continue
        visited.add(vb)
        for move in possible_moves:
            new_pos = move_f[move](vb)
            if maze[new_pos[0]][new_pos[1]] != '#':
                queue.append((new_pos,dist+1))

for g in goals:
    BFS(g)

def heura(positions):
    curr_dist = sorted([distances[pos] for pos in positions])
    degree = 36
    return sum(curr_dist[-degree:])
### BFS ###
def moveComando(positions,move):
    new_positions = set()
    for pos in positions:
        new_pos = move_f[move](pos)
        if maze[new_pos[0]][new_pos[1]] != '#':
            new_positions.add(move_f[move](pos))
        else:
            new_positions.add(pos)
    return new_positions

queue = PriorityQueue()
visited = set()

def checkWin(positions):
    for pos in positions:
        if maze[pos[0]][pos[1]] != 'G':
            return False
    return True

def printOutput(moves):
    output = open("zad_output.txt","w+")
    otp = ""
    for pos in moves:
        output.write(pos)
    output.close()


queue.push((comando_starts,[]),heura(comando_starts))

while queue.len():
    state = queue.pop()
    positions = state[0]
    moves = state[1]
    if checkWin(positions):
        printOutput(moves_seq + moves)
        exit(0)
    for move in possible_moves:
        new_positions = tuple(moveComando(positions,move))
        if new_positions not in visited:
            visited.add(new_positions)
            queue.push((new_positions,moves + [move]),len(moves) + 1 + heura(new_positions))
