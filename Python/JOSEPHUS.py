## 간단한 linked list 문제

def main():
    for _ in range(int(input())):
        N, K = map(int, input().strip().split())
        li = [i for i in range(1, N + 1)]
        removal = 0
        while len(li) > 2:
            del li[removal]
            removal = (removal + K - 1) % len(li)
        print(*li, sep=" ")

if __name__ == '__main__':
    main()
    