# 개같은 재귀 제한

## 남은 블록 수, 이전 단계의 블록 수
memo = [[0] * 101 for _ in range(101)]


def solve(prev, remaining):
    if memo[prev][remaining]!=0:
        return memo[prev][remaining]
    elif remaining == 0:
        memo[prev][remaining] = 1;
    elif prev == 0:
        for i in range(remaining + 1):
            memo[prev][remaining] = solve(i,remaining - i)
    else:
        for i in range(remaining + 1):
            memo[prev][remaining] += (prev + i - 1) * solve(i, remaining - i)
    return memo[prev][remaining]

for _ in range(int(input())):
    blocks = int(input())
    # print(solve(0, blocks))
    memo = [[0] * 101 for _ in range(101)]
    for i in range(blocks + 1):   # remaning
        for j in range(blocks - i + 1): # prev
            if i == 0:
                memo[i][j] = 1
            elif j == 0:
                for k in range(1, i+1):
                    memo[i][j] += memo[i-k][k]
            else:
                for k in range(1, i+1):
                    memo[i][j] += (k + j - 1) * memo[i - k][k]
    # print(memo)
    print(memo[blocks][0] % 10**7)