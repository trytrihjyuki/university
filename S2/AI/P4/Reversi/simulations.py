import random
import random
import sys
from agent import Agent,initial_board
from collections import defaultdict as dd
from turtle import *

#####################################################
# turtle graphic
#####################################################
tracer(0,1)

SIMULATIONS = 5000

BOK = 50
SX = -100
SY = 0
M = 8

simulations = 0

def kwadrat(x, y, kolor):
  fillcolor(kolor)
  pu()
  goto(SX + x * BOK, SY + y * BOK)
  pd()
  begin_fill()
  for i in range(4):
    fd(BOK)
    rt(90)
  end_fill() 

def kolko(x, y, kolor):
  fillcolor(kolor)

  pu()
  goto(SX + x * BOK + BOK/2, SY + y * BOK - BOK)
  pd()
  begin_fill()
  # circle(BOK/2)
  write(round(good[x][y]/simulations - 0.005, 2), True, align="center")
  write("   %", True, align="center")
  end_fill() 

#####################################################



    
class Board:
    dirs  = [ (0,1), (1,0), (-1,0), (0,-1), (1,1), (-1,-1), (1,-1), (-1,1) ]
    
    
    def __init__(self):
        self.board = initial_board()
        self.fields = set()
        self.move_list = []
        self.history = []
        self.winner = 0
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
        

    def showGood(self):
        for i in range(M):
            for j in range(M):
                kwadrat(j, i, 'green')
                
        for i in range(M):
            for j in range(M):
                if self.board[i][j] == 1:
                    kolko(j, i, 'black')
                if self.board[i][j] == 0:
                    kolko(j, i, 'white')


    def show(self):
        for i in range(M):
            for j in range(M):
                kwadrat(j, i, 'green')
                
        for i in range(M):
            for j in range(M):
                kolko(j, i, 'black')
                                   
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
    
    def scoreGood(self, goodBoard):
        for i in range(M):
            for j in range(M):
                if self.board[i][j] == 1 - self.winner:
                    goodBoard[i][j]-=1
                # elif self.board[i][j]:
                    # goodBoard[i][j]-=1

good = [ [SIMULATIONS] * M for i in range(M)]

score = {'Random' : 0, 'Agent' : 0}
for i in range(SIMULATIONS):
    a0 = Agent(0)
    a1 = Agent(1)
    B = Board()
    player = random.choice([0,1])
    simulations+=1
    while True:
        # B.draw()
        # B.show()
        if player == 1:
            m = a1.randomMove(B.board,B.fields)
        else:
            m = a0.randomMove(B.board,B.fields)
        if B.terminal():
            break

        if not B.do_move(m, player):
            break
        player = 1-player

    if B.result() > 0:
        B.winner = 1
    else:
        B.winner = 0
    B.scoreGood(good)
    if i%100 == 0:
        print('Game %d has ended'%i)
        B.show()

print(good)


input('\nEnd of experiment')

sys.exit(0)
