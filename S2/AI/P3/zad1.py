from collections import deque
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
board = []
for y in range(n):
    board.append([])
    for x in range(m):
        board[y].append(0)

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

possible_rows = [allPossibleBlocks(m,0,row,0) for row in rows]
possible_columns = [allPossibleBlocks(n,0,col,0) for col in columns]

badPixels = deque()


def cleanRows(y,x,val):
    possible_rows[y] = [row for row in possible_rows[y] if row[x] == val]

def cleanColumns(y,x,val):
    possible_columns[x] = [col for col in possible_columns[x] if col[y] == val]

def tryToFix(y,x):
        allComps = possible_rows[y]
        val = possible_rows[y][0][x]
        if all(possible_rows[y][k][x] == val for k in range(len(possible_rows[y]))): # Wszystkie możliwe ułożenia i-tego wiersza mają ten sam bit na pozycji (i,j)
            board[y][x] = val
            cleanColumns(y,x,val)
        else:
            val = possible_columns[x][0][y]
            if all(possible_columns[x][k][y] == val for k in range(len(possible_columns[x]))): # Wszystkie możliwe ułożenia j-tej kolumny mają ten sam bit na pozycji (i,j)
                board[y][x] = val
                cleanRows(y,x,val)
            else:
                badPixels.append((y,x))

for y in range(n):
    for x in range(m):
        tryToFix(y,x)

while badPixels:
    y, x = badPixels.popleft()
    tryToFix(y,x)

output = open("zad_output.txt","w+")
for row in board:
    str1 = ""
    row = ['#' if x else '.' for x in row]
    output.write("{}\n".format(str1.join(row)))
output.close()