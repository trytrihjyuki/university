import random
# from copy import deepcopy
import math
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

MAXTIME = 0.8
MAXDEPTH = 60
NUMSIM = 10
#####################################################
def deepcopy(board):
    return [list(row) for row in board]

good = [[(0, 0), (0, 7), (7, 0), (7, 7)],[(1, 2), (2, 1), (1, 5), (3, 1), (6, 1), (4, 6), (5, 1), (6, 4), (1, 6), (1, 3), (4, 1), (6, 2), (6, 5), (1, 1), (1, 4), (2, 6), (5, 6), (3, 6), (6, 6), (6, 3)], [(2, 4), (5, 5), (5, 4), (4, 2), (2, 3), (4, 5), (2, 2), (5, 3), (3, 2), (2, 5), (3, 5), (5, 2)]]
neutral = [(0, 2), (0, 3), (0, 4), (0, 5), (2, 0), (2, 7), (3, 0), (3, 3), (3, 4), (3, 7), (4, 0), (4, 3), (4, 4), (4, 7), (5, 0), (5, 7), (7, 2), (7, 3), (7, 4), (7, 5)]
bad = [(0, 1), (7, 1), (6, 1), (1, 1), (6, 6), (0, 6), (6, 7), (1, 7), (7, 6), (6, 0), (1, 0), (1, 6)]

ALLFIELDS = []
for i in range(M):
    for j in range(M):
        ALLFIELDS.append((i,j))

C = 1.5

class MCTS():

    def __init__(self, board, player):
        super(MCTS, self).__init__()
        self.move = player
        self.board = deepcopy(board)
        self.node_no = 1
        self.allNodesNo = 1
        self.visited = {} ###############################################UWAGA######################33
        self.not_leaf = set()
        self.root = Node(player,deepcopy(board),1,None,None)
        self.N = 0


    def getMove(self):
        start = time.time()
        while(time.time() - start < MAXTIME):
            node = self.root

            while not node.isLeaf():                               #SELECTION
                node = node.bestSon(self.N)


            B = Board()                                             #EXPANSION
            B.board = deepcopy(node.board)
            ms = B.moves(node.player)

            if ms[0] is None:
                continue

            for m in ms:
                B_son = Board()
                B_son.board = deepcopy(B.board)
                B_son.do_move(m,node.player)
                son = Node(1-node.player, B_son.board, self.allNodesNo + 1, node,m)
                self.allNodesNo+=1
                node.addSon(son)

            v = random.choice(list(node.sons))                            #SIMULATION
            self.N+=1

            state = Board()
            state.board = deepcopy(v.board)
            current_player = v.player

            while not state.terminal(current_player):
                ms = state.moves(current_player)
                m = random.choice(ms)
                state.do_move(m,current_player)
                current_player = 1-current_player


            win = False                                             #BACKPROPAGATION
            if state.result() >= 0:
                win = True


            while v is not None:
                v.games+=1
                if win:
                    v.wins+=1
                v = v.father

        return self.root.bestSon(self.N).move

class Node():
    def __init__(self,player,board,number,father,move):
        self.move = move
        self.player = player
        self.board = board
        self.no = number
        self.games = 0
        self.wins = 0
        self.father = father
        self.sons = set()

    def isLeaf(self):
        return len(self.sons) == 0

    def UCT(self,N):
        if self.games == 0:
            return 1
        return (self.wins / self.games) + C * math.sqrt(math.log(N) / self.games)

    def bestSon(self,N):
        return max(list(self.sons), key = lambda x: x.UCT(N))

    def addSon(self,v):
        self.sons.add(v)


class Board:
    dirs  = [ (0,1), (1,0), (-1,0), (0,-1), (1,1), (-1,-1), (1,-1), (-1,1) ]
    
    
    def __init__(self):
        self.board = initial_board()
        self.move_list = []
        self.history = []

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
        for (x,y) in ALLFIELDS:
            if self.board[y][x] is None:
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
                
    def terminal(self,player):
        if self.moves(player)[0] is None:
            return True
        flag = True
        for f in ALLFIELDS:
            if self.board[f[0]][f[1]] is None:
                flag = False
        if flag:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] == self.move_list[-2] == None 

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return [None]


our_losses = 0
games = 10
for i in range(1, games+1):

    player = 0
    B = Board()
    ab = Agent(1)
    tmp = 0
    while True:
        # print("ruch: %d\n"%tmp)
        tmp+=1
        if not player:
            m = B.random_move(player)
        else:
            mcts = MCTS(B.board, player)
            # m = ab.move(B.board, B.fields)
            m = mcts.getMove()

        B.do_move(m, player)
        player = 1-player
        # B.draw()
        if B.terminal(player):
            break

    r = B.result()
    if r < 0:
        our_losses += 1
    print(f"Games played: {i} Games lost: {our_losses}")

print(f"Games played: {games} Games lost: {our_losses}")
