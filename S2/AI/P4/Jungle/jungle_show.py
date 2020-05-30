import random
import sys
import time
import copy

NUMSIMULATIONS = 20000
NUMGAMES = 50

traps = [(0,2),(0,4),(1,3),(8,2),(8,4),(7,3)]
caves = [(0,3),(8,3)]
water = [(3,1),(3,2),(3,4),(3,5),(4,1),(4,2),(4,4),(4,5),(5,1),(5,2),(5,4),(5,5)]

#animal = ("id",strentgh,can be in water, can jump above water)
rat = ("r",0,True,False)
cat = ("c",1,False,False)
dog = ("d",2,False,False)
wolf = ("w",3,False,False)
jeopard = ("j",4,False,False)
tiger = ("t",5,False,True)
lion = ("l",6,False,True)
elephant = ("e",7,False,False)

strentgh = {'r': 0,'c': 1,'d': 2,'w': 3,'j': 4,'t': 5,'l': 6,'e': 7}
animalsSorted = ['e','l','t','j','w','d','c','r']

dirs  = [(0,1), (1,0), (-1,0), (0,-1)]

def manhhatan(p1,p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

class Game():

    def __init__(self,start):
        self.startingPlayer = start
        self.noBeat = 0
        self.animals = [None, None]
        self.board = [ [None] * 7 for i in range(9)]
        self.animals[0] = [(lion,(0,0)), (tiger,(0,6)), (dog,(1,1)), (cat,(1,5)), (rat,(2,0)), (jeopard,(2,2)), (wolf,(2,4)), (elephant,(2,6))]
        self.animals[1] = [(lion,(8,6)), (tiger,(8,0)), (dog,(7,5)), (cat,(7,1)), (rat,(6,6)), (jeopard,(6,4)), (wolf,(6,2)), (elephant,(6,0))]

        for player in range(2):
            for (a,p) in self.animals[player]:
                self.board[p[0]][p[1]] = (a[0],player)

    def moves(self, player):
        moves = []
        for d in dirs:
            for (a,p) in self.animals[player]:
                newP = (new_y,new_x) = (p[0] + d[0], p[1] + d[1])

                if new_x < 0 or new_x > 6 or new_y < 0 or new_y > 8: #Out of the board
                    continue

                tmp = False
                while newP in water and a[3]: #Jumping through the water
                    newP = (new_x,new_y) = (newP[0] + d[0], newP[1] + d[1])
                    if (rat, newP) in self.animals[1-player]: #Cannot jump above enemy rat
                        tmp = True
                        break
                if tmp:
                    continue

                if newP in water and not a[2]: #Can't go to the water
                    continue

                if newP == caves[player]: #Can't go into my cave
                    continue

                if (a[0] == "r") and (p in water) and (newP not in water) and (self.board[newP[0]][newP[1]] is not None):
                    continue

                if self.board[newP[0]][newP[1]] is not None: #BEAT!
                    (animal, owner) = self.board[newP[0]][newP[1]]
                    if owner == player: #Cannot beat myself
                        continue
                    if newP in traps:
                        moves.append((a[0],newP))
                    elif a[1] >= strentgh[animal] or (a[1] - strentgh[animal] == 10):
                        moves.append((a[0],newP))
                else:
                    moves.append((a[0],newP))
        return moves

    def doMove(self, player, move):
        pos = move[1]
        animalId = move[0]
        self.animals[1-player] = [ (a,p) for (a,p) in self.animals[1-player] if p != pos]

        newAnimals = []
        for (a,p) in self.animals[player]:
            if a[0] == animalId:
                self.board[p[0]][p[1]] = None
                newAnimals.append((a,pos))
            else:
                newAnimals.append((a,p))
        self.animals[player] = newAnimals
        if self.board[pos[0]][pos[1]] is not None:
            self.noBeat = 0
        else:
            self.noBeat+=1
        self.board[pos[0]][pos[1]] = (animalId,player)

    def doRandomMove(self,player):
        moves = self.moves(player)
        if len(moves) == 0:
            return
        move = random.choice(moves)
        self.doMove(player, move)

    def doHeuristicMove(self,player):
        moves = self.moves(player)
        if len(moves) == 0:
            return
        move = min(moves, key = lambda x: self.heuristic(x,player))
        self.doMove(player, move)

    def win(self):
        c0 = self.board[caves[0][0]][caves[0][1]]
        c1 = self.board[caves[1][0]][caves[1][1]]

        if c0 is not None:
            return 1
        if c1 is not None:
            return 0

        if self.noBeat >= 130:
            for animalId in animalsSorted:
                got = [None, None]
                for (a,p) in self.animals[0]:
                    if a[0] == animalId:
                        got[0] = True
                        break
                for (a,p) in self.animals[1]:
                    if a[0] == animalId:
                        got[1] = True
                        break
                if got[0] and got[1] is None:
                    return 0
                if got[1] and got[0] is None:
                    return 1

                return self.startingPlayer

        return None

    def printBoard(self):
        for i in range(9):
            for j in range(7):
                tmp = True
                if self.board[i][j] is not None:
                    (a,pl) = self.board[i][j]
                    if pl == 0:
                        print(a,end="")
                        tmp = False
                    else:
                        print(a.upper(),end="")
                        tmp = False
                if tmp and (i,j) in traps:
                    print("#",end="")
                    tmp = False
                if tmp and (i,j) in caves:
                    print("*",end="")
                    tmp = False
                if tmp and (i,j) in water:
                    print("~",end="")
                    tmp = False
                if tmp:
                    print(".",end="")
            print("")

    def agent1(self, player):
        moves = self.moves(player)
        if len(moves) == 0:
            return

        self.doMove(player,max(moves, key = lambda x: self.simulate(x,NUMSIMULATIONS//len(moves),player)))

    def agent2(self, player):
        moves = self.moves(player)
        if len(moves) == 0:
            return

        self.doMove(player,max(moves, key = lambda x: self.simulate2(x,player)))

    def simulate(self, move, N,player):
        totalMoves = 0
        p1wins = 0
        p2wins = 0
        tmp = 0
        while totalMoves <= N:
            G = Game(self.startingPlayer)
            G.noBeat = self.noBeat
            G.animals = copy.deepcopy(self.animals)
            G.board = copy.deepcopy(self.board)
            G.doMove(player,move)
            totalMoves+=1
            currPlayer = 1-player
            while G.win() is None: #RANDOM GAME
                G.doRandomMove(currPlayer)
                totalMoves+=1
                currPlayer = 1 - currPlayer

            if G.win() == 0:
                p1wins+=1
            elif G.win() == 1:
                p2wins+=1

        if player == 0:
            return p1wins
        else:
            return p2wins

    def simulate2(self, move, player):
        p1wins = 0
        p2wins = 0
        tmp = 0
        sims = 0
        while sims < 5:
            G = Game(self.startingPlayer)
            G.noBeat = self.noBeat
            G.animals = copy.deepcopy(self.animals)
            G.board = copy.deepcopy(self.board)
            G.doMove(player,move)
            currPlayer = 1-player
            totalMoves = 0
            while totalMoves < 10:
                if (currPlayer == player):
                    G.doHeuristicMove(currPlayer)
                else:
                    G.doRandomMove(currPlayer)
                currPlayer = 1 - currPlayer
                totalMoves+=1
            while G.win() is None: #RANDOM GAME
                G.doRandomMove(currPlayer)
                totalMoves+=1
                currPlayer = 1 - currPlayer

            if G.win() == 0:
                p1wins+=1
            elif G.win() == 1:
                p2wins+=1
            sims+=1

        if player == 0:
            return p1wins
        else:
            return p2wins

    def heuristic(self, move, player):
        G = Game(self.startingPlayer)
        G.noBeat = self.noBeat
        G.animals = copy.deepcopy(self.animals)
        G.board = copy.deepcopy(self.board)
        G.doMove(player,move)
        score = 0
        for a in G.animals[player]:
            score += (manhhatan(a[1], caves[1-player]) ** 1)

        return score


p1wins = 0
p2wins = 0
G = Game(0)
currPlayer = 0

# while G.win() is None: #RANDOM GAME
#       G.doRandomMove(currPlayer)
#       currPlayer = 1 - currPlayer
#       G.printBoard()
#       input("")

# if G.win() == 1:
#       print("Player1 won!")
# else:
#       print("Player2 won!")


for i in range(NUMGAMES):
    currPlayer = random.choice([0,1])
    G = Game(currPlayer)
    while G.win() is None: #RANDOM GAME
        if currPlayer == 0:
            G.agent1(currPlayer)
        else:
            G.doHeuristicMove(currPlayer)
        currPlayer = 1 - currPlayer
    G.printBoard()
    if G.win() == 0:
        p1wins+=1
    elif G.win() == 1:
        p2wins+=1


    if i%1 == 0:
        print("%d games played"%i)
        print("P1 won: %d\nP2 won: %d"%(p1wins,p2wins))
