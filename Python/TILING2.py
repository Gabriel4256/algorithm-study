# 쏘 이지

for i in range(int(input())):
    width = int(input())
    memo = {}
    for j in range(0, width+1):
        if j <= 1:
            memo[j] = 1
        else:
            memo[j] = memo[j-1] + memo[j-2]
    print(memo[width] % (10**9 + 7))
    