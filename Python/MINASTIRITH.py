## 여러모로 많이 헤멨던 문제, 단순 직선 구간 문제로 바꾸는 것은 떠올렸는데,
## 첫 경계기지를 선택하는 부분에서 좀 헤맸다. 하지만 그렇게 어령운 문제는 아니었다.

import math

global ranges

def get_radian(chord):
    return 2 * math.asin(chord / 16)

def get_answer(start, end):
    if start >= end:
        return 0
    maxval = start
    for r in ranges:
        if r[0] <= start:
            maxval = max(maxval, r[1])
    if maxval == start:
        return 10000
    return 1 + get_answer(maxval, end)

def main():
    global ranges
    for _ in range(int(input())):
        ranges = []
        for _ in range(int(input())):
            y,x,r = map(float, input().strip().split())
            to_point = (2 * math.pi + math.atan2(y, x)) % (2 * math.pi)
            start = (to_point - get_radian(r))
            end = (to_point + get_radian(r))
            ranges.append((start, end))
        ranges = sorted(ranges, key=lambda x: x[0])

        answer = 10000
        for r in ranges:
            if r[0] <=0 or r[1] >= 2 * math.pi:
                begin = r[1] % (2 * math.pi)
                end = (r[0] + 2 * math.pi) % (2 * math.pi)
                answer = min(answer, 1 + get_answer(begin, end))

        if answer < 0 or answer == 10000:
            print('IMPOSSIBLE')
        else:
            print(answer)

if __name__ == "__main__":
    main()