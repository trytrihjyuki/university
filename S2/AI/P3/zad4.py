from itertools import product
inpt = open('zad_input.txt').readlines()
otpt = open('zad_output.txt', 'w')

def B(i,j):
    return 'B_%d_%d' % (i,j)

def storms(raws, cols, triples):
    writeln(':- use_module(library(clpfd)).')
    
    R = len(raws)
    C = len(cols)
    
    bs = [B(i, j) for i in range(R) for j in range(C)]

    writeln('solve([' + ', '.join(bs) + ']) :- ')

    writeln('[' + ', '.join(bs) + '] ins 0..1,')

    for i,raw in enumerate(raws):
        rs = [B(i,j) for j in range(C)]
        writeln('sum([' + ', '.join(rs) + '], #=, ' + str(raw) + '), ')

    for j, col in enumerate(cols):
        cs = [B(i,j) for i in range(R)]
        writeln('sum([' + ', '.join(cs) + '], #=, ' + str(col) + '), ')

    forbiddenSquares = [[1,1,1,0], [1,1,0,1], [1,0,1,1], [0,1,1,1], [1,0,0,1], [0,1,1,0]]
    allSquares = [list(mask) for mask in product(*[[0,1]]*4)]
    goodSquares = [s for s in allSquares if s not in forbiddenSquares]

    for j in range(C-2):
        for i in range(R):
            writeln('tuples_in( [['+B(i,j)+','+B(i,j+1)+','+B(i,j+2)+']], [ [0,0,0], [1,1,0], [1,0,0],[0,1,1], [0,0,1], [1,1,1], [1,0,1]]),')
    for j in range(C):
        for i in range(R-2):
            writeln('tuples_in( [['+B(i,j)+','+B(i+1,j)+','+B(i+2,j)+']], [ [0,0,0], [1,1,0], [1,0,0],[0,1,1], [0,0,1], [1,1,1], [1,0,1]]),')

    for j in range(C-1):
        for i in range(R-1):
            writeln('tuples_in( [['+B(i,j)+','+B(i+1,j)+','+B(i,j+1)+','+B(i+1,j+1)+']],'+str(goodSquares)+'),')

    # for j in range(C-1):
    #     for i in range(R-1):
    #         writeln(B(i,j+1)+'+'+B(i+1,j)+'#= 2 #<==> '+B(i,j)+'+'+B(i+1,j+1)+'#= 2, ')

    # for i in range(R-2):
    #     for j in range(C):
    #         writeln(B(i+1,j)+'#= 1 #==> '+B(i,j)+'+'+B(i+2,j)+'#>= 1, ')

    # for j in range(C-2):
    #     for i in range(R):
    #         writeln(B(i,j+1)+'#= 1 #==> '+B(i,j)+'+'+B(i,j+2)+'#>= 1, ')

    for x, y, val in triples:
        otpt.write('%s #= %d, ' % (B(x, y), val))

    writeln('')
    writeln('    labeling([ff], [' +  ', '.join(bs) + ']).' )
    writeln('')
    writeln(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.")

def writeln(s):
    otpt.write(s + '\n')


if __name__ == "__main__":
    raws = list(map(int, inpt[0].split()))
    cols = list(map(int, inpt[1].split()))
    triples = []

    for i in range(2, len(inpt)):
        if inpt[i].strip():
            triples.append(list(map(int, inpt[i].split())))

    storms(raws, cols, triples)