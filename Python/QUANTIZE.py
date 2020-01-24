import math

global memo
global sq_sums
global sums


sys.setrecursionlimit(10**6)

def get_min_err(start, end, numbers):
    # start, end 둘 다 포함
    global sums, sq_sums
    avg = round((sums[end] - sums[start-1]) / (end - start + 1))
    ai2 = sq_sums[end] - sq_sums[start-1]
    ai = sums[end] - sums[start-1]
    ret = ai2 - 2 * avg * ai + (avg**2) * (end-start + 1)
    # print(start, end, ret)
    return ret
    
def quantize(start, numbers, numcnt):
    global memo
    ret  = math.inf
    if (start, numcnt) in memo:
        return memo[(start, numcnt)]

    if numcnt == 1:
        return get_min_err(start, len(numbers)-1, numbers)
    else:
        for i in range(start+1, len(numbers)):
            ret = min(ret, get_min_err(start, i-1, numbers) + quantize(i, numbers, numcnt-1))
    memo[(start, numcnt)] = ret
    return ret

for i in range(int(input().strip())):
    global memo, sq_sums, sums
    num = int(input().strip().split(' ')[1])
    numbers = list(map(int, input().strip().split(' ')))
    numbers.sort()
    
    memo, sq_sums, sums = {}, {}, {}
    sq_sums[-1] = 0
    sums[-1] = 0
    for j in range(len(numbers)):
        if j == 0:
            sums[j] = numbers[j]
            sq_sums[j] = numbers[j] ** 2
        else:
            sums[j] = sums[j-1] + numbers[j]
            sq_sums[j] = sq_sums[j-1] + numbers[j] ** 2
    # print(sums , sq_sums)
    print(quantize(0, numbers, num))
    # print(memo)