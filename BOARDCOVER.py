## 풀지 못함, 나중에 다시 재도전

import sys
import copy

global k, l

def check(board):
    global k, l
    count = 0
    sort = (((0, 0), (0, -1), (-1, 0)), ((0, 0), (0, 1), (0, -1)), ((0, 0), (0, -1), (1, 0)), ((0,0), (0,1), (1,0)))
    flag = False
    for i in range(k):
        for j in range(l):
            if board[i][j]:
                for s in sort:
                    for u in range(3):
                        points = []
                        result = True
                        for m in range(3):
                            x = i + s[m][0] -s[u][0]
                            y = j + s[m][1] -s[u][1]
                            if x > -1 and x < len(board) and y > -1 and y < len(board[0]):
                                points.append((x, y))
                                result = result and board[x][y]
                            else:
                                result = False
                                break
                        if result:
                            flag = True
                            tmp = copy.deepcopy(board)
                            for point in points:
                                tmp[point[0]][point[1]] = False
                            # print(tmp)
                            count += check(tmp)
                if not flag:
                    return 0
                else:
                    return count
    if not flag:
        return 1
    return count

i = int(input())
for j in range(i):
    inp = input()
    k = int(inp.split(' ')[0])
    l = int(inp.split(' ')[1])
    board = [[False for i in range(l)] for i in range(k)]
    for i in range(k):
        t = input()
        t = list(t)
        for m in range(l):
            # True: 흰 칸, False:검은  칸
            if t[m] == '#':
                board[i][m] = False
            else:
                board[i][m] = True
    print(check(board))
    
    