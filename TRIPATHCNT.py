## piece of a cake

numbers = []
memo = {}
for i in range(int(input())):
    memo = {}
    numbers = []
    for j in range(int(input())):
        tmp = list(map(int, input().strip().split(' ')))
        numbers.append(tmp)
    
    for j in range(len(tmp)-1, -1, -1):
        for k in range(j, -1, -1):
            if j == len(tmp) - 1:
                memo[(j, k)] = (numbers[j][k], 1)
            else:
                if memo[(j + 1, k)][0] == memo[(j+1, k+1)][0]:
                    memo[(j, k)] = (numbers[j][k] + memo[(j+1, k)][0], memo[(j+1, k)][1] + memo[(j+1, k+1)][1])
                else:
                    if memo[(j+1, k)][0] > memo[(j+1, k+1)][0]:
                        memo[(j, k)] = (numbers[j][k] + memo[(j+1, k)][0], memo[(j+1, k)][1])
                    else:
                        memo[(j,k)] = (numbers[j][k] + memo[(j+1, k+1)][0], memo[(j+1, k+1)][1])
    print(memo[(0, 0)][1])
    