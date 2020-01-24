## memo하는 기준을 정확히 정하자, 풀기 쉬운 쪽으로
## 어려운 문제는 아니었다
# 이분 탐색을 활용하는 방법도 있지만 잘 이해가 안감

import sys

i = int(input())
for j in range(i):
    k = int(input())
    memo = {}
    if k == 0:
        print(0)
        continue
    nums = list(map(int, input().split(' ')))
    maxl = 1
    for k in range(len(nums) -1, -1, -1):
        if k == len(nums) - 1:
            memo[k] = 1
        else:
            memo[k]  = 1
            for l in range(k+1, len(nums)):
                if nums[k] < nums[l]:
                    memo[k] = max(memo[l] + 1, memo[k])
                maxl = max(maxl, memo[k])
    print(maxl)
    