## 알고리즘은 맞는데, 제한시간 초과!!
## memo를 dictionary에서 list로 바꾸니까 해결됨!
## 아무래도 dictionary구조로 동적으로 메모를 하는 게 느린듯?
## backtracking을 잘 기억해 두자!

import sys

memo = []
names = []
volumes = []
need = []
picked = []
sys.setrecursionlimit(10**6)

def get_max_need(s_index, cap):
    result = (0, [])
    if memo[s_index][cap] != -1:
        return memo[s_index][cap]
    if s_index >= len(names) or cap <=0:
        return 0
    result = get_max_need(s_index + 1, cap)
    if volumes[s_index] <= cap:
        result = max(result, need[s_index] + get_max_need(s_index + 1, cap - volumes[s_index]))
    memo[s_index][cap] = result
    return result

def reconstruct(s_index, cap):
    if s_index >= len(names):
        return
    if get_max_need(s_index, cap) == get_max_need(s_index + 1, cap):
        reconstruct(s_index + 1, cap)
    else:
        picked.append(names[s_index])
        reconstruct(s_index+1, cap - volumes[s_index])

for _ in range(int(input())):
    # initialization
    maxv = 0
    names = []
    volumes = []
    need = []

    no_of_items, cap = map(int, sys.stdin.readline().strip().split())
    memo = [[-1] * (cap + 1) for _ in range(no_of_items + 1)]
    for _ in range(no_of_items):
        name, v, n = input().strip().split();
        names.append(name)
        volumes.append(int(v))
        need.append(int(n))
    picked = []
    reconstruct(0, cap)
    print(memo[0][cap], len(picked))
    for item in picked:
        print(item)

        