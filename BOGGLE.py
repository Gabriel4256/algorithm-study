# testcase별 초기화를 제대로 하자!!!!!
# memoization

import sys

global board
global word
global memo

def check(startx, starty, wordindex):
    global word
    global board
    global memo
    if wordindex in memo[startx][starty]:
        return memo[startx][starty][wordindex]
        
    result = False
    if wordindex >= len(word):
        return True
    for i in range(-1, 2):
        for j in range(-1, 2):
            if i == 0 and j ==0:
                continue
            x = startx + i;
            y = starty + j;
            if x < 5 and x > -1 and y < 5 and y > -1 and word[wordindex] == board[x][y]:
                result = result or check(x, y, wordindex + 1)
    memo[startx][starty][wordindex] = result
    return result

board = []
result = False
memo = [[{} for j in range(5)] for i in range(5)]

i = int(input())
for j in range(i):
    board = []
    result = False
    for l in range(5):
        w = input()
        board.append(list(w))
    wordnum = int(input())
    for l in range(wordnum):
        result = False
        memo = [[{} for j in range(5)] for i in range(5)]
        
        word = input();
        for k in range(5):
            for t in range(5):
                if board[k][t] == word[0]:
                    result = result or check(k, t, 1)
        if result:
            print(word + " YES")
        else:
            print(word + " NO")
            
            