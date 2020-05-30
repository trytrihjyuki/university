import random
import copy
import operator

BOK = 50
SX = -100
SY = 0
M = 8

POWERVAL = 2
WINBONUS = 10000
MINSCORE = 40
INF = 1e9
MAXDEPTH = 10
MAXDEPTHAB = 3
NUMSIM = 6

def initial_board():
    B = [ [None] * M for i in range(M)]
    B[3][3] = 1
    B[4][4] = 1
    B[3][4] = 0
    B[4][3] = 0
    return B


valueBoard = [[99,-8,8,6,6,8,-8,99],[-8,-24,-4,-3,-3,-4,-24,-8],
             [8,-4,7,4,4,7,-4,8],[6,-3,4,0,0,4,-3,6],
             [6,-3,4,0,0,4,-3,6],[8,-4,7,4,4,7,-4,8],
             [-8,-24,-4,-3,-3,-4,-24,-8],[99,-8,8,6,6,8,-8,99]]


good = [[(0, 0), (0, 7), (7, 0), (7, 7)],[(1, 2), (2, 1), (1, 5), (3, 1), (6, 1), (4, 6), (5, 1), (6, 4), (1, 6), (1, 3), (4, 1), (6, 2), (6, 5), (1, 1), (1, 4), (2, 6), (5, 6), (3, 6), (6, 6), (6, 3)], [(2, 4), (5, 5), (5, 4), (4, 2), (2, 3), (4, 5), (2, 2), (5, 3), (3, 2), (2, 5), (3, 5), (5, 2)]]
neutral = [(0, 2), (0, 3), (0, 4), (0, 5), (2, 0), (2, 7), (3, 0), (3, 3), (3, 4), (3, 7), (4, 0), (4, 3), (4, 4), (4, 7), (5, 0), (5, 7), (7, 2), (7, 3), (7, 4), (7, 5)]
bad = [(0, 1), (7, 1), (6, 1), (1, 1), (6, 6), (0, 6), (6, 7), (1, 7), (7, 6), (6, 0), (1, 0), (1, 6)]

class GameState:
    dirs  = [ (0,1), (1,0), (-1,0), (0,-1), (1,1), (-1,-1), (1,-1), (-1,1) ]

    board = []
    fields = {}
    currPlayer = 1

    def __init__(self,startId,board,fields):
        self.board = [list(row) for row in board]
        self.fields = fields.copy()
        self.currPlayer = startId

    def can_beat(self,x,y,d,playerId):
        dx,dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x,y) == 1-playerId:
            cnt += 1
            x += dx
            y += dy
        return (cnt > 0 and self.get(x,y) == playerId,cnt)

    def get(self,x,y):
        if 0 <= x < M and 0 <=y < M:
            return self.board[y][x]
        return None

    def moves(self,playerId = None):
        if playerId is None:
            playerId = self.currPlayer
        res = []
        for (x,y) in self.fields:
            for direction in self.dirs:
                beatScore = self.can_beat(x, y, direction, playerId)
                if beatScore[0]:
                    res.append( ((x,y) , beatScore[1] ))
        if not res:
            return [None]
        return res

    def winner(self):
        onBoard = set()
        for i in range(M):
            for j in range(M):
                if self.board[i][j] is not None:
                    onBoard.add(self.board[i][j])

        if len(onBoard) == 1:
            return list(onBoard)[0]

        if self.moves()[0] is None:
            if self.result() > 0:
                return 1
            else:
                return 0
        return None

    def do_move(self, move):
        if move == None:
            return None
        x,y = move
        x0,y0 = move
        newGS = GameState(self.currPlayer,self.board,self.fields)
        newGS.board[y][x] = newGS.currPlayer
        newGS.fields -= set([move])
        for dx,dy in self.dirs:
            x,y = x0,y0
            to_beat = []
            x += dx
            y += dy
            while newGS.get(x,y) == 1-newGS.currPlayer:
              to_beat.append( (x,y) )
              x += dx
              y += dy
            if newGS.get(x,y) == newGS.currPlayer:
                for (nx,ny) in to_beat:
                    newGS.board[ny][nx] = newGS.currPlayer
        newGS.currPlayer = 1 - newGS.currPlayer
        return newGS

    def heuristic(self):
        player0 = 0
        player1 = 0

        winner = self.winner()
        # if winner is not None:
        #     if winner == 1:
        #         return (-WINBONUS,WINBONUS)
        #     else:
        #         return (WINBONUS,-WINBONUS)

        for i in range(M):
            for j in range(M):
                if self.board[i][j] is not None:
                    if self.board[i][j] == 1:
                        # player1 += valueBoard[i][j]
                        player1 += 1
                    else:
                        # player0 += valueBoard[i][j]
                         player0 += 1
        return (player0,player1)

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

class Agent:

    playerId = 1

    def __init__(self,myId):
        self.playerId = myId

    def move(self, board, fields):
        gm = self.moveGoodPos(board,fields)
        if gm:
            return gm

        bs = self.bestsimulate(board,fields)
        if bs:
            return bs

        # abm = self.bestAB(board,fields)
        # if abm:
        #     return abm

    def moveGoodPos(self, board, fields):
        gs = GameState(self.playerId,board,fields)
        ms = gs.moves()
        search = [move[0] for move in ms if move not in bad]
        if ms[0] == None:
            return None
        corners = set(good[0]) & set(ms)

        if corners:
            return random.choice(list(corners))


        fl = set(good[1]) & set(search)

        if fl:
            return random.choice(list(fl))

        sl = set(good[2]) & set(search)

        if sl:
            return random.choice(list(sl))
        return None
    def bestAB(self, board, fields):
        gs = GameState(self.playerId,board,fields)
        ms = gs.moves()
        if ms[0] is not None:
            candidates = [(m[0], self.alphabeta(gs.do_move(m[0]),0,-INF,INF)) for m in ms]
            return max(candidates, key = lambda x:x[1])[0]

        return None

    def bestsimulate(self, board, fields):
        gs = GameState(self.playerId,board,fields)
        ms = gs.moves()
        candidates = []
        if ms[0] is not None:
            for (m,bs) in ms:
                if m in neutral:
                    currscore = 0
                    for i in range(NUMSIM):
                        currscore+=self.getScore(gs.do_move(m),0)
                    candidates.append((m,currscore))
            if candidates:
                return max(candidates, key = lambda x:x[1])[0]
            else:
                return None
                for (m,bs) in ms:
                    if m in bad:
                        currscore = 0
                        for i in range(NUMSIM):
                            currscore+=self.getScore(gs.do_move(m),0)
                        candidates.append((m,currscore))

        return None


    def getScore(self, gs, depth):

        winner = gs.winner()

        if winner is not None or depth == MAXDEPTH:
            return gs.heuristic()[self.playerId] - gs.heuristic()[1-self.playerId]

        rm = random.choice(gs.moves())[0]
        return self.getScore(gs.do_move(rm),depth + 1)

    def alphabeta(self, gs, depth, a, b):
        if depth == MAXDEPTHAB or gs.winner() is not None:
            return gs.heuristic()[self.playerId] #- gs.heuristic()[1-self.playerId]

        if gs.currPlayer == self.playerId: # MAX PLAYER
            val = -INF
            states = [gs.do_move(m) for (m,bs) in gs.moves()]

            for s in states:
                val = max(val, self.alphabeta(s,depth+1,a,b))
                a = max(a,val)
                if a >= b: #CUT OFF
                    break

            return val
        else:   #MIN PLAYER
            val = INF
            states = [gs.do_move(m) for (m,bs) in gs.moves()]

            for s in states:
                val = min(val, self.alphabeta(s,depth+1,a,b))
                b = min(b,val)
                if a >= b: #CUT OFF
                    break
            return val