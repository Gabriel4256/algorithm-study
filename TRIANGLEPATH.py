# 쉬운 dynamic programming 문제

import sys

i = int(input())

for j in range(i):
    height = int(input())
    tri = []
    memo = {}
    for k in range(height):
        tmp = input().strip()
        tmp = list(map(int, tmp.split(' ')))
        tri.append(tmp)
    for k in range(height-1, -1, -1):
        for l in range(0, k+1):
            if k == height -1:
                memo[(k,l)] = tri[k][l]
            else:
                memo[(k, l)] = max(memo[(k+1, l)], memo[(k+1, l+1)]) + tri[k][l]
    print(memo[(0, 0)])