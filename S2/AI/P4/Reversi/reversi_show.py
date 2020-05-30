import random
import random
import sys
from agent import Agent,initial_board
import time
#####################################################
# turtle graphic
#####################################################
# tracer(0,1)

BOK = 50
SX = -100
SY = 0
M = 8

GAMES = 100

MAXTIME = 0.6
MAXDEPTH = 60
NUMSIM = 10
#####################################################
def deepcopy(board):
    return [list(row) for row in board]

good = [[(0, 0), (0, 7), (7, 0), (7, 7)],[(1, 2), (2, 1), (1, 5), (3, 1), (6, 1), (4, 6), (5, 1), (6, 4), (1, 6), (1, 3), (4, 1), (6, 2), (6, 5), (1, 1), (1, 4), (2, 6), (5, 6), (3, 6), (6, 6), (6, 3)], [(2, 4), (5, 5), (5, 4), (4, 2), (2, 3), (4, 5), (2, 2), (5, 3), (3, 2), (2, 5), (3, 5), (5, 2)]]
neutral = [(0, 2), (0, 3), (0, 4), (0, 5), (2, 0), (2, 7), (3, 0), (3, 3), (3, 4), (3, 7), (4, 0), (4, 3), (4, 4), (4, 7), (5, 0), (5, 7), (7, 2), (7, 3), (7, 4), (7, 5)]
bad = [(0, 1), (7, 1), (6, 1), (1, 1), (6, 6), (0, 6), (6, 7), (1, 7), (7, 6), (6, 0), (1, 0), (1, 6)]




class Board:
    dirs  = [ (0,1), (1,0), (-1,0), (0,-1), (1,1), (-1,-1), (1,-1), (-1,1) ]
    
    
    def __init__(self):
        self.board = initial_board()
        self.fields = set()
        self.move_list = []
        self.history = []
        for i in range(M):
            for j in range(M):
                if self.board[i][j] == None:
                    self.fields.add( (j,i) )

    def draw(self):
        for i in range(M):
            res = []
            for j in range(M):
                b = self.board[i][j]
                if b == None:
                    res.append('.')
                elif b == 1:
                    res.append('#')
                else:
                    res.append('o')
            print(''.join(res))
        print("")
        
    
    def show(self):
        for i in range(M):
            for j in range(M):
                kwadrat(j, i, 'green')
                
        for i in range(M):
            for j in range(M):
                if self.board[i][j] == 1:
                    kolko(j, i, 'black')
                if self.board[i][j] == 0:
                    kolko(j, i, 'white')
                                   
    def moves(self, player):
        res = []
        for (x,y) in self.fields:
            if any( self.can_beat(x,y, direction, player) for direction in Board.dirs):
                res.append( (x,y) )
        if not res:
            return [None]
        return res               
    
    def can_beat(self, x,y, d, player):
        dx,dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x,y) == 1-player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x,y) == player
    
    def get(self, x,y):
        if 0 <= x < M and 0 <=y < M:
            return self.board[y][x]
        return None
                        
    def do_move(self, move, player):
        self.history.append([x[:] for x in self.board])
        self.move_list.append(move)
        
        if move == None:
            return False
        x,y = move
        x0,y0 = move
        self.board[y][x] = player
        self.fields -= set([move])
        for dx,dy in self.dirs:
            x,y = x0,y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x,y) == 1-player:
              to_beat.append( (x,y) )
              x += dx
              y += dy
            if self.get(x,y) == player:
                for (nx,ny) in to_beat:
                    self.board[ny][nx] = player
        return True

    def result(self):
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]
                if b == 0:
                    res -= 1
                elif b == 1:
                    res += 1
        return res
                
    def terminal(self):
        if not self.fields:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] == self.move_list[-2] == None 

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return [None]

    def agent_move(self,player):
        ms = self.moves(player)
        search = [move for move in ms if move not in bad]


        corners = set(good[0]) & set(ms)

        if corners:
            return random.choice(list(corners))


        fl = set(good[1]) & set(search)

        if fl:
            return random.choice(list(fl))

        sl = set(good[2]) & set(search)

        if sl:
            return random.choice(list(sl))

        return max(search if search else ms, key=lambda x: self.simulate(x,player))

    def simulate(self, move,player):
        total_score = 0
        curr_state = Board()
        curr_state.board = deepcopy(self.board)
        curr_state.fields = set(self.fields)
        curr_state.move_list = list(self.move_list)
        curr_state.history = list(self.history)
        curr_state.do_move(move, player)
        for _ in range(NUMSIM):
            new_state = Board()
            new_state.board = deepcopy(curr_state.board)
            new_state.fields = set(curr_state.fields)
            new_state.move_list = list(curr_state.move_list)
            new_state.history = list(curr_state.history)
            new_player = 1 - player

            for _ in range(MAXDEPTH):
                m = new_state.random_move(new_player)
                new_state.do_move(m, new_player)
                new_player = 1-new_player
                if new_state.terminal():
                    break
            total_score += new_state.result()
        return total_score





our_losses = 0
games = 1000
for i in range(1, games+1):

    player = 0
    B = Board()
    ab = Agent(1)
    while True:
        if not player:
            m = B.random_move(player)
        else:
            # m = ab.move(B.board, B.fields)
            m = B.agent_move(player)

        B.do_move(m, player)
        player = 1-player
        if B.terminal():
            break

    r = B.result()
    if r < 0:
        our_losses += 1
    print(f"Games played: {i} Games lost: {our_losses}")

print(f"Games played: {games} Games lost: {our_losses}")
