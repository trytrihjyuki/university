#!/usr/bin/python

def opt_dist(row,D):
    bestAns = len(row)
    for i in range(len(row) - D + 1):
        ones = 0
        for j in range(i,i + D):
            if row[j] == 1:
                ones+=1
        allOnes = row.count(1)
        bestAns = min(bestAns, allOnes - ones + (D - ones))
    return bestAns


output = open('zad4_output.txt','w')
output.close()

with open('zad4_input.txt','r') as inputFile:
    lines = inputFile.readlines()
    for line in lines:
        inputData = line.split()
        with open('zad4_output.txt','a') as outputFile:
            row = []
            for i in range(len(list(inputData[0]))):
                row.append(int(list(inputData[0])[i]))
            D = int(inputData[1])
            outputFile.write(str(opt_dist(row,D)) + '\n')
