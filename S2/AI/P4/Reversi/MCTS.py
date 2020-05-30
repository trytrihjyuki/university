import random
import time
import math
import sys

C = 1

MAXTIME = 0.6
MAXDEPTH = 60
NUMSIM = 10

def deepcopy(board):
    return [list(row) for row in board]

class MCTS():

    def __init__(self, board, player):
        super(MCTS, self).__init__()
        self.move = player
        self.board = deepcopy(board)
        self.node_no = 1
        self.not_leaf = set()
        self.root = Node(player,deepcopy(board),None,None)
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
                son = Node(1-node.player, B_son.board, node,m)
                node.addSon(son)

            v = random.choice(list(node.sons))                            #SIMULATION
            self.N+=1

            state = Board()
            state.board = deepcopy(v.board)
            current_player = v.player

            while not state.terminal():
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
    def __init__(self,player,board,father,move):
        self.move = move
        self.player = player
        self.board = board
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