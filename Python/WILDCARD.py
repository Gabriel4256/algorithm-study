import sys
## index 실수에 조심할 것!!

# 이거 안쓰임
def check(wc,target, windex, tindex):
    tmp1 = windex; tmp2 = tindex
    if (windex, tindex) in memo:
        return memo[(windex, tindex)]
    while windex < len(wc) and tindex < len(target):
        if wc[windex] == '*':
            for i in range(0, len(target) - tindex):
                if check(wc, target, windex+1, tindex + i):
                    memo[(tmp1, tmp2)] = True
                    return True
            memo[(tmp1, tmp2)] = False
            return False
        elif wc[windex] == '?':
            windex+=1; tindex+=1
        else:
            if wc[windex] == target[tindex]:
                windex+=1; tindex+=1
            else:
                memo[(tmp1, tmp2)] = False
                return memo[(tmp1, tmp2)]
    if tindex == len(target) and windex == len(wc):
        memo[(tmp1, tmp2)] = True
        return memo[(tmp1, tmp2)]
    elif windex == len(wc):
        memo[(tmp1, tmp2)] = False
        return memo[(tmp1, tmp2)]
    elif tindex == len(target):
        for i in range(windex, len(wc)):
            if wc[i] != '*':
                memo[(tmp1, tmp2)] = False
                return memo[(tmp1, tmp2)]
        memo[(tmp1, tmp2)] = True
        return memo[(tmp1, tmp2)]
    else:
        raise ValueError
                
                
i = int(input())
for j in range(i):
    wc = input()
    num = int(input())
    result = []
    memo = {}
    for k in range(num):
        tmp = input()
        memo = {}
        
        for l in range(len(wc)-1, -1 ,-1):
            for m in range(len(tmp)-1, -1, -1):
                if l == len(wc) - 1 and m == len(tmp) - 1:
                    memo[(l,m)] = wc[l] == tmp[m] or wc[l] == '?' or wc[l] == '*'
                elif l == len(wc) - 1:
                    memo[(l,m)] = wc[l] == '*'
                elif m == len(tmp) - 1:
                    if wc[l] == tmp[m] or wc[l] == '?':
                        memo[(l, m)] = set(list(wc[l+1:])) == set(['*'])
                    elif wc[l] == '*':
                        memo[(l, m)] = memo[(l+1, m)]
                    else:
                        memo[(l, m)] = False
                else:
                    if wc[l] == '*':
                        memo[(l,m)] = memo[(l, m+1)] or memo[(l+1, m)]
                    elif wc[l] == '?':
                        memo[(l,m)] = memo[(l+1,m+1)]
                    else:
                        if wc[l] == tmp[m]:
                            memo[(l,m)] = memo[(l+1,m+1)]
                        else:
                            memo[(l,m)] = False
        # if tmp == 'help' and wc == '*p*':
        #     print(memo)
        if memo[(0,0)]:
            result.append(tmp)
    result.sort()
    for k in result:
        print(k)