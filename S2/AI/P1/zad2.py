#!/usr/bin/python

dictionary = set()
DP = []

def importDictionary():
    with open('words_for_ai1.txt','r') as f:
        lines = f.readlines()
        for line in lines:
            global dictionary
            dictionary.add(line.strip())

def getBestRow(row):
    del DP[:]
    for i in range(len(row)+1):
        DP.append([0,''])
    for i in range(len(row)+1):
        currWord = ''
        for j in range(i-1,max(i-40,-1),-1):
            currWord += row[j]
            if currWord[::-1] in dictionary:
                if DP[i][0] < (DP[j][0] + (len(currWord) * len(currWord))):
                    DP[i] = [DP[j][0] + (len(currWord) * len(currWord)),DP[j][1] + ' ' + currWord[::-1]]

importDictionary()

with open('zad2_input.txt','r') as file:
    lines = file.readlines()
    for line in lines:
        line = line.strip()
        getBestRow(line)
        bestRow = DP[len(line)][1]
        bestRow = bestRow[1:]
        output = open("zad2_output.txt","a")
        output.write("{}\n".format(bestRow))
        output.close() 