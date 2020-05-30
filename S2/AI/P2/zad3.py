import sys
import heapq
import itertools
from collections import deque
import time

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
board = []
for i in range(n):
    board.append(tmpl[i])

###END OF INPUT###

visited_states = set()

moves = ['U','D','R','L']
q = PriorityQueue()
goals = []
K_Position = (0,0)
B_Positions = []
for i in range(n):
    for j in range(len(board[0])):
        if board[i][j] == 'K':
            K_Position = (i,j) # (Y,X) //// (ROW,COL)
            board[i] = board[i][:j] + '.' + board[i][j+1:]
        if board[i][j] == 'B':
            board[i] = board[i][:j] + '.' + board[i][j+1:]
            B_Positions.append((i,j))
        if board[i][j] == 'G':
            goals.append((i,j))
            board[i] = board[i][:j] + '.' + board[i][j+1:]
        if board[i][j] == '*':
            goals.append((i,j))
            board[i] = board[i][:j] + '.' + board[i][j+1:]
            B_Positions.append((i,j))
        if board[i][j] == '+':
            goals.append((i,j))
            board[i] = board[i][:j] + ',' + board[i][j+1:]
            K_Position = (i,j) # (Y,X) //// (ROW,COL)


def checkMove(state,ind,move):
    dx = 0
    dy = 0
    curr_Bpositions = state[0]
    curr_moves = state[1]
    last_position = state[2]
    if move == 'U':
        dy-=1
    if move == 'D':
        dy+=1
    if move == 'R':
        dx+=1
    if move == 'L':
        dx-=1
    curr_position = curr_Bpositions[ind]
    new_position = (curr_position[0]+dy,curr_position[1]+dx)
    previous_position = (curr_position[0]-dy,curr_position[1]-dx)
    elem_on_np = board[new_position[0]][new_position[1]]

    if elem_on_np == 'W':
        return

    if new_position in curr_Bpositions:
        return
    neededMoves = getPath(curr_Bpositions,last_position,previous_position)
    if neededMoves is None:
        return
    new_Bpositions = curr_Bpositions.copy()
    new_Bpositions[ind] = new_position
    new_moves = curr_moves + neededMoves + [move]
    return (new_Bpositions,new_moves,curr_position)

def getPath(B_positions,start_p,end_p):
    if board[end_p[0]][end_p[1]] == 'W':
        return
    if end_p in B_positions:
        return
    queue = deque()
    visited = set()
    queue.append((start_p,[]))
    while queue:
        v = queue.popleft()
        pos = v[0]
        moves = v[1]
        if pos in B_positions:
            continue
        if pos == end_p:
            return moves
        new_moves = moves
        if (board[pos[0]+1][pos[1]] == '.') and ((pos[0]+1,pos[1]) not in visited):
            visited.add((pos[0]+1,pos[1]))
            queue.append(((pos[0]+1,pos[1]),new_moves + ['D']))
        if (board[pos[0]-1][pos[1]] == '.') and ((pos[0]-1,pos[1]) not in visited):
            visited.add((pos[0]-1,pos[1]))
            queue.append(((pos[0]-1,pos[1]),new_moves + ['U']))
        if (board[pos[0]][pos[1]+1] == '.') and ((pos[0],pos[1]+1) not in visited):
            visited.add((pos[0],pos[1]+1))
            queue.append(((pos[0],pos[1]+1),new_moves + ['R']))
        if (board[pos[0]][pos[1]-1] == '.') and ((pos[0],pos[1]-1) not in visited):
            visited.add((pos[0],pos[1]-1))
            queue.append(((pos[0],pos[1]-1),new_moves + ['L']))

def checkWin(B_Positions):
    for b_pos in B_Positions:
        if b_pos not in goals:
            return False
    return True

def printOutput(state):
    output = open("zad_output.txt","w")
    otp = ""
    for pos in state[1]:
        output.write(str(pos))
    output.close()

def man_len(pos_A,pos_B):
    return (abs(pos_A[0] - pos_B[0])+abs(pos_A[1] - pos_B[1]))

def heura(BPositions):
    positions = BPositions.copy()
    val = 0
    for g in goals:
        dist = [(man_len(g,b), b) for b in positions]
        mini = min(dist)
        positions.remove(mini[1])
        val+=mini[0]
    return val

q.push((B_Positions,[],K_Position),heura(B_Positions))

cnt = 0
t1 = time.time()
while q.len():
    cnt += 1
    state = q.pop()
    curr_positions = state[0]
    curr_moves = state[1]
    curr_KPosition = state[2]
    if checkWin(curr_positions):
        printOutput(state)
        sys.exit()
    t1 = time.time()
    for move in moves:
        for i in range(len(B_Positions)):
            new_state = checkMove(state,i,move)
            if (new_state is not None) and ((tuple(sorted(new_state[0])),new_state[2]) not in visited_states):
                visited_states.add((tuple(sorted(new_state[0])),new_state[2]))
                q.push(new_state[:],heura(new_state[0]))
