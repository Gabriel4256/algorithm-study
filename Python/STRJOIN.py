## 어렵지 않은 그리디 문제

from bisect import bisect_left
def main():
    for _ in range(int(input())):
        input()
        numbers = list(map(int, input().strip().split()))
        numbers.sort()
        answer = 0
        cur_len = len(numbers)
        while len(numbers) > 1:
            n1 = numbers.pop(0)
            n2 = numbers.pop(0)
            idx = bisect_left(numbers, n1 + n2)
            numbers.insert(idx, n1 + n2)
            answer += n1 + n2;
        print(answer)

if __name__ == "__main__":
    main()