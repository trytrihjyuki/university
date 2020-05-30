from collections import deque
import copy
#### INPUT ####
with open('zad_input.txt','r') as f:
    lines = f.readlines()

n,m = map(int, lines[0].strip().split())
lines.pop(0)

rows = [lines[i].strip().split() for i in range(n)]
columns = [lines[i].strip().split() for i in range(n,len(lines))]

rows = [list(map(int, row)) for row in rows]
columns = [list(map(int, column)) for column in columns]
#### SOLVE ####
board_og = []
for y in range(n):
    board_og.append([])
    for x in range(m):
        board_og[y].append(False)

def allPossibleBlocks(size,lastEndPos,pattern,ind):
    if ind == len(pattern):
        return [[0]*(size-lastEndPos+1)]
    if len(pattern) == 0:
        return [[0]*size]

    pom = 1
    if ind == (len(pattern) - 1):
        pom = 0
    start = lastEndPos
    if pattern[ind] + start > size:
        return
    currAllPoss = []
    while pattern[ind] + start <= size:
        tryBlock = allPossibleBlocks(size,pattern[ind] + start + 1,pattern,ind+1)
        if tryBlock is not None:
            for comp in tryBlock:
                currAllPoss.append((start - lastEndPos)*[0] + pattern[ind]*[1]  + pom*[0] +  comp)
        else:
            return currAllPoss
        start+=1

    return currAllPoss

possible_rows_og = [allPossibleBlocks(m,0,row,0) for row in rows]
possible_columns_og = [allPossibleBlocks(n,0,col,0) for col in columns]

badPixels = deque()

def saveOutput(board):
    output = open("zad_output.txt","w+")
    for row in board:
        str1 = ""
        row = ['#' if x else '.' for x in row]
        output.write("{}\n".format(str1.join(row)))
    output.close()

def DFS(board,badPixels,possible_rows,possible_columns):
    flag = True
    for y in range(n):
        for x in range(m):
            if (not possible_rows[y]) or (not possible_columns[x]):
                return
    while flag:
        flag = False
        newBadPixels = deque()
        for i in range(len(badPixels)):
            y, x = badPixels[i]
            if (not tryToFix(y,x,board,possible_rows,possible_columns)):
                newBadPixels.append((y,x))
            else:   
                flag = True
            if (not possible_rows[y]) or (not possible_columns[x]):
                return
        badPixels = newBadPixels

    if badPixels:
        y, x = badPixels.popleft()

        possible_columns2 = copy.copy(possible_columns)
        possible_rows2 = copy.copy(possible_rows)
        
        board[y][x] = True
        cleanColumns(y,x,True,possible_columns)
        cleanRows(y,x,True,possible_rows)
        DFS(copy.copy(board),badPixels.copy(),copy.copy(possible_rows),copy.copy(possible_columns))
        
        board[y][x] = False
        cleanRows(y,x,False,possible_rows2)
        cleanColumns(y,x,False,possible_columns2)
        DFS(copy.copy(board),badPixels.copy(),possible_rows2,possible_columns2)
    else:
        saveOutput(board)
        exit(0)


def cleanRows(y,x,val,possible_rows):
    possible_rows[y] = [row for row in possible_rows[y] if row[x] == val]

def cleanColumns(y,x,val,possible_columns):
    possible_columns[x] = [col for col in possible_columns[x] if col[y] == val]

def tryToFix(y,x,board,possible_rows,possible_columns):
        allComps = possible_rows[y]
        val = possible_rows[y][0][x]
        if all(possible_rows[y][k][x] == val for k in range(len(possible_rows[y]))): # Wszystkie możliwe ułożenia i-tego wiersza mają ten sam bit na pozycji (i,j)
            board[y][x] = val
            cleanColumns(y,x,val,possible_columns)
            return True
        else:
            val = possible_columns[x][0][y]
            if all(possible_columns[x][k][y] == val for k in range(len(possible_columns[x]))): # Wszystkie możliwe ułożenia j-tej kolumny mają ten sam bit na pozycji (i,j)
                board[y][x] = val
                cleanRows(y,x,val,possible_rows)
                return True
            else:
                return False

for y in range(n):
    for x in range(m):
        if not tryToFix(y,x,board_og,possible_rows_og,possible_columns_og):
            badPixels.append((y,x))

DFS(copy.copy(board_og),badPixels.copy(),copy.copy(possible_rows_og),copy.copy(possible_columns_og))