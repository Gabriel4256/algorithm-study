## 쉬운 그리디 문제2

def main():
    for _ in range(int(input().strip())):
        total_time = 0
        input()
        M = list(map(int, input().strip().split()))
        E = list(map(int, input().strip().split()))

        pair = list(zip(M, E))
        pair = sorted(pair, key=lambda x: -x[1])
        micro_time = 0
        eatting_time = 0
        for p in pair:
            micro_time += p[0]
            total_time = max(total_time, micro_time + p[1])
        print(total_time)

if __name__ == "__main__":
    main()