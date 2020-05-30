#!/usr/bin/python

import random
from itertools import combinations

blotkarz = []
figurant = []

blotkarz.append([])
figurant.append([])
for card in range(0,17):
    blotkarz.append([])
    figurant.append([])
    for color in range(1,7):
        blotkarz[card].append(False)
        figurant[card].append(False)

blotkarzCards = []
figurantCards = []

def getScore(hand):
    hand = sorted(hand, key = lambda x: x[1])
    score = 0
    flush = True
    straight = True
    for i in range(1,5):
        if hand[i][0] != hand[i-1][0]:
            flush = False
    for i in range(1,5):
        if (hand[i][1] - hand[0][1]) != i:
            straight = False

    handSpreading = []
    i = 1
    sameCards = 1
    while i < 5:
        if hand[i][1] == hand[i-1][1]:
            sameCards+=1
        else:
            handSpreading.append(sameCards)
            sameCards = 1
        i+=1
    handSpreading.append(sameCards)

    handSpreading = sorted(handSpreading, reverse = True)

    if straight and flush: # Straight Flush
        return 8
    if handSpreading[0] == 4: # Four of kind
        return 7
    if (handSpreading[0] == 3) and (handSpreading[1]==2): # Full House
        return 6
    if flush: # Flush
        return 5
    if straight: # Straight
        return 4
    if handSpreading[0] == 3: # Three of kind
        return 3
    if (handSpreading[0] == 2) and (handSpreading[1] == 2): # Two of kind
        return 2
    if handSpreading[0] == 2: # One pair
        return 1
    return 0


for color in range(1,5):
    for card in range(2,11):
        blotkarz[card][color] = True
    for card in range(11,15):
        figurant[card][color] = True

for color in range(1,5):
    for card in range(2,11):
        if blotkarz[card][color]:
            blotkarzCards.append([color,card])
    for card in range(11,15):
        if figurant[card][color]:
            figurantCards.append([color,card])

figurantScores=[]
blotkarzScores=[]

for i in range(20):
    figurantScores.append(0)
    blotkarzScores.append(0)

figurantHands = [list(hand) for hand in combinations(figurantCards, 5)]
blotkarzHands = [list(hand) for hand in combinations(blotkarzCards, 5)]

for hand in figurantHands:
    figurantScores[getScore(hand)]+=1
for hand in blotkarzHands:
    blotkarzScores[getScore(hand)]+=1

figurantWorse = figurantScores[1]
totalWins = 0

for i in range(2,9):
    totalWins+=(figurantWorse*(blotkarzScores[i]))
    figurantWorse+=figurantScores[i]

print((totalWins/(len(figurantHands)*len(blotkarzHands)))*100)