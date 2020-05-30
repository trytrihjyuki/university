import sys
import heapq
import itertools
 
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
B_Positions = []
pozycja = (0,0)
for i in range(n):
    for j in range(len(board[0])):
        if board[i][j] == 'K':
            pozycja = (i,j) # (Y,X) //// (ROW,COL)
        if board[i][j] == 'B':
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
            board[i] = board[i][:j] + '.' + board[i][j+1:]
            pozycja = (i,j) # (Y,X) //// (ROW,COL)

def checkMove(state,move):
    dx = 0
    dy = 0
    moves = state[0]
    curr_position = state[1]
    curr_BPositions = state[2]
    if move == 'U':
        dy-=1
    if move == 'D':
        dy+=1
    if move == 'R':
        dx+=1
    if move == 'L':
        dx-=1
    new_position = (curr_position[0]+dy,curr_position[1]+dx)
    new_new_position = (curr_position[0]+dy+dy,curr_position[1]+dx+dx)

    if board[new_position[0]][new_position[1]] == 'W':
        return

    if (new_position in curr_BPositions):
        if (board[new_new_position[0]][new_new_position[1]] == 'W') or (new_new_position in curr_BPositions):
            return
        new_Bpositions = [new_new_position if p==new_position else p for p in curr_BPositions]
        return (moves+[move],new_position,new_Bpositions)

    return (moves+[move],new_position,curr_BPositions)

def checkWin(B_Positions):
    for b_pos in B_Positions:
        if b_pos not in goals:
            return False
    return True

def printOutput(state):
    output = open("zad_output.txt","w")
    otp = ""
    output.write(otp.join(state[0]))
    output.close()

def heura(B_Positions):
    mini = n*m*100
    for B_pos in itertools.permutations(B_Positions):
        val = 0
        for i in range(len(goals)):
            val+=(abs(goals[i][0] - B_pos[i][0])+abs(goals[i][1] - B_pos[i][1]))
        mini = min(val,mini)
    return mini

q.push(([],pozycja,B_Positions),heura(B_Positions))
while q.len() > 0:
    state = q.pop()
    moves_done = state[0]
    curr_position = state[1]
    curr_Bpositions = state[2]
    if (curr_position,tuple(curr_Bpositions)) in visited_states:
        continue
    visited_states.add((curr_position,tuple(sorted(curr_Bpositions))))
    if checkWin(state[2]):
        printOutput(state)
        sys.exit()
    for move in moves:
        new_state = checkMove(state,move)
        if (new_state is not None) and ((new_state[1],tuple(sorted(new_state[2]))) not in visited_states):
            q.push(new_state,len(list(moves_done)) + heura(state[2]))
