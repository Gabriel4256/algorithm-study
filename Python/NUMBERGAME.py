## 정말 쉬운 문제다. 다만 math.inf를 쓰니까 채점서버에서 런타임 오류가 나는 문제가 있었다.

import sys

global memo
global numbers

sys.setrecursionlimit = 10 ** 9;

def max_profit(start, end, turn):
    global memo, numbers
    if start > end:
        return 0
    if memo[start][end][turn] != -1:
        return memo[start][end][turn]
    
    result = (2 * turn - 1)* 50000
    compare_func = max
    if turn == 1:
        compare_func = min
        # 선공의 차례일 때는 최대한 큰 값을 골라야 한다.
        # 후공의 차례일 때는 최대한 작은 값을 골라야 한다.
    result = compare_func(result, (-2 *turn + 1) *numbers[start] + max_profit(start + 1, end, 1-turn))
    result = compare_func(result, (-2 *turn + 1) *numbers[end] + max_profit(start, end -1, 1-turn))
    if end - start >=1: 
        result = compare_func(result, max_profit(start + 2, end, 1-turn))
        result = compare_func(result, max_profit(start, end -2, 1-turn))
    
    memo[start][end][turn] = result
    return result


def main():
    global memo, numbers
    for _ in range(int(sys.stdin.readline().strip())):
        sys.stdin.readline()
        numbers = list(map(int, sys.stdin.readline().strip().split()))
        memo = [[[-1] * 2 for _ in range(len(numbers))] for _ in range(len(numbers))]
        print(max_profit(0, len(numbers)-1, 0))

if __name__ == '__main__':
    main()
    
     