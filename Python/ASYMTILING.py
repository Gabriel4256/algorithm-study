## so easy

memo_total = [-1] * 101
memo_sym = [-1] * 101
memo_total[0] = 1; memo_total[1] = 1
memo_sym[0] = 1; memo_sym[1] = 1; memo_sym[2] = 2; memo_sym[3] = 1
for _ in range(int(input())):
    width = int(input())
    for i in range(width+1):
        if memo_total[i] == -1:
            memo_total[i] = memo_total[i-1] + memo_total[i-2]
        if memo_sym[i] == -1:
            memo_sym[i] = memo_sym[i-2] + memo_sym[i-4]
    print((memo_total[width] - memo_sym[width]) % (10**9 + 7))