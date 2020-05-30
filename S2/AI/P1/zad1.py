#!/usr/bin/python
from collections import namedtuple
from queue import Queue

debug = False
Positions = namedtuple('Positions',['turn','wk_c','wk_r','wt_c','wt_r','bk_c','bk_r'])
allMoves = []
checkmate = False


def checkCorrectness(state):
    if (state.wk_r == state.wt_r) and (state.wk_c == state.wt_c):
        return False
    if (state.wk_r == state.wt_r) and (state.wk_c == state.wt_c):
        return False
    if (abs(state.wk_r - state.bk_r) <= 1) and (abs(state.wk_c - state.bk_c) <= 1): # Kings cannot be neighbours
        return False
    for cord in state[1:7]: # Out of board
        if (cord > 8) or (cord < 1):
            return False
    return True

def check(state):
    return bool((state.bk_r == state.wt_r) ^ (state.bk_c == state.wt_c))

def checkcheck(state): # Checking check and correctness of the move
    return bool(check(state) or not checkCorrectness(state))

def getPossibleMoves(state,currentScore,rookMoves):
    moves = []
    if state.turn == 'white':
        ### Moving white king ###
        moves.append([state._replace(turn = 'black', wk_r = state.wk_r + 1), currentScore + 1, rookMoves])
        moves.append([state._replace(turn = 'black', wk_r = state.wk_r - 1), currentScore + 1, rookMoves])
        moves.append([state._replace(turn = 'black', wk_c = state.wk_c + 1), currentScore + 1, rookMoves])
        moves.append([state._replace(turn = 'black', wk_c = state.wk_c - 1), currentScore + 1, rookMoves])
        moves.append([state._replace(turn = 'black', wk_r = state.wk_r + 1, wk_c = state.wk_c + 1), currentScore + 1, rookMoves])
        moves.append([state._replace(turn = 'black', wk_r = state.wk_r - 1, wk_c = state.wk_c + 1), currentScore + 1, rookMoves])
        moves.append([state._replace(turn = 'black', wk_r = state.wk_r + 1, wk_c = state.wk_c - 1), currentScore + 1, rookMoves])
        moves.append([state._replace(turn = 'black', wk_r = state.wk_r - 1, wk_c = state.wk_c - 1), currentScore + 1, rookMoves])
        ### Moving white tower ###
        if rookMoves <= 3:
            for cord in range(state.wt_c, 9):
                if (((state.wt_r == state.bk_r) and (state.bk_c == cord)) or (state.wt_r == state.wk_r) and (state.wk_c == cord)):
                    break
                moves.append([state._replace(turn = 'black', wt_c = cord), currentScore + 1, rookMoves + 1])
            for cord in range(state.wt_c,0,-1):
                if (((state.wt_r == state.bk_r) and (state.bk_c == cord)) or (state.wt_r == state.wk_r) and (state.wk_c == cord)):
                    break
                moves.append([state._replace(turn = 'black', wt_c = cord), currentScore + 1, rookMoves + 1])
            for cord in range(state.wt_r, 9):
                if (((state.wt_c == state.bk_c) and (state.bk_r == cord)) or (state.wt_c == state.wk_c) and (state.wk_r == cord)):
                    break
                moves.append([state._replace(turn = 'black', wt_r = cord), currentScore + 1, rookMoves + 1])
            for cord in range(state.wt_r,0,-1):
                if (((state.wt_c == state.bk_c) and (state.bk_r == cord)) or (state.wt_c == state.wk_c) and (state.wk_r == cord)):
                    break
                moves.append([state._replace(turn = 'black', wt_r = cord), currentScore + 1, rookMoves + 1])
    else:
        ### Moving black king ###
        flag = True
        if not checkcheck(state._replace(turn = 'white', bk_r = state.bk_r + 1)):
            moves.append([state._replace(turn = 'white', bk_r = state.bk_r + 1), currentScore + 1, rookMoves])
            flag = False
        if not checkcheck(state._replace(turn = 'white', bk_r = state.bk_r - 1)):
            moves.append([state._replace(turn = 'white', bk_r = state.bk_r - 1), currentScore + 1, rookMoves])
            flag = False
        if not checkcheck(state._replace(turn = 'white', bk_c = state.bk_c + 1)):
            moves.append([state._replace(turn = 'white', bk_c = state.bk_c + 1), currentScore + 1, rookMoves])
            flag = False
        if not checkcheck(state._replace(turn = 'white', bk_c = state.bk_c - 1)):
            moves.append([state._replace(turn = 'white', bk_c = state.bk_c - 1), currentScore + 1, rookMoves])
            flag = False
        if not checkcheck(state._replace(turn = 'white', bk_r = state.bk_r + 1, bk_c = state.bk_c + 1)):
            moves.append([state._replace(turn = 'white', bk_r = state.bk_r + 1, bk_c = state.bk_c + 1), currentScore + 1, rookMoves])
            flag = False
        if not checkcheck(state._replace(turn = 'white', bk_r = state.bk_r - 1, bk_c = state.bk_c + 1)):
            moves.append([state._replace(turn = 'white', bk_r = state.bk_r - 1, bk_c = state.bk_c + 1), currentScore + 1, rookMoves])
            flag = False
        if not checkcheck(state._replace(turn = 'white', bk_r = state.bk_r + 1, bk_c = state.bk_c - 1)):
            moves.append([state._replace(turn = 'white', bk_r = state.bk_r + 1, bk_c = state.bk_c - 1), currentScore + 1, rookMoves])
            flag = False
        if not checkcheck(state._replace(turn = 'white', bk_r = state.bk_r - 1, bk_c = state.bk_c - 1)):
            moves.append([state._replace(turn = 'white', bk_r = state.bk_r - 1, bk_c = state.bk_c - 1), currentScore + 1, rookMoves])
            flag = False
        if flag and check(state) and checkCorrectness(state):
            global checkmate
            checkmate = True

    return moves

def getScore(startState):
    queue = Queue(0)
    visitedPositions = set()
    queue.put([startState,0,0,0]) # Posistions, score, Id, rookMoves
    allMoves.append([startState,-1]) # Positions, lastMove, father
    while not queue.empty():
        state = queue.get()
        if (not state[0] in visitedPositions) and checkCorrectness(state[0]):
            visitedPositions.add(state[0])
            possibleMoves = getPossibleMoves(state[0],state[1],state[3])
            for move in possibleMoves:
                if (not move[0] in visitedPositions) and checkCorrectness(move[0]):
                    allMoves.append([move[0],state[2]])
                    myId = len(allMoves) - 1
                    queue.put([move[0],move[1],myId,move[2]])
            if checkmate:
                if debug:
                    print("Checkmate! In {} moves.".format(state[1]))
                    movesToWin = []
                    currId = state[2]
                    while currId != -1:
                        movesToWin.append(allMoves[currId])
                        currId = allMoves[currId][1]
                    movesToWin.reverse()
                    for move in movesToWin:
                        print(move)
                output = open("zad1_output.txt","w")
                output.write("{}\n".format(state[1])) 
                output.close() 
                return


with open('zad1_input.txt', 'r') as file:
    lines =  file.readlines()
    tests = []
    for test in lines:
        tests.append(test.strip().split())
    for test in tests:
        startingPositions = Positions(test[0],ord(test[1][0]) - 96,int(test[1][1]),ord(test[2][0]) - 96,int(test[2][1]),ord(test[3][0]) - 96,int(test[3][1]))
        if debug:
            print("New test: ",test)
        getScore(startingPositions)