import random
from collections import deque
import itertools

with open('zad_input.txt','r') as f:
    lines = f.readlines()

tmpl = []
for line in lines:
    tmpl.append(line.strip())
n = len(tmpl)
m = len(tmpl[0])
labirynth = []
for i in range(n):
    labirynth.append(tmpl[i])

### END OF INPUT ###

comando_starts = set()
possible_moves = ['U','D','R','L']
moves_seq = []


move_f = {
    'U': (lambda pos: (pos[0]-1, pos[1])),
    'D': (lambda pos: (pos[0]+1, pos[1])),
    'R': (lambda pos: (pos[0], pos[1]+1)),
    'L': (lambda pos: (pos[0], pos[1]-1))
}

for i in range(n):
    for j in range(len(labirynth[0])):
        if labirynth[i][j] == 'S':
            comando_starts.add((i,j))
            labirynth[i] = labirynth[i][:j] + ' ' + labirynth[i][j+1:]
        if labirynth[i][j] == 'B':
            comando_starts.add((i,j))
            labirynth[i] = labirynth[i][:j] + 'G' + labirynth[i][j+1:]

### RANDOM ###
def moveComando(positions,move):
    new_positions = set()
    for pos in positions:
        new_pos = move_f[move](pos)
        if labirynth[new_pos[0]][new_pos[1]] != '#':
            new_positions.add(move_f[move](pos))
        else:
            new_positions.add(pos)
    return new_positions


best_pos = set()
best_seq = []
moves_len = 120

all_cycles = list(itertools.permutations(possible_moves))
for seq in all_cycles:
    no = 18
    act_seq = seq[0] * no + seq[1] * no + seq[2] * no + seq[3] * no
    candidate_pos = comando_starts
    for m in act_seq:
        candidate_pos = moveComando(candidate_pos,m)
    if len(candidate_pos) < moves_len:
        moves_len = len(candidate_pos)
        best_seq = act_seq
        best_pos = candidate_pos

moves_seq = best_seq
comando_starts = best_pos
### BFS ###

queue = deque()
visited = set()

def checkWin(positions):
    for pos in positions:
        if labirynth[pos[0]][pos[1]] != 'G':
            return False
    return True

def printOutput(moves):
    output = open("zad_output.txt","w+")
    otp = ""
    for pos in moves:
        output.write(pos)
    output.close()

queue.append((comando_starts,[]))

while queue:
    state = queue.popleft()
    positions = state[0]
    moves = state[1]
    if checkWin(positions):
        printOutput(list(moves_seq.split(" ") + moves))
        exit(0)
    for move in possible_moves:
        new_positions = tuple(moveComando(positions,move))
        if new_positions in visited:
            continue
        if (len(new_positions) < len(positions)):
            visited.clear()
            queue.clear()
            queue.append((new_positions,moves + [move]))
            visited.add(new_positions)
            break
        queue.append((new_positions,moves + [move]))
        visited.add(new_positions)