## 어려운 문제는 아니었는데 감이 떨어졌는지 자꾸만 비교 등을 할 때 boundary check이나 점화식을 쓸 때
## 숫자를 착각하는 등 초보적인 실수들을 계속 반복했다. 애초에 함수를 선언할 때 생각하기 쉬운 방향으로
## 기준을 잡는 습관을 들여야 겠다.

# -*- coding: utf-8 -*-
import sys

## memo의 값은 (a, b) 형태의 tuple인데, 첫 번째 값은 X, Y의 개수
## b는 전체 길이
global memo

def get_len(level):
    ## origin은 X 시작이면 0, Y 시작이면 1
    ## level은 0단계부터 시작
    if level == 1:
        return (1, 4)
    if memo[level]!= (0, 0):
        return memo[level];
    prev_lev_len = get_len(level-1)
    result = (prev_lev_len[0] * 2, prev_lev_len[1] + prev_lev_len[0] * 6)
    memo[level] = result
    return result

def next_level(str):
    result = ''
    for s in str:
        if s == 'X':
            result +='X+YF'
        elif s == 'Y':
            result += 'FX-Y'
        else:
            result +=s
    return result

def reconstruct(initial_string, level, start, length):
    if level == 0:
        return initial_string[start: start + length]
    if length == 0:
        return ""
    answer = ''
    
    for letter in initial_string:
        if length <= 0:
            return answer
        if letter == 'X' or letter == 'Y':
            partial_len = get_len(level)[1]
            if partial_len >= start + 1:
                if partial_len >= start + length:
                    ## 이 부분 집합이 start와 end 모두를 포함할 수 있는 경우
                    return answer + reconstruct(next_level(letter), level-1, start, length)
                else:
                    answer += reconstruct(next_level(letter), level-1, start, partial_len - start)
                    length -= partial_len - start
                    start = 0
            else:
                start -= partial_len
        else:
            if start == 0:
                answer += letter
                length -= 1
            else:
                start -= 1
    return answer

if __name__ == "__main__":
    global memo
    for i in range(int(sys.stdin.readline().strip())):
        gen, start, length = map(int, sys.stdin.readline().split())
        memo = [(0, 0) for _ in range(gen+1)]
        print(reconstruct('FX', gen, start-1, length))
    
    