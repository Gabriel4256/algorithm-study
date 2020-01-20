import sys

memo = {}
i = int(input())
for j in range(i):
    mat = []
    num = int(input())
    memo = [[False for i in range(num)] for j in range(num)]
    for k in range(num):
        tmp = input()
        tmp = list(map(int,tmp.split(' ')))
        mat.append(tmp)
    for k in range(num-1, -1, -1):
        for l in range(num-1, -1, -1):
            if k == num - 1 and l == num - 1:
                memo[k][l] = True
            else:
                val = mat[k][l]
                if k + val < num:
                    if memo[k+val][l]:
                        memo[k][l] = memo[k + val][l]
                        continue
                if l + val < num:
                    if memo[k][l+val]:
                        memo[k][l] = memo[k][l + val]
                        continue
                memo[k][l] = False
    # print(memo)
    if memo[0][0]:
        print('YES')
    else:
        print('NO')