## 매우 쉬운 문제.

import sys
global memo
       
def reconstruct(hyphen_count, o_count, remaining):
    global memo
    if remaining == 1:
        return hyphen_count * '-' + o_count * 'o'
    if hyphen_count > 0:
        if remaining <= memo[hyphen_count-1][o_count]:
            return '-' + reconstruct(hyphen_count-1, o_count, remaining)
        else:
            return 'o' + reconstruct(hyphen_count, o_count-1, remaining - memo[hyphen_count-1][o_count])
    
if __name__ == '__main__':
    global memo
    for _ in range(int(sys.stdin.readline().strip())):
        n,m,k = map(int, sys.stdin.readline().strip().split())
        memo = [[0]*101 for _ in range(101)]
        memo[0][0] = 1
        answer = ''
        for i in range(n+1):
            for j in range(m+1):
                if memo[i][j] != 0:
                    continue
                if i !=0:
                    memo[i][j] += memo[i-1][j]
                if j !=0:
                    memo[i][j] += memo[i][j-1]
        print(reconstruct(n,m,k))
               
        