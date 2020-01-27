# 시간제한에 걸리는 코드. CPP로 동일한 알고리즘의 코드를 작성하니 통과되었다...

import sys

global foods, memo

def main():
    global foods, memo
    for _ in range(int(input())):
        foods = []
        no_of_foods, budget = map(int, input().strip().split())
        memo = [0] * (budget // 100 + 1)
        for _ in range(no_of_foods):
            foods.append(list(map(int, input().strip().split())))
        sorted(foods, key = lambda x: x[0])
            
        for i in range(0, budget // 100 + 1):
            if i == 0:
                memo[i] = 0
            else:
                for food in foods:
                    if food[0] // 100 > i:
                        break;
                    memo[i] = max(food[1] + memo[i - food[0] // 100], memo[i])
        print(memo[budget // 100])
if __name__ == '__main__':
    main()
    