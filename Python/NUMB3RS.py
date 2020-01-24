## 나와있는 난이도(중)에 비해 체감 난이도는 매우 낮았음
from functools import reduce


for _ in range(int(input())):
    ## 지난 일 수, 종착점, value는 학률
    memo = [[0] * 50 for _ in range(101)]
    connected = []
    connected_cnt = []
    node_num, days_passed, ptown = map(int, input().strip().split())
    for _ in range(node_num):
        tmp = list(map(int, input().split()))
        cnt = tmp.count(1)
        connected.append(tmp)
        connected_cnt.append(cnt)
    input()
    targets = list(map(int, input().split()))
    
    for i in range(days_passed +1):
        for j in range(node_num):
            if i == 0:
                if j == ptown:
                    memo[i][j] = 1
            else:
                for k in range(node_num):
                    if connected[k][j] == 1:
                        memo[i][j] += memo[i-1][k] * (1 / connected_cnt[k])
            

    print(reduce(lambda x,y: "{} {}".format(x, y), [memo[days_passed][target] for target in targets]))